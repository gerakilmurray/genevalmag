/**
  *  \file		Parser.cpp
  *  \brief		Parsing module of Attribute Grammar.
  *  \date		13/09/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

//#define BOOST_SPIRIT_DEBUG  ///$$$ DEFINE THIS BEFORE ANYTHING ELSE $$$///

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_symbols.hpp>
#include <boost/spirit/include/classic_attribute.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <stdio.h>
#include <iostream>
#include <string>

#include "SemDomain.h"

using namespace std;
using namespace BOOST_SPIRIT_CLASSIC_NS;
using namespace genevalmag;
using namespace phoenix;

#define PATH_INPUT_FILE "./src/grammar.txt"
/**
  * Constant that represent the maximum size of the file buffer.
  */
#define MAX_INPUT_FILE 32000
/**
  * Constant that represent the maximum size of the line read.
  */
#define MAX_INPUT_LINE 256

/**
  * /var sem_domain
  * /brief Variable to represent Semantic domain.
  */
SemDomain sem_domain;

/**
  * Methods and functions for parse Sort class.
  */
void add_sort (char const* str, char const* end)
{
    string  name (str, end);
	Sort sort (name);
	sem_domain.add_sort (sort);
}

/**
  * Methods and functions for parse Operator class.
  */
/**
  * Pointer that reference a new operator in the grammar.
  */
Operator * current_oper;

void add_operator (char const* str, char const* end)
{
	sem_domain.add_operator (*current_oper);
	// Call destruction before free memory.
	current_oper->Operator::~Operator ();
	free (current_oper);
	current_oper =NULL;
}

//void inic_operator (char const* str, char const* end)
//{
//	// Ignore the string parsed.
//	current_oper = new Operator ();
//}

void save_name_op (char const* str, char const* end)
{
	if (current_oper==NULL)
	{
		current_oper = new Operator ();
	}
	//current_oper = new Operator ();
	string name (str, end);
	current_oper->set_name (name);
}

void save_mode_op (char const* str, char const* end)
{
	if (current_oper==NULL)
	{
		current_oper = new Operator ();
	}
	string mode (str, end);
	current_oper->set_mode (mode);
}

void save_prec_op (int const prec)
{
	if (current_oper==NULL)
	{
		current_oper = new Operator ();
	}
	current_oper->set_prec (prec);
}

void save_assoc_op (char const* str, char const* end)
{
	if (current_oper==NULL)
	{
		current_oper = new Operator ();
	}
	string assoc (str, end);
	current_oper->set_oper_assoc (assoc);
}

void save_domain_op (char const* str, char const* end)
{
	string domain (str, end);
	current_oper->add_domain (&(sem_domain.return_sort (domain)));
}

void save_image_op (char const* str, char const* end)
{
	string image (str, end);
	current_oper->set_image (&(sem_domain.return_sort (image)));
}

/**
  * Methods and functions for parse Function class.
  */
/**
  * Pointer that reference a new function in the grammar.
  */
Function * current_func;

//void inic_function (char const* str, char const* end)
//{
//	current_func = new Function ();
//}

void add_function (char const* str, char const* end)
{
	sem_domain.add_function (*current_func);
	// Call destruction before free memory.
	current_func->Function::~Function ();
	free (current_func);
	current_func = NULL;
}

void save_name_func (char const* str, char const* end)
{
	if (current_func==NULL)
	{
		current_func = new Function ();
	}
	string name (str, end);
	current_func->set_name (name);
}

void save_domain_func (char const* str, char const* end)
{
	string domain (str, end);
	current_func->add_domain (&(sem_domain.return_sort (domain)));
}

void save_image_func (char const* str, char const* end)
{
	string image (str, end);
	current_func->set_image (&(sem_domain.return_sort (image)));
}

/**
  * Methods and functions for parse Attribute class.
  */
/**
  * Type that represent the structure of a full declaration of one Attribute.
  */
struct decl_attribute
{
	vector<string>	d_names;
	string			d_sort_type;
	type_attr		d_mod_type;
	string			d_member_symbol;
} * new_attrs;

