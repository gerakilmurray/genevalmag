/**
  *  \file Parser.cpp
  *      \brief Parsing module.
  *  \date 13/09/2009
  *  \author    Kilmurray, Gerardo Luis.
  *  \author    Picco, Gonzalo Martín.
  */

#include <boost/spirit/include/classic_core.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "SemDomain.h"

using namespace std;
using namespace BOOST_SPIRIT_CLASSIC_NS;
using namespace genevalmag;

#define MAX_INPUT_LINE 100

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

void pepito(char const* str, char const* end)
{
//	string pepe(str, end);
//	cout << pepe << endl;
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
			r_ident = lexeme_d[(alpha_p | '_') >> *(alnum_p | '_' )] - r_reserved_word;

			r_reserved_word = strlit<>("compute")|strlit<>("COMPUTE")|
							  strlit<>("all")|strlit<>("ALL");

			r_oper  = lexeme_d[(alpha_p | '_' | r_id_op) >> *(alnum_p | '_' | r_id_op)];

			r_id_op = ch_p ('+')|'*'|'/'|'^'|'%'|'&'|'<'|'='|'-'|'>';

			r_char	= lexeme_d[ch_p('\'')>> (alnum_p | r_id_op) >> ch_p('\'')];

			////////////////////////////////////////////////////////////
			// Grammar's Semantic Domain
			////////////////////////////////////////////////////////////

			r_semantics = strlit<>("semantics domains")>> +bloq_sem;

			bloq_sem    = decl_op[&add_op] | decl_sort;

			decl_sort   = strlit<>("sort ") >> r_ident[&add_sort] >> *(',' >> r_ident[&add_sort]) >> ';';

			decl_op     = strlit<>("op ")[&inic_op] >>
						  !(mod_op[&save_mod]) >>
						  !('(' >> int_p[&save_pred] >> ')') >>
						  r_oper[&save_name] >> ':' >>
						  dom_op >> strlit<>("->") >>
						  r_ident[&save_img]  >> ';';

			dom_op      = r_ident[&save_dom] >> *(',' >> r_ident[&save_dom]);

			mod_op      = strlit<>("infix") | strlit<>("prefix") | strlit<>("sufix");

			////////////////////////////////////////////////////////////
			// Grammar's Attribute
			////////////////////////////////////////////////////////////

			r_attributes = strlit<>("attributes")>> +decl_att[&save_decl_attrs];

			decl_att     = r_ident[&add_attr] >> *(',' >> r_ident[&add_attr]) >>
					       ':' >> !(r_type_att[&save_type_attr]) >> '<' >> r_ident[&save_sort_attr] >> '>' >>
					       strlit<>("of") >>
					       (conj_simb |
					       (strlit<>("all") >> !('-' >> conj_simb)))[&save_member_list] >> ';';

			conj_simb 	 = '{' >> r_ident >> *(',' >> r_ident) >> '}';

			r_type_att   = (strlit<>("inh") | strlit<>("syn"));

			////////////////////////////////////////////////////////////
			// Grammar's Rule
			////////////////////////////////////////////////////////////

			r_rules		= strlit<>("rules") >> (+decl_rule);

			decl_rule	= r_ident[&save_non_terminal][&add_left_side_rule] >>
						  strlit<>("::=") >> r_right_rule[&save_rule] >>
						  *(strlit<>("|")[&abbreviated_rule] >> r_right_rule[&save_rule]) >> ';';

			r_right_rule =  +( r_ident[&save_non_terminal]
			                 | r_char[&save_terminal])[&add_right_side_rule] >>
						    !( strlit<>("compute") >>
							   +(r_sem_expr[&pepito]) >>
							   strlit<>("end")
							  );

			r_sem_expr	= left_side >> '=' >> right_side >> ';';

			left_side	= r_att_sem;

			right_side	= +(r_att_sem | r_id_op) ;

			r_att_sem	= lexeme_d[ r_ident >> '[' >> int_p >> ']' >> '.' >> r_ident ];

			////////////////////////////////////////////////////////////
			// Attribute Grammar
			////////////////////////////////////////////////////////////

			r_att_grammar = r_semantics >> r_attributes >> r_rules >> end_p;
		}

		rule<ScannerT> r_ident, r_oper, r_id_op, r_char,r_reserved_word;

		rule<ScannerT> r_semantics, bloq_sem, decl_sort, decl_op, dom_op,mod_op;
		rule<ScannerT> r_attributes, decl_att, r_type_att, conj_simb;
		rule<ScannerT> r_rules, decl_rule, r_sem_expr, left_side, right_side, r_att_sem,r_right_rule;

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
	char buffer[MAX_INPUT_LINE];
	string texto;

	p_file = fopen ("./src/grammar.txt" , "r");
	if (p_file == NULL)
		perror ("Error opening file");
	else
	{
		while ( !feof (p_file) )
		{
	          fgets (buffer , 128 , p_file);
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
