/**
  *  \file		Parser.cpp
  *  \brief		Parsing module of Attribute Grammar.
  *  \date		13/09/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */



#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_symbols.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <stdio.h>
#include <iostream>
#include <string>

#include "SemDomain.h"

using namespace std;
using namespace BOOST_SPIRIT_CLASSIC_NS;
using namespace genevalmag;

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
Operator * new_oper;

void add_operator (char const* str, char const* end)
{
	sem_domain.add_operator (*new_oper);
	// Call destruction before free memory.
	new_oper->Operator::~Operator ();
	free (new_oper);
}

void inic_operator (char const* str, char const* end)
{
	// Ignore the string parsed.
	new_oper = new Operator ();
}

void save_name_op (char const* str, char const* end)
{
	string name (str, end);
	new_oper->set_name (name);
}

void save_mode_op (char const* str, char const* end)
{
	string mode (str, end);
	new_oper->set_mode (mode);
}

void save_prec_op (int const prec)
{
	new_oper->set_prec (prec);
}

void save_assoc_op (char const* str, char const* end)
{
	string assoc (str, end);
	new_oper->set_oper_assoc (assoc);
}

void save_domain_op (char const* str, char const* end)
{
	string domain (str, end);
	new_oper->add_domain (&(sem_domain.return_sort (domain)));
}

void save_image_op (char const* str, char const* end)
{
	string image (str, end);
	new_oper->set_image (&(sem_domain.return_sort (image)));
}

/**
  * Methods and functions for parse Function class.
  */
/**
  * Pointer that reference a new function in the grammar.
  */
Function * new_func;

void inic_function (char const* str, char const* end)
{
	new_func = new Function ();
}

void add_function (char const* str, char const* end)
{
	sem_domain.add_function (*new_func);
	// Call destruction before free memory.
	new_func->Function::~Function ();
	free (new_func);
}

void save_name_func (char const* str, char const* end)
{
	string name (str, end);
	new_func->set_name (name);
}

void save_domain_func (char const* str, char const* end)
{
	string domain (str, end);
	new_func->add_domain (&(sem_domain.return_sort (domain)));
}