void add_attr (char const* str, char const* end)
{
	string name (str, end);
	if (new_attrs == NULL)
	{
		// New declaration. Must be allocate new memory.
		new_attrs = new decl_attribute;
	}
	// Enqueue the name of new attribute.
	new_attrs->d_names.push_back (name);
	if (new_attrs->d_names.size () == 1)
	{
		// First attribute name.
		// Setting default values.
		new_attrs->d_mod_type = k_synthetize;
		new_attrs->d_member_symbol = "\0";
	}
}

void save_sort_attr (char const* str, char const* end)
{
	string sort (str, end);
	new_attrs->d_sort_type = sort;
}

void save_type_attr (char const* str, char const* end)
{
	string mod_type (str, end);
	if (mod_type.compare ("inh") == 0)
		new_attrs->d_mod_type = k_inherit;
}

void save_member_list (char const* str, char const* end)
{
	string members (str, end);
	boost::erase_all (members, " ");
	new_attrs->d_member_symbol = members;
}

void save_decl_attrs (char const* str, char const* end)
{
	for (vector<string>::size_type i = 0; i < new_attrs->d_names.size (); i++)
	{
		Attribute attr;
		attr.set_name (new_attrs->d_names[i]);
		attr.set_sort_type (&(sem_domain.return_sort (new_attrs->d_sort_type)));
		attr.set_mod_type (new_attrs->d_mod_type);
		attr.set_member_symbol (new_attrs->d_member_symbol);
		sem_domain.add_attribute (attr);
	}
	// Free space memory and assign NULL at pointer.
	free (new_attrs);
	new_attrs = NULL;
}

/**
  * Methods and functions for parse Symbol class.
  */
void save_non_terminal (char const* str, char const* end)
{
	string name (str, end);
	Symbol symb (name, k_non_terminal);
	sem_domain.add_symbol (symb);
}

void save_terminal (char const* str, char const* end)
{
	string name (str, end);
	// The string is 'char'
	Symbol symb (name, k_terminal);
	sem_domain.add_symbol (symb);
}

/**
  * Methods and functions for parse Rule class.
  */
/**
  * Pointer that reference a current rule parsed in the grammar.
  */
Rule * current_rule;

void save_rule (char const* str, char const* end)
{
	sem_domain.add_rule (*current_rule);
	// Call destruction before free memory.
	current_rule->Rule::~Rule ();
	free (current_rule);

}

void add_left_symbol_rule (char const* str, char const* end)
{
	string left_side_symbol (str, end);
	current_rule = new Rule ();
	current_rule->set_left_symbol (&(sem_domain.get_symbol (left_side_symbol)));
}

void add_right_side_rule (char const* str, char const* end)
{
	string right_side_symbol (str, end);
	current_rule->add_right_symbol (&(sem_domain.get_symbol (right_side_symbol)));
}

void abbreviated_rule (char const* str, char const* end)
{
	current_rule = new Rule ();
	current_rule->set_left_symbol (current_rule->get_left_symbol ());
}

/**
  * Methods and functions for parse Equation class of Rule.
  */

/**
  * Pointer to the last instance of attribute to parse successfully.
  */
instance_attr* current_instance;
literal_node* current_literal;

Equation * current_eq;
tree<node_ast> current_tree;

node_ast *current_node;

/*********************************************************************/
void print_tree(tree<node_ast>& tr, tree<node_ast>::pre_order_iterator it, tree<node_ast>::pre_order_iterator end)
   {
   //if(!tr.is_valid(it)) return;
   int rootdepth=tr.depth(it);
   cout << "-----" << endl;
   while(it!=end) {
      for(int i=0; i<tr.depth(it)-rootdepth; ++i)
         cout << "  ";
//       std::cout << current_eq->print_literal(*it) << std::endl << std::flush;
		  switch (it->n_type_node)
			{
				case k_intance: cout << current_eq->print_instance(*(it->n_data.instance)) << endl;	break;
				case k_literal:	cout<< current_eq->print_literal(*(it->n_data.literal))<< endl;	break;
				case k_operator:case k_function:;
			 }
      ++it;
      }
   std::cout << "-----" << std::endl;
   }

