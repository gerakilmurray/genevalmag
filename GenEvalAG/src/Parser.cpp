/**
  *  \file Parser.cpp
  *      \brief Parsing module.
  *  \date 13/09/2009
  *  \author    Kilmurray, Gerardo Luis.
  *  \author    Picco, Gonzalo Martín.
  */

#include <boost/spirit/include/classic_core.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/spirit/include/classic_symbols.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

#include "SemDomain.h"

using namespace std;
using namespace BOOST_SPIRIT_CLASSIC_NS;
using namespace genevalmag;

#define MAX_INPUT_FILE 1000
#define MAX_INPUT_LINE 128

/** /var sem_domain
  * /brief Variable to represent Semantic domain
  */
SemDomain sem_domain;

///////////////////////////////////////////////
// Operation for Sort
///////////////////////////////////////////////

void add_sort (char const* str, char const* end)
{
    string  name(str, end);
	Sort sort(name);
	sem_domain.add_sort(sort);
}

///////////////////////////////////////////////
// Operation for Operation
///////////////////////////////////////////////

// a new operator in the parser
Operator * new_op;

void inic_op (char const* str, char const* end)
{
	new_op = new Operator();
}

void add_op (char const* str, char const* end)
{
	sem_domain.add_op(*new_op);
	new_op->Operator::~Operator(); // call destruction before free memory.
	free(new_op);
}

void save_mod (char const* str, char const* end)
{
	string mode(str, end);
	new_op->set_mod(mode);
}

void save_mod_assoc (char const* str, char const* end)
{
	string assoc(str, end);
	new_op->set_mod_assoc(assoc);
}

void save_pred (int const i)
{
	new_op->set_pred(i);
}

void save_name (char const* str, char const* end)
{
	string name(str, end);
	new_op->set_name(name);
}

void save_dom (char const* str, char const* end)
{
	string dom(str, end);
	new_op->add_domain(&(sem_domain.return_sort(dom)));
}

void save_img (char const* str, char const* end)
{
	string  img(str, end);
	new_op->set_image(&(sem_domain.return_sort(img)));
}

///////////////////////////////////////////////
// Operation for Functions
///////////////////////////////////////////////

// a new function in the parser
Function * new_function;

void inic_function (char const* str, char const* end)
{
	new_function = new Function();
}

void add_function (char const* str, char const* end)
{
	sem_domain.add_func(*new_function);
	new_function->Function::~Function(); // call destruction before free memory.
	free(new_function);
}

void save_name_function (char const* str, char const* end)
{
	string name(str, end);
	new_function->set_name(name);
}

void save_dom_function (char const* str, char const* end)
{
	string dom(str, end);
	new_function->add_domain(&(sem_domain.return_sort(dom)));
}

void save_img_function (char const* str, char const* end)
{
	string  img(str, end);
	new_function->set_image(&(sem_domain.return_sort(img)));
}

///////////////////////////////////////////////
// Operation for Attributes
///////////////////////////////////////////////

struct decl_attr
{
	vector<string> names;
	string sort_type;
	type_attr mod_type;
	string member_symbol;
} * new_attrs;

void add_attr (char const* str, char const* end)
{
	string name(str, end);
	if (new_attrs == NULL)
	{
		// New declaration. Must be allocate new memory.
		new_attrs = new decl_attr;
	}
	// The declaration has more of one attribute

	// Save name of new attribute
	new_attrs->names.push_back(name);
	if (new_attrs->names.size() == 1)
	{
		new_attrs->mod_type = k_syntetize; // Default value
		new_attrs->member_symbol = "\0";
	}
}

void save_sort_attr (char const* str, char const* end)
{
	string sort(str, end);
	new_attrs->sort_type = sort;
}

void save_type_attr (char const* str, char const* end)
{
	string mod_type(str, end);
	if (mod_type.compare("inh") == 0)
		new_attrs->mod_type = k_inherit;
}

void save_member_list (char const* str, char const* end)
{
	string members(str, end);
	boost::erase_all(members, " ");
	new_attrs->member_symbol = members;
}

void save_decl_attrs (char const* str, char const* end)
{
	for (vector<string>::size_type i = 0; i < new_attrs->names.size(); i++)
	{
		Attribute attr(
						new_attrs->names[i],
						new_attrs->sort_type,
						new_attrs->mod_type,
						new_attrs->member_symbol
				       );
		sem_domain.add_att(attr);

	}
	// Free space memory and assign NULL at pointer.
	free(new_attrs);
	new_attrs = NULL;
}

///////////////////////////////////////////////
// Operation for symbol
///////////////////////////////////////////////

void save_non_terminal(char const* str, char const* end)
{
	string name(str, end);
	Symbol symb(name, k_non_terminal);
	sem_domain.add_symb(symb);
}

void save_terminal(char const* str, char const* end)
{
	string name(str, end);
	// The string is 'char'
	Symbol symb(name, k_terminal);
	sem_domain.add_symb(symb);
}

