/**
  *  \file		Parser_AG.cpp
  *  \brief		Implementation of parsing module of Attribute Grammar, Parser_AG.h.
  *  \date		13/09/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

//#define BOOST_SPIRIT_DEBUG  ///$$$ DEFINE THIS BEFORE ANYTHING ELSE $$$///

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_symbols.hpp>
#include <boost/spirit/include/classic_attribute.hpp>

#include <iostream>
#include <string>

#include "Parser_AG.h"
#include "Semantic_check.h"
#include "Semantics_actions.h"

using namespace std;
using namespace BOOST_SPIRIT_CLASSIC_NS;

namespace genevalmag
{

Parser_AG::Parser_AG()
{
}

Parser_AG::~Parser_AG()
{
}

const Attr_grammar &Parser_AG::get_attr_grammar()
{
	return attr_grammar;
}

/**
  * Declaration of a parser for inputs that ignore within
  * an Attribute Grammar file, with the Spirit library of Boost.
  */
struct skip_parser: public grammar<skip_parser>
{
	template <typename ScannerT>
	struct definition
	{
		definition(skip_parser const &self)
		{
			skip = space_p
				 | "//" >> *(anychar_p - '\n')
				 | "/*" >> *(anychar_p - "*/") >> "*/"
				 ;
		}

		rule<ScannerT> skip;

		rule<ScannerT> const &start() const
		{
			return skip;
		}
	};
};

/**
  * Declaration of the Attribute Grammar structure
  * with the Spirit library of Boost.
  */