void prueba()
{
	tree<node_ast> tr9;
	literal_node node1;
	node1.value_lit.int_l=3;
	node1.type_lit = k_int;
	node_ast n1;
	n1.n_data.literal = new literal_node;
	*(n1.n_data.literal) = node1;
	n1.n_type_node = k_literal;
	tr9.set_head(n1);

	instance_attr ins1;
	ins1.i_symb = &(sem_domain.get_symbol("E"));
	ins1.i_num = 9;
	ins1.i_attr = ins1.i_symb->get_attribute("valor");
	node_ast n4;
	n4.n_data.instance = new instance_attr;
	n4.n_data.instance = &ins1;
	n4.n_type_node = k_intance;
	tr9.insert(tr9.begin().begin(), n4);

	literal_node node2;
	node2.value_lit.ch_l='A';
	node2.type_lit = k_char;
	node_ast n2;
	n2.n_data.literal = new literal_node;
	*(n2.n_data.literal) = node2;
	n2.n_type_node = k_literal;
	tr9.insert(tr9.begin().begin(), n2);
	literal_node node3;
	node3.value_lit.flt_l=3.13;
	node3.type_lit = k_float;
	node_ast n3;
	n3.n_data.literal = new literal_node;
	*(n3.n_data.literal) = node3;
	n3.n_type_node = k_literal;
	tr9.insert(tr9.begin().begin().begin(), n3);

	print_tree(tr9, tr9.begin(), tr9.end());

}
////////////////////////////////////////////////////////////////////////////////////////***

////////////////////////////////////////////////////////////////////////////////////////***
void inic_tree(char const chr)
{
//	current_tree = new tree<node_ast>;
	literal_node node1;
	node1.value_lit.int_l=3;
	node1.type_lit = k_int;
	node_ast n1;
	n1.n_data.literal = new literal_node;
	*(n1.n_data.literal) = node1;
	n1.n_type_node = k_literal;
	current_tree.set_head(n1);
}

void save_node_tree()
{
	current_tree.insert(current_tree.begin().begin(),*current_node);
//	current_node = NULL;
}

void save_literal_tree()
{
	current_node = new node_ast;
	current_node->n_data.literal = current_literal;
	current_node->n_type_node = k_literal;
	// falta type synthetize
	save_node_tree();
	//cout << current_eq->print_literal(*current_literal) << endl;

	current_node = NULL;
}

void save_symb_ins (char const* str, char const* end)
{
	string symb (str, end);
	if (current_instance == NULL)
	{
		current_instance = new instance_attr;
	}
	current_instance->i_symb = &(sem_domain.get_symbol(symb));
}

void save_index_ins (int const index)
{
	current_instance->i_num = index;
}

void save_attr_ins (char const* str, char const* end)
{
	string attr (str, end);
	if ((current_instance->i_attr = current_instance->i_symb->get_attribute(attr)) == NULL)
	{
		cerr << "ERROR: Atribute inexistente. Verifique los atributos usados en los symbolos." << endl;
		exit(1);
	}

	current_node = new node_ast;
	current_node->n_data.instance = current_instance;
	current_node->n_type_node = k_intance;
	save_node_tree();
	current_node = NULL;
}

void save_lit_int (int const int_lit)
{
	if (current_literal == NULL)
	{
		current_literal = new literal_node;
	}
	current_literal->type_lit = k_int;
	current_literal->value_lit.int_l = int_lit;
	save_literal_tree();
}

void save_lit_flt (double const flt_lit)
{
	if (current_literal == NULL)
	{
		current_literal = new literal_node;
	}
	current_literal->type_lit = k_float;
	current_literal->value_lit.flt_l = flt_lit;
	save_literal_tree();
}

void save_lit_ch (char const* ch, char const* end)
{
	if (current_literal == NULL)
	{
		current_literal = new literal_node;
	}
	string ch_l(ch,end);
	current_literal->type_lit = k_char;
	current_literal->value_lit.ch_l = ch_l.at(1);
	save_literal_tree();
}

void save_lit_str (char const* str, char const* end)
{
	if (current_literal == NULL)
	{
		current_literal = new literal_node;
	}
	string str_l (str+1, end-1); // the pointer +1 and -1 for remove the double quotes.Ex: "uno" --> uno.
	current_literal->type_lit = k_string;
	current_literal->value_lit.str_l = new string(str_l);
	save_literal_tree();
}

void save_lvalue (char const* str, char const* end)
{
	current_eq = new Equation();
	current_eq->set_l_value(*current_instance);
	free(current_instance);
	current_instance = NULL;
}