///////////////////////////////////////////////
// Operation for rules
///////////////////////////////////////////////

Rule * current_rule;

void save_rule(char const* str, char const* end)
{
	sem_domain.add_rule(*current_rule);
	current_rule->Rule::~Rule(); // call destruction before free memory.
	free(current_rule);

}

void add_left_side_rule(char const* str, char const* end)
{
	string left_side_symbol(str, end);
	current_rule = new Rule();
	current_rule->set_left_symbol(&(sem_domain.get_symbol(left_side_symbol)));
}

void add_right_side_rule(char const* str, char const* end)
{
	string right_side_symbol(str, end);
	current_rule->add_right_symbol(&(sem_domain.get_symbol(right_side_symbol)));
}

void abbreviated_rule(char const* str, char const* end)
{
	current_rule = new Rule();
	current_rule->set_left_symbol(current_rule->get_left_symbol());
}

///////////////////////////////////////////////
// Operation of section compute of rule.
///////////////////////////////////////////////

void add_op_exp(char const* str, char const* end)
{
	string name_op(str, end);
	//Operator* op = &(sem_domain.get_operation(name_op));
	//cout << op->get_name() << endl;
	cout << "op " << name_op << endl;
}

void pepito(char const* str, char const* end)
{
	string pepe(str, end);
	cout << pepe << endl;
}

void oper_table(char const* str, char const* end)
{
	string name_op(str, end);

}

///////////////////////////////////////////////
// Skip parser
///////////////////////////////////////////////

struct skip_parser: public grammar<skip_parser>
{
	template <typename ScannerT>
	struct definition
	{
		definition(skip_parser const &self)
		{
			skip = space_p
                    |   "//" >> *(anychar_p - '\n') >> '\n'
                    |   "/*" >> *(anychar_p - "*/") >> "*/"
                    ;
		}
		rule<ScannerT> skip;
		rule<ScannerT> const& start() const { return skip; }
	};
};

///////////////////////////////////////////////
// Type attribute grammar
///////////////////////////////////////////////

struct att_grammar: public grammar<att_grammar>
{
	template <typename ScannerT>
	struct definition
	{
		definition(att_grammar const &self)
		{
			r_ident		= lexeme_d[(alpha_p | '_') >> *(alnum_p | '_' )] - r_reserved_word;

			r_oper		= lexeme_d[(alpha_p | '_' | r_id_op) >> *(alnum_p | '_' | r_id_op)];

			r_id_op		= ch_p ('+')|'*'|'/'|'^'|'%'|'&'|'<'|'='|'-'|'>';

			r_char		= lexeme_d[ch_p('\'')>> (alnum_p | r_id_op) >> ch_p('\'')];

			r_string	= lexeme_d[ch_p('\"')>> +(alnum_p | r_id_op) >> ch_p('\"')];

			r_reserved_word = strlit<>("compute")|strlit<>("COMPUTE")|
							  strlit<>("all")|strlit<>("ALL");

			////////////////////////////////////////////////////////////
			// Grammar's Semantic Domain
			////////////////////////////////////////////////////////////

			r_semantics = strlit<>("semantics domains")>> +bloq_sem;

			bloq_sem    = decl_op[&add_op] | decl_sort | decl_func[&add_function];

			decl_sort   = strlit<>("sort ") >> r_ident[&add_sort][st_sorts.add] >> *(',' >> r_ident[&add_sort]) >> ';';

			decl_op     = strlit<>("op ")[&inic_op] >>
						  (op_infix | op_postfix | op_prefix) >>
						  strlit<>("->") >>
						  sort[&save_img]  >> ';';


			op_infix	=  strlit<>("infix")[&save_mod] >> !oper_mod >> r_oper[&save_name][st_op_infix.add]
			            >> ':' >> sort[&save_dom] >> ',' >> sort[&save_dom];
			op_postfix	=  strlit<>("postfix")[&save_mod] >> !oper_mod >> r_oper[&save_name][st_op_postfix.add]
			            >> ':' >> sort[&save_dom];
			op_prefix	= !(strlit<>("prefix")[&save_mod]) >> !oper_mod >> r_oper[&save_name][st_op_prefix.add]
						>> ':' >> sort[&save_dom];

			oper_mod	= '(' >> (uint_p[&save_pred]| '_') >> ',' >> (mod_assoc[&save_mod_assoc]|'_') >> ')';

			mod_assoc	= strlit<>("left") | strlit<>("right") | strlit<>("non-assoc");

			sort		= st_sorts;

			decl_func	= strlit<>("function ")[&inic_function]
						>> r_oper[&save_name_function][st_functions.add] >> ':' >>
						dom_func >> strlit<>("->") >>
						sort[&save_img_function]  >> ';';

			dom_func    = sort[&save_dom_function] >> *(',' >> sort[&save_dom_function]);

			////////////////////////////////////////////////////////////
			// Grammar's Attribute
			////////////////////////////////////////////////////////////

			r_attributes = strlit<>("attributes")>> +decl_att[&save_decl_attrs];

			decl_att     = r_ident[&add_attr][st_attributes.add] >> *(',' >> r_ident[&add_attr][st_attributes.add]) >>
					       ':' >> !(r_type_att[&save_type_attr]) >> '<' >> r_ident[&save_sort_attr] >> '>' >>
					       strlit<>("of") >>
					       (conj_simb |
					       (strlit<>("all") >> !('-' >> conj_simb)))[&save_member_list] >> ';';

			conj_simb 	 = '{' >> r_ident >> *(',' >> r_ident) >> '}';

			r_type_att   = (strlit<>("inh") | strlit<>("syn"));

			////////////////////////////////////////////////////////////
			// Grammar's Rule
			////////////////////////////////////////////////////////////

			r_rules		 = strlit<>("rules") >> (+decl_rule);

			decl_rule	 = r_ident[&save_non_terminal][&add_left_side_rule][st_symbols.add] >>
						   strlit<>("::=") >> r_right_rule[&save_rule] >>
						   *(strlit<>("|")[&abbreviated_rule] >> r_right_rule[&save_rule]) >> ';';

			r_right_rule = +( r_ident[&save_non_terminal][st_symbols.add]
			                | r_char[&save_terminal])[&add_right_side_rule] >>
						   !(strlit<>("compute") >>
						     +(r_sem_expr)[&pepito] >>
						     strlit<>("end")
						    );

			r_sem_expr	 = left_side >> '=' >> right_side >> ';';

			left_side	 = r_instance;

			right_side	 = r_expresion;

			/** Expresion's Grammar non ambigua based in
			  *
			  * 	E = T <op_infix> E | T
			  *		T = F <op_postfix> | F
			  *		F = (E) | <symb_base>
			  *
			  */
			r_expresion 		= r_expr_prime >> st_op_infix >> r_expresion
								| r_expr_prime;

			r_expr_prime		= r_expr_prime_prime >> st_op_postfix
								| r_expr_prime_prime;

			r_expr_prime_prime  = st_op_prefix >> r_expresion
								| '('>> r_expresion >>')'
								| r_function
								| r_instance
								| r_literal
								;

			r_function			= st_functions >> '(' >> r_expresion >> *(',' >> r_expresion) >> ')';

			/** Literals accepted: Integer and Float numbers, characters and string,
			  * between signs ' and " respectively.
			  */
			r_literal			= int_p | real_p | r_char | r_string;

			/** An instance is, the symbol with the number of occurrences in square brackets within
			  * the rule, with the specific attribute with which it operates.
			  * Example: E[0].value
			  */
			r_instance			= lexeme_d[ st_symbols >> '[' >> int_p >> ']' >> '.' >> st_attributes ];

			////////////////////////////////////////////////////////////
			// Attribute Grammar
			////////////////////////////////////////////////////////////

			r_att_grammar = r_semantics >> r_attributes >> r_rules >> end_p;
		}
		symbols <> st_sorts;