void save_image_func (char const* str, char const* end)
{
	string image (str, end);
	new_func->set_image (&(sem_domain.return_sort (image)));
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
		new_attrs->d_mod_type = k_syntetize;
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
void add_op_exp (char const* str, char const* end)
{
	string name_op (str, end);
	// Operator* op = &(sem_domain.get_operation (name_op));
	// cout << op->get_name () << endl;
	cout << "op " << name_op << endl;
}

void pepito (char const* str, char const* end)
{
	string pepe (str, end);
	cout << pepe << endl;
}

void oper_table (char const* str, char const* end)
{
	string name_op (str, end);
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
  * Declaration of the Attribute Grammar structure
  * with the Spirit library of Boost.
  */
struct attr_grammar: public grammar<attr_grammar>
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

			r_reserved_word = strlit<> ("compute") | strlit<> ("COMPUTE") |
							  strlit<> ("all")     | strlit<> ("ALL");

			/**
			  * Declaration of Semantic Domain.
			  */

			r_semantic_domain = lexeme_d[ strlit<> ("semantic domain") >> space_p ] >> +r_bloq_sem;

			r_bloq_sem		  = r_decl_sort | r_decl_oper[&add_operator] | r_decl_func[&add_function];

			// Declaration of Sorts.

			r_decl_sort = lexeme_d[strlit<> ("sort")>> space_p ] >> r_ident[&add_sort][st_sorts.add] >> *(',' >> r_ident[&add_sort]) >> ';';

			// Declaration of Operators.

			r_decl_oper    = lexeme_d[strlit<> ("op")[&inic_operator]>> space_p ] >>
						   (r_oper_infix | r_oper_postfix | r_oper_prefix) >>
						   strlit<> ("->") >>
						   r_sort[&save_image_op] >> ';';

			r_oper_infix   = strlit<> ("infix")[&save_mode_op]>> !r_oper_mode
						   >> r_oper[&save_name_op][st_op_infix.add]
						   >> ':' >> r_sort[&save_domain_op] >> ',' >> r_sort[&save_domain_op];

			r_oper_postfix = strlit<> ("postfix")[&save_mode_op]	>> !r_oper_mode
						   >> r_oper[&save_name_op][st_op_postfix.add]
						   >> ':' >> r_sort[&save_domain_op];

			r_oper_prefix  = !(strlit<> ("prefix")[&save_mode_op]) >> !r_oper_mode
						   >> r_oper[&save_name_op][st_op_prefix.add]
						   >> ':' >> r_sort[&save_domain_op];

			r_oper_mode	   = '(' >> (uint_p[&save_prec_op] | '_') >> ',' >> (r_oper_assoc[&save_assoc_op] | '_') >> ')';

			r_oper_assoc   = strlit<> ("left") | strlit<> ("right") | strlit<> ("non-assoc");

			r_sort		   = st_sorts;

			// Declaration of Functions.

			r_decl_func		  = lexeme_d[strlit<> ("function")[&inic_function]>> space_p ] >>
								r_oper[&save_name_func][st_functions.add] >> ':' >>
							    r_dom_func >> strlit<> ("->") >>
							    r_sort[&save_image_func] >> ';';

			r_dom_func		  = r_sort[&save_domain_func] >> *(',' >> r_sort[&save_domain_func]);

			/**
			  * Declaration of Attributes.
			  */
			r_attributes = lexeme_d[strlit<> ("attributes")>> space_p ] >> +r_decl_attr[&save_decl_attrs];

			r_decl_attr  = r_ident[&add_attr][st_attributes.add] >> *(',' >> r_ident[&add_attr][st_attributes.add]) >>
					       ':' >> !(r_type_attr[&save_type_attr]) >> '<' >> r_sort[&save_sort_attr] >> '>' >>
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
						        +(r_sem_expr) >>
						      strlit<> ("end")
						     );

			r_sem_expr	  = r_left_symbol >> '=' >> r_right_side >> ';';

			r_left_symbol = r_instance;

			r_right_side  = r_expresion;

			/**
			  * Expresion's Grammar non ambiguos based in
			  *
			  * 	E = T <op_infix> E | T
			  *		T = F <op_postfix> | F
			  *		F = (E) | <symb_base>
			  */
			r_expresion 		= r_expr_prime >> st_op_infix >> r_expresion
								| r_expr_prime
								;

			r_expr_prime		= r_expr_prime_prime >> st_op_postfix
								| r_expr_prime_prime
								;


			r_expr_prime_prime  = st_op_prefix >> r_expresion
								| '('>> r_expresion >>')'
								| r_function
								| r_instance
								| r_literal
								;

			/**
			  * The functions accept a list of expressions.
			  */
			r_function			= st_functions >> '(' >> r_expresion >> *(',' >> r_expresion) >> ')';

			/**
			  * Literals accepted: Integer and Float numbers, characters and string,
			  * between signs ' and " respectively.
			  */
			r_literal			= int_p | real_p | r_char | r_string;

			/**
			  * An instance is, the symbol with the number of occurrences in square brackets within
			  * the rule, with the specific attribute with which it operates.
			  *
			  * Example: E[0].value
			  */
			r_instance			= lexeme_d[ st_symbols >> '[' >> int_p >> ']' >> '.' >> st_attributes ];

			/**
			  * Declaration of Attribute Grammar.
			  */
			r_att_grammar = r_semantic_domain >> r_attributes >> r_rules >> end_p;
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

		/**
		  * Variables using in parsing time.
		  */
		rule<ScannerT> r_reserved_word, r_ident, r_oper, r_id_op, r_char, r_string;

		rule<ScannerT> r_semantic_domain, r_bloq_sem, r_decl_sort, r_decl_oper, r_decl_func, r_sort,
					   r_oper_assoc, r_oper_mode, r_oper_prefix, r_oper_infix, r_oper_postfix,
					   r_dom_func;

		rule<ScannerT> r_attributes, r_decl_attr, r_type_attr, r_conj_symb;

		rule<ScannerT> r_rules, r_decl_rule, r_sem_expr, r_left_symbol, r_right_side, r_instance, r_right_rule;

		rule<ScannerT> r_expresion, r_function, r_literal, r_expr_prime, r_expr_prime_prime;

		rule<ScannerT> r_att_grammar;

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
	return (parse (txt_input, attribute_grammar, skip_p)).full;
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

	cout << "-------------------------";
    if (parse_grammar (input_grammar.c_str ()))
	{
		cout << sem_domain.to_string ();
		cout << "-------------------------\n";
		cout << "Parsing OK\n";
    }
	else
	{
		cout << "Parsing failed\n";
	}
	cout << "-------------------------\n";
    cout << "Bye... :-D" << endl;
    return 0;
}