void save_rvalue (char const* str, char const* end)
{
//	string full_exp (str, end);
//	cout << full_exp << endl;

	current_eq->set_r_value(current_tree);

	current_rule->add_eq(*current_eq);

//	free(current_tree);
//	current_tree = NULL;
	print_tree(current_tree,current_tree.begin(),current_tree.end());
	current_tree.clear();
	free(current_eq);

}


void pepito (char const* str, char const* end)
{
	string pepe (str, end);
	cout << pepe << endl;
}


/**
  * Declaration of a parser for imputs that ignore within
  * an Attribute Grammar file, with the Spirit library of Boost.
  */
struct skip_parser: public grammar<skip_parser>
{
	template <typename ScannerT>
	struct definition
	{
		definition (skip_parser const &self)
		{
			skip = space_p
                 | "//" >> *(anychar_p - '\n') >> '\n'
                 | "/*" >> *(anychar_p - "*/") >> "*/"
                 ;
		}
		rule<ScannerT> skip;
		rule<ScannerT> const& start () const { return skip; }
	};
};

/**
  * Declaration struct for sinthetize type expression.
  * Use rule with context: "Closures".
  * Reference: http://www.boost.org/doc/libs/1_33_1/libs/spirit/example/fundamental/phoenix_calc.cpp
  */
struct type_expression: BOOST_SPIRIT_CLASSIC_NS::closure<type_expression, string>
{
	member1 type;
};

/**
  * Declaration of the Attribute Grammar structure
  * with the Spirit library of Boost.
  */