		symbols <> st_op_prefix;
		symbols <> st_op_infix;
		symbols <> st_op_postfix;

		symbols <> st_functions;

		symbols <> st_attributes;

		symbols <> st_symbols;

		rule<ScannerT> r_ident, r_oper, r_id_op, r_char,r_reserved_word, r_string;

		rule<ScannerT> r_semantics, bloq_sem, decl_sort,decl_func, decl_op, mod_assoc, sort,
					   dom_func,oper_mod, op_prefix,op_infix,op_postfix;
		rule<ScannerT> r_attributes, decl_att, r_type_att, conj_simb;
		rule<ScannerT> r_rules, decl_rule, r_sem_expr, left_side, right_side, r_instance, r_right_rule;

		rule<ScannerT> r_expresion,r_function, r_literal, r_expr_prime, r_expr_prime_prime;

		rule<ScannerT> r_att_grammar;
		rule<ScannerT> const& start() const { return r_att_grammar; }
	};
};

///////////////////////////////////////////////
// Parser grammar
///////////////////////////////////////////////
bool parse_grammar(char const* str)
{
	att_grammar gramatica;
	skip_parser skip_p;
	return parse (str,gramatica,skip_p).full;
}

///////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////
int main()
{
	FILE * p_file;
	char buffer[MAX_INPUT_FILE];
	string texto;

	p_file = fopen ("./src/grammar.txt" , "r");
	if (p_file == NULL)
		perror ("Error opening file");
	else
	{
		while ( !feof (p_file) )
		{
	          fgets (buffer , MAX_INPUT_LINE , p_file);
	          texto += buffer;
	    }
		fclose (p_file);
	}

    if (parse_grammar(texto.c_str()))
    {
		cout << "-------------------------\n";
		cout << sem_domain.to_string();
		cout << "-------------------------\n";
		cout << "Parsing OK\n";
		cout << "-------------------------\n";
    }
	else
	{
		cout << "-------------------------\n";
		cout << "Parsing failed\n";
		cout << "-------------------------\n";
	}
    cout << "Bye... :-D" << endl;
    return 0;
}