struct attritute_grammar: public grammar<attritute_grammar>
{
	template <typename ScannerT>
	struct definition
	{
		definition(attritute_grammar const &self)
		{
			// Common declarations.

			r_ident			= lexeme_d[ (alpha_p | '_') >> *(alnum_p | '_') ] - r_reserved_word;

			r_oper			= lexeme_d[ (alpha_p | '_' | r_id_op) >> *(alnum_p | '_' | r_id_op) ];

			r_id_op			= ch_p('+')|'*'|'/'|'^'|'%'|'&'|'<'|'='|'-'|'>';

			r_char			= lexeme_d[ ch_p('\'') >> (alnum_p | r_id_op) >> ch_p('\'') ];

			char_pp			= lexeme_d[ ch_p('\'') >> (anychar_p) >> ch_p('\'') ];

			r_string		= lexeme_d[ ch_p('\"') >> r_string_lit >> ch_p('\"') ];

			r_string_lit	= +((anychar_p - (ch_p('\"') | "\\" | '\'' )) | r_esc_seq);

			r_esc_seq		= ch_p('\\') >>
							  ( oct_p |
								as_lower_d['x'] >> hex_p |
								(anychar_p - ch_p('\n'))
							  )
				;

			r_reserved_word = strlit<>("compute") 	|
									   "all"	  	|
									   "int" 		|
									   "string" 	|
									   "float"	 	|
									   "char"
							  ;

			r_basic_types	= strlit<>("int") | "float" | "string" | "char";

			/**
			  * Declaration of Semantic Domain.
			  */

			r_semantic_domain = lexeme_d[ strlit<>("semantic domain") >> space_p ] >> +r_bloq_sem;

			r_bloq_sem		  = r_decl_sort | r_decl_oper[&add_operator] | r_decl_func[&add_function];

			// Declaration of Sorts.

			r_decl_sort		  = lexeme_d[ strlit<>("sort") >> space_p ] >>
								(r_ident[&create_sort][st_sorts.add] % ',') >> ';';

			// Declaration of Operators.

			r_decl_oper	= lexeme_d[ strlit<>("op") >> space_p ][&inic_func] >>
							(r_oper_infix | r_oper_postfix | r_oper_prefix) >>
							 strlit<>("->") >>
							 r_sort_st[&save_image_func] >> ';';

			r_oper_infix   = strlit<>("infix")[&save_mode_op] >> !r_oper_mode >>
							 r_oper[&save_name_func][st_op_infix.add] >> ':' >>
							 r_sort_st[&save_domain_func] >> ',' >> r_sort_st[&save_domain_func];

			r_oper_postfix = strlit<>("postfix")[&save_mode_op] >> !r_oper_mode >>
							 r_oper[&save_name_func][st_op_postfix.add] >> ':' >>
							 r_sort_st[&save_domain_func];

			r_oper_prefix  = !(strlit<>("prefix")[&save_mode_op]) >> !r_oper_mode >>
							 r_oper[&save_name_func][st_op_prefix.add] >> ':' >>
							 r_sort_st[&save_domain_func];

			r_oper_mode	   = '(' >>(uint_p[&save_prec_op] | '_') >> ',' >>(r_oper_assoc[&save_assoc_op] | '_') >> ')';

			r_oper_assoc   = strlit<>("left") | strlit<>("right") | strlit<>("non-assoc");

			// Declaration of Functions.

			r_decl_func	= lexeme_d[ strlit<>("function")>> space_p ] >>
							 r_oper[&inic_func][&save_name_func][st_functions.add] >> ':' >>
							 !r_dom_func >> strlit<>("->") >>
							 r_sort_st[&save_image_func] >> ';';

			r_dom_func	= r_sort_st[&save_domain_func] % ',';

			/**
			  * Declaration of Attributes.
			  */
			r_attributes = lexeme_d[ strlit<>("attributes")>> space_p ] >> +r_decl_attr[&create_attributes];

			r_decl_attr  =(r_ident[&add_attribute][st_attributes.add] % ',') >>
						   ':' >> !(r_type_attr[&save_type_attr]) >> '<' >> r_sort_st[&save_sort_attr] >> '>' >>
						   lexeme_d[ strlit<>("of")>> space_p ] >>
						  (r_conj_symb |
						  (strlit<>("all") >> !('-' >> r_conj_symb)))[&save_member_list_attr] >> ';';

			r_conj_symb	 = '{' >>(r_ident % ',') >> '}';

			r_type_attr  =(strlit<>("inh") | strlit<>("syn"));

			/**
			  * Declaration of Rules.
			  */

			r_rules		  = lexeme_d[ strlit<>("rules")>> space_p ] >> (+r_decl_rule) >> eps_p[&check_well_defined];

			r_decl_rule	  = r_ident[&create_new_non_terminal][&create_rule][st_non_terminal.add] >>
							strlit<>("::=") >>
							r_right_rule[&save_rule] >>
							*(strlit<>("|")[&create_abbreviated_rule] >> r_right_rule[&save_rule]) >> ';';

			r_right_rule  = +( r_ident[&create_new_non_terminal][st_non_terminal.add]
			                 | r_terminal[&create_new_terminal]
							 )[&save_right_side_rule] >>
							!(strlit<>("compute") >>
								+(r_equation) >>
							  strlit<>("end")
							 );

			r_terminal	  = lexeme_d[ ch_p('\'') >> r_string_lit >> ch_p('\'') ];

			r_equation	  = r_instance[&create_equation] >> '=' >> r_expression[&save_rvalue] >> ';';

			/**
			  * expression's Grammar non ambiguos based in
			  *
			  * 	E = T *(<op_infix> T)
			  *		T = F *(<op_postfix>) | (<op_prefix>) T
			  *		F = (E) | function | literal | instance
			  */
			r_expression 		= r_expr_prime >> *(r_op_infix_st[&create_operator][&create_func_node] >> r_expr_prime[&create_root_infix_node])
								;

			r_expr_prime		= r_expr_prime_prime >> *(r_op_postfix_st[&create_operator][&create_func_node][&create_root_postfix_node])
								| r_op_prefix_st[&create_operator][&create_func_node] >> r_expr_prime[&create_root_prefix_node]
								;

			r_expr_prime_prime  = ch_p('(')[&increment_level] >> r_expression >> ch_p(')')[&decrement_level]
								| r_function[&create_root_function_node]
								| r_literal[&create_literal_node]
								| r_instance[&create_instance_node]
								;

			/**
			  * The functions accept a list of expressions.
			  */
			r_function			= r_function_st[&create_function][&create_func_node] >> ch_p('(')[&push_mark][&increment_level] >>!(r_expression % ',') >> ch_p(')')[&decrement_level];

			/**
			  * Literals accepted: Integer and Float numbers, characters and string,
			  * between signs ' and " respectively.
			  */
			r_literal			= longest_d[ real_p | int_p ][&create_lit_number]
					 			| r_char[&create_lit_ch]
								| r_string[&create_lit_str]
							    ;

			/**
			  * An instance is, the symbol with the number of occurrences in square brackets within
			  * the rule, with the specific attribute with which it operates.
			  *
			  * Example: E[0].value
			  */
			r_instance			= lexeme_d[ r_non_term_st[&create_instance] >>
					  						'[' >> int_p[&save_index_ins] >> ']' >>
					  						'.' >> r_attribute_st[&save_attr_ins]
					  					  ];

			/**
			  * Declaration of Attribute Grammar.
			  */
			r_att_grammar		= r_semantic_domain >> r_attributes >> r_rules >> end_p ;

			/**
			  * Parsers based in the symbol tables.
			  */
			r_sort_st			= st_sorts | r_basic_types;
			r_op_prefix_st		= st_op_prefix;
			r_op_infix_st		= st_op_infix;
			r_op_postfix_st		= st_op_postfix;
			r_function_st		= st_functions;
			r_attribute_st		= st_attributes;
			r_non_term_st		= st_non_terminal;
		}
		/**
		  * Symbols's Table for the elements of an Attribute Grammar.
		  */
		symbols <> st_sorts;
		symbols <> st_op_prefix;
		symbols <> st_op_infix;
		symbols <> st_op_postfix;
		symbols <> st_functions;
		symbols <> st_attributes;
		symbols <> st_non_terminal;