struct attr_grammar: public grammar<attr_grammar, type_expression::context_t>
{
	template <typename ScannerT>
	struct definition
	{
		definition (attr_grammar const &self)
		{
			// Common declarations.

			r_ident			= lexeme_d[ (alpha_p | '_') >> *(alnum_p | '_' ) ] - r_reserved_word;

			r_oper			= lexeme_d[ (alpha_p | '_' | r_id_op) >> *(alnum_p | '_' | r_id_op) ];

			r_id_op			= ch_p ('+')|'*'|'/'|'^'|'%'|'&'|'<'|'='|'-'|'>';

			r_char			= lexeme_d[ ch_p ('\'') >>  (alnum_p | r_id_op) >> ch_p ('\'') ];

			r_string		= lexeme_d[ ch_p ('\"') >> +(alnum_p | r_id_op) >> ch_p ('\"') ];

//            string =
//                    +( (anychar_p - chset<>("\"\\")) | escseq )
//                ;
//
//            escseq =
//                    ch_p('\\')
//                    >>  (
//                            oct_parser_t()
//                        |   as_lower_d['x'] >> hex_parser_t()
//                        |   (anychar_p - chset<>('\n'))
//                        )
//                ;

			r_reserved_word = strlit<> ("compute") | strlit<> ("COMPUTE") |
							  strlit<> ("all")     | strlit<> ("ALL");

			/**
			  * Declaration of Semantic Domain.
			  */

			r_semantic_domain = lexeme_d[ strlit<> ("semantic domain") >> space_p ] >> +r_bloq_sem;

			r_bloq_sem		  = r_decl_sort | r_decl_oper[&add_operator] | r_decl_func[&add_function];

			// Declaration of Sorts.

			r_decl_sort		  = lexeme_d[ strlit<> ("sort") >> space_p ] >>
								r_ident[&add_sort][st_sorts.add] >> *(',' >> r_ident[&add_sort]) >> ';';

			// Declaration of Operators.

			r_decl_oper    = lexeme_d[ strlit<> ("op") >> space_p ] >>
						     (r_oper_infix | r_oper_postfix | r_oper_prefix) >>
						     strlit<> ("->") >>
						     r_sort_st[&save_image_op] >> ';';

			r_oper_infix   = strlit<> ("infix")[&save_mode_op] >> !r_oper_mode >>
							 r_oper[&save_name_op][st_op_infix.add] >> ':' >>
							 r_sort_st[&save_domain_op] >> ',' >> r_sort_st[&save_domain_op];

			r_oper_postfix = strlit<> ("postfix")[&save_mode_op] >> !r_oper_mode >>
							 r_oper[&save_name_op][st_op_postfix.add] >> ':' >>
							 r_sort_st[&save_domain_op];

			r_oper_prefix  = !(strlit<> ("prefix")[&save_mode_op]) >> !r_oper_mode >>
							 r_oper[&save_name_op][st_op_prefix.add] >> ':' >>
							 r_sort_st[&save_domain_op];

			r_oper_mode	   = '(' >> (uint_p[&save_prec_op] | '_') >> ',' >> (r_oper_assoc[&save_assoc_op] | '_') >> ')';

			r_oper_assoc   = strlit<> ("left") | strlit<> ("right") | strlit<> ("non-assoc");

			// Declaration of Functions.

			r_decl_func	   = lexeme_d[strlit<> ("function")>> space_p ] >>
							 r_oper[&save_name_func][st_functions.add] >> ':' >>
							 r_dom_func >> strlit<> ("->") >>
							 r_sort_st[&save_image_func] >> ';';

			r_dom_func	   = r_sort_st[&save_domain_func] >> *(',' >> r_sort_st[&save_domain_func]);

			/**
			  * Declaration of Attributes.
			  */
			r_attributes = lexeme_d[strlit<> ("attributes")>> space_p ] >> +r_decl_attr[&save_decl_attrs];

			r_decl_attr  = r_ident[&add_attr][st_attributes.add] >> *(',' >> r_ident[&add_attr][st_attributes.add]) >>
					       ':' >> !(r_type_attr[&save_type_attr]) >> '<' >> r_sort_st[&save_sort_attr] >> '>' >>
					       lexeme_d[strlit<> ("of")>> space_p ] >>
					       (r_conj_symb |
					       (strlit<> ("all") >> !('-' >> r_conj_symb)))[&save_member_list] >> ';';

			r_conj_symb	 = '{' >> r_ident >> *(',' >> r_ident) >> '}';

			r_type_attr  = (strlit<> ("inh") | strlit<> ("syn"));

			/**
			  * Declaration of Rules.
			  */

			r_rules		  = lexeme_d[strlit<> ("rules")>> space_p ] >> +r_decl_rule;

			r_decl_rule	  = r_ident[&save_non_terminal][&add_left_symbol_rule][st_symbols.add] >>
						    strlit<> ("::=") >>
						    r_right_rule[&save_rule] >>
						    *(strlit<> ("|")[&abbreviated_rule] >> r_right_rule[&save_rule]) >> ';';

			r_right_rule  = +(  r_ident[&save_non_terminal][st_symbols.add]
			                  | r_char[&save_terminal]
			                 )[&add_right_side_rule] >>
						    !(strlit<> ("compute") >>
						        +(r_equation) >>
						      strlit<> ("end")
						     );

			r_equation	  = r_left_symbol[&save_lvalue] >> ch_p('=')[&inic_tree] >> r_right_side[&save_rvalue] >> ';';

			r_left_symbol = r_instance;

			r_right_side  = r_expression;

			/**
			  * expression's Grammar non ambiguos based in
			  *
			  * 	E = T *(<op_infix> T)
			  *		T = F *(<op_postfix>)
			  *		F = +(<op_prefix>) E | (E) | function | literal | instance
			  */
			r_expression 		= r_expr_prime >> *(r_op_infix_st[&save_name_op] >> r_expr_prime)[r_expression.type=arg1]
								;

			r_expr_prime		= r_expr_prime_prime >> *(r_op_postfix_st[&save_name_op])[r_expr_prime.type=arg1]
								;

			r_expr_prime_prime  = +(r_op_prefix_st[&save_name_op]) >> r_expression
								| '('>> r_expression >>')'
								| r_function
								| r_literal
								| r_instance[r_expr_prime_prime.type=arg1]
								;

			/**
			  * The functions accept a list of expressions.
			  */
			r_function			= r_function_st[&save_name_func] >> '(' >> r_expression >> *(',' >> r_expression) >> ')';

			/**
			  * Literals accepted: Integer and Float numbers, characters and string,
			  * between signs ' and " respectively.
			  */
			r_literal			= int_p[&save_lit_int] | real_p[&save_lit_flt]
			         			| r_char[&save_lit_ch] | r_string[&save_lit_str];

			/**
			  * An instance is, the symbol with the number of occurrences in square brackets within
			  * the rule, with the specific attribute with which it operates.
			  *
			  * Example: E[0].value
			  */
			r_instance			= lexeme_d[ r_symbol_st[&save_symb_ins] >>
			          			            '[' >> int_p[&save_index_ins] >> ']' >>
			          			            '.' >> r_attribute_st[&save_attr_ins][r_instance.type="hola"]
			          			          ];

			/**
			  * Declaration of Attribute Grammar.
			  */
			r_att_grammar = r_semantic_domain >> r_attributes >> r_rules >> end_p ;

			/**
			  * Parsers based in the symbol tables.
			  */
			r_sort_st		= st_sorts;
			r_op_prefix_st	= st_op_prefix;
			r_op_infix_st	= st_op_infix;
			r_op_postfix_st	= st_op_postfix;
			r_function_st	= st_functions;
			r_attribute_st	= st_attributes;
			r_symbol_st		= st_symbols;

		}
		/**
		  * Table of Symbols for the elements of an Attribute Grammar.
		  */
		symbols <> st_sorts;
		symbols <> st_op_prefix;
		symbols <> st_op_infix;
		symbols <> st_op_postfix;
		symbols <> st_functions;
		symbols <> st_attributes;
		symbols <> st_symbols;

//		void pepito2()
//		{
//			cout << r_expression.type << endl;
//			cout << r_instance.type << endl;
//		}
		/**
		  * Variables using in parsing time.
		  */
		rule<ScannerT> r_reserved_word, r_ident, r_oper, r_char, r_string;

