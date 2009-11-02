/**
  *  \file Parser.cpp
  *      \brief Example of Spirit Librarie.
  *  \date 13/09/2009
  *  \author    Kilmurray, Gerardo Luis.
  *  \author    Picco, Gonzalo Martín.
  */

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_push_back_actor.hpp>
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

// a new operator in the parser
Operator * new_op;

///////////////////////////////////////////////
// Operation for Sort
///////////////////////////////////////////////
void addSort (char const* str, char const* end)
{
    string  s(str, end);
	Sort sort(s);
	sem_domain.add_sort(sort);
}

///////////////////////////////////////////////
// Operation for Operation
///////////////////////////////////////////////
void inicOp (char const* str, char const* end)
{
	new_op = new Operator();
}

void addOp (char const* str, char const* end)
{
	if (!sem_domain.add_op(*new_op))
		// operation repeat.
	{
		free(new_op); // free memory of operation repeat.
	}
}

void saveMod (char const* str, char const* end)
{
	string  s(str, end);
	new_op->setMod(s);
}

void savePred (int const i)
{
	new_op->setPred(i);
}

void saveName (char const* str, char const* end)
{
	string  s(str, end);
	new_op->setName(s);
}

void saveDom (char const* str, char const* end)
{
	string  s(str, end);
	new_op->add_domain(sem_domain.get_sort(s));
}

void saveImg (char const* str, char const* end)
{
	string  s(str, end);
	new_op->setImage(sem_domain.get_sort(s));
}

///////////////////////////////////////////////
// Operation for Attributes
///////////////////////////////////////////////
struct decl_attr
{
	vector<string> names;
	string sort_type;
	TipeAttr mod_type;
	string member_symbol;
} * new_atts;

void addAttrib (char const* str, char const* end)
{
	string name(str, end);
	if (new_atts == NULL)
	{
		// New declaration. Must be allocate new memory.
		new_atts = new decl_attr;
	}
	// The declaration has more of one attribute

	// Save name of new attribute
	new_atts->names.push_back(name);
	if (new_atts->names.size() == 1){
		new_atts->mod_type = kSyntetize; // Default value
		new_atts->member_symbol = "\0";
	}
}

void saveSortAtts (char const* str, char const* end)
{
	string sort(str, end);
	new_atts->sort_type = sort;
}

void saveTypeAtts (char const* str, char const* end)
{
	string mod_type(str, end);
	if (mod_type.compare("inh") == 0)
		new_atts->mod_type = kInherit;
}

void saveMemberList (char const* str, char const* end)
{
	string members(str, end);
	boost::erase_all(members, " ");
	new_atts->member_symbol = members;
}

void saveDeclAtts (char const* str, char const* end)
{
	for (vector<string>::size_type i = 0; i < new_atts->names.size(); i++)
	{
		Attribute * att = new Attribute(
								new_atts->names[i],
								new_atts->sort_type,
								new_atts->mod_type,
								new_atts->member_symbol
							 );
		if (!sem_domain.add_att(*att))
		{
			// Attribute repeat.
			free(att); // free memory of attribute repeat.
		}
	}
	// Free space memory and assign NULL at pointer.
	free(new_atts);
	new_atts = NULL;
}

///////////////////////////////////////////////
// Operation for Attributes
///////////////////////////////////////////////
void pepito(char const* str, char const* end)
{
	string pepe(str, end);
    cout << pepe << endl;
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

			r_reserved_word = strlit<>("compute")|strlit<>("COMPUTE");

			r_oper  = lexeme_d[(alpha_p | '_' | r_id_op) >> *(alnum_p | '_' | r_id_op)];

			r_id_op = ch_p ('+')|'*'|'/'|'^'|'%'|'&'|'<'|'='|'-'|'>';

			r_char	= lexeme_d[ch_p('\'')>> (alnum_p | r_id_op) >> ch_p('\'')];

			////////////////////////////////////////////////////////////
			// Grammar's Semantic Domain
			////////////////////////////////////////////////////////////

			r_semantics = strlit<>("semantics domains")>> +bloq_sem;

			bloq_sem    = decl_op[&addOp] | decl_sort;

			decl_sort   = strlit<>("sort ") >> r_ident[&addSort] >> *(',' >> r_ident[&addSort]) >> ';';

			decl_op     = strlit<>("op ")[&inicOp] >>
						  !(mod_op[&saveMod]) >>
						  !('(' >> int_p[&savePred] >> ')') >>
						  r_oper[&saveName] >> ':' >>
						  dom_op >> strlit<>("->") >>
						  r_ident[&saveImg]  >> ';';

			dom_op      = r_ident[&saveDom] >> *(',' >> r_ident[&saveDom]);

			mod_op      = strlit<>("infix") | strlit<>("prefix") | strlit<>("sufix");

			////////////////////////////////////////////////////////////
			// Grammar's Attribute
			////////////////////////////////////////////////////////////

			r_attributes = strlit<>("attributes")>> +decl_att[&saveDeclAtts];

			decl_att     = r_ident[&addAttrib] >> *(',' >> r_ident[&addAttrib]) >>
					       ':' >> !(r_type_att[&saveTypeAtts]) >> '<' >> r_ident[&saveSortAtts] >> '>' >>
					       strlit<>("of") >>
					       (conj_simb |
					       (strlit<>("all") >> !('-' >> conj_simb)))[&saveMemberList] >> ';';

			conj_simb 	 = '{' >> r_ident >> *(',' >> r_ident) >> '}';

			r_type_att   = (strlit<>("inh") | strlit<>("syn"));

			////////////////////////////////////////////////////////////
			// Grammar's Rule
			////////////////////////////////////////////////////////////

			r_rules		= strlit<>("rules") >> (+decl_rule);

			decl_rule	= r_ident[&pepito] >> strlit<>("::=") >>
						  r_right_rule >> *('|'>> r_right_rule) >> ';';

			r_right_rule =  +(r_ident[&pepito] | r_char[&pepito]) >>
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
		rule<ScannerT> r_attributes, decl_att, r_type_att,conj_simb;
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
	return parse(str,gramatica,skip_p).full;
}

///////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////
int main()
{
	FILE * pFile;
	char buffer[MAX_INPUT_LINE];
	string texto;

	//pFile = fopen ("/home/gonza/TesisLic/repositorio/genevalmag/GenEvalAG/src/grammar.txt" , "r");
	pFile = fopen ("/home/gera/tesisLic/genevalmag/GenEvalAG/src/grammar.txt" , "r");
	if (pFile == NULL)
		perror ("Error opening file");
	else
	{
		while ( !feof (pFile) )
		{
	          fgets (buffer , 128 , pFile);
	          texto += buffer;
	    }
		fclose (pFile);
	}

    if (parse_grammar(texto.c_str()))
    {
//		cout << texto <<  endl;
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