		/**
		  * Variables using in parsing time.
		  */
		typedef rule<ScannerT> rule_exp;

		 // Rule in lexeme_d.
		typedef rule<typename lexeme_scanner<ScannerT>::type> rule_lexeme;

		// Basic rules: characters, strings and identifiers.
		rule_exp r_reserved_word, r_ident, r_oper, r_char, r_string, r_basic_types, char_pp;

		rule_lexeme r_id_op, r_string_lit, r_esc_seq;

		// Semantic domain's rule: Sort, Operator and Function.
		rule_exp r_semantic_domain, r_bloq_sem, r_decl_sort, r_decl_oper, r_decl_func,
				 r_oper_assoc, r_oper_mode, r_oper_prefix, r_oper_infix, r_oper_postfix,
				 r_dom_func;

		// Atribute's rule.
		rule_exp r_attributes, r_decl_attr, r_type_attr, r_conj_symb;

		// Rule's rule.
		rule_exp r_rules, r_decl_rule, r_equation, r_right_rule, r_terminal;

		// Expresion's rule: Compute. Add context for type expresion.
		rule_exp r_expression,  r_expr_prime, r_expr_prime_prime, r_function, r_literal, r_instance;

		// Translate for symbol table.
		rule_exp r_sort_st, r_op_prefix_st, r_op_infix_st, r_op_postfix_st,
				 r_function_st, r_attribute_st, r_non_term_st, r_sort_stable;

		// Main rule.
		rule_exp r_att_grammar;

		rule_exp const &start() const
		{
			return r_att_grammar;
		}
	};
};

/**
  * This method invokes the method 'parse' of the library Spitir included in Boost.
  * Returns true if could parse all the input.
  */
bool Parser_AG::parse_grammar(char const *txt_input)
{
	attritute_grammar	attr_grammar_decl;
	skip_parser			skip_p;

	set_at(&attr_grammar);
	set_s_check(&sem_check);

	parse_info<> info =  parse(txt_input, attr_grammar_decl, skip_p);

	#ifdef _DEBUG
		cout << "STOP: " << info.stop << "fin-STOP" << endl;
	#endif

	cout << "-------------------------\n";
	if(info.full)
	{
		cout << attr_grammar.to_string();
		cout << "-------------------------\n";
		cout << "Parsing OK\n";
	}
	else
	{
		cout << "Parsing FAILED\n";
	}
	cout << "-------------------------\n";

	return info.full;
}

} // namespace