		rule<typename lexeme_scanner<ScannerT>::type> r_id_op; // rule in lexeme_d.

		// Semantic domain's rule: Sort, Operator and Function.
		rule<ScannerT> r_semantic_domain, r_bloq_sem, r_decl_sort, r_decl_oper, r_decl_func,
					   r_oper_assoc, r_oper_mode, r_oper_prefix, r_oper_infix, r_oper_postfix,
					   r_dom_func;

		// Atribute's rule.
		rule<ScannerT> r_attributes, r_decl_attr, r_type_attr, r_conj_symb;

		// Rule's rule.
		rule<ScannerT> r_rules, r_decl_rule, r_equation, r_left_symbol, r_right_side, r_right_rule;

		// Expresion's rule: Compute. Add context for type expresion.
		typedef rule<ScannerT, type_expression::context_t> rule_exp;

		rule_exp r_expression,  r_expr_prime, r_expr_prime_prime, r_function, r_literal, r_instance;

		// Main rule.
		rule<ScannerT> r_att_grammar;

		// Translate for symbol table.
		rule<ScannerT> r_sort_st, r_op_prefix_st, r_op_infix_st, r_op_postfix_st,
					   r_function_st, r_attribute_st, r_symbol_st;

		rule<ScannerT> const& start () const { return r_att_grammar; }
	};
};


/**
  * This method invokes the method 'parse' of the library Spitir included in Boost.
  * Returns true if could parse all the input.
  */
bool parse_grammar (char const* txt_input)
{
	attr_grammar attribute_grammar;
	skip_parser skip_p;

	#ifdef _DEBUG
		cout << (parse(txt_input, attribute_grammar, skip_p)).stop << endl;
	#endif
	return (parse(txt_input, attribute_grammar, skip_p)).full;
}

/**
  * Reads the contents of the file and save it in the
  * string passed as parameter.
  */
void read_file_in(string & txt_output)
{
	FILE * p_file;
	char buffer[MAX_INPUT_FILE];

	p_file = fopen (PATH_INPUT_FILE , "r");
	if (p_file == NULL)
		perror ("Error opening file");
	else
	{
		while ( !feof (p_file) )
		{
	          fgets (buffer , MAX_INPUT_LINE , p_file);
	          txt_output += buffer;
	    }
		fclose (p_file);
	}
}

/**
  * Main method of the parsing.
  */
int main ()
{
	string input_grammar;
	read_file_in(input_grammar);
	cout << "-------------------------\n";



	if (parse_grammar (input_grammar.c_str ()))
	{
		cout << sem_domain.to_string ();
		cout << "-------------------------\n";
		cout << "Parsing OK\n";
		prueba();
    }
	else
	{
		cout << "Parsing failed\n";
	}
	cout << "-------------------------\n";
    cout << "Bye... :-D" << endl;
    return 0;
}
