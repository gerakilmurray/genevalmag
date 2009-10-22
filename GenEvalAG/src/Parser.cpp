/**
  *  \file Parser.cpp
  *      \brief Example of Spirit Librarie.
  *  \date 13/09/2009
  *  \author    Kilmurray, Gerardo Luis.
  *  \author    Picco, Gonzalo Martín.
  */

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_push_back_actor.hpp>
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

Operator * new_op; // a new operator in the parser

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
		cout << "libero" << endl;
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

////////////////////////////
//// method for attribute bloq
///////////////////////////

void pepito (char const* str, char const* end)
{
	string  s(str, end);
	cout << s << endl;
}

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
			r_ident = (alpha_p | '_') >> *(alnum_p | '_' | '-');

			r_oper  = (alpha_p | '_' | r_id_op) >> *(alnum_p | '_' | r_id_op);

			r_id_op = ch_p ('+')|'*'|'/'|'^'|'%'|'&'|'<'|'='|'-'|'>';

			////////////////////////////////////////////////////////////
			// Grammar's Semantic Domain
			////////////////////////////////////////////////////////////

			r_semantics = strlit<>("semantics domains")>> '{' >> +bloq_sem >> '}';

			bloq_sem    = decl_op[&addOp] | decl_sort;

			decl_sort   = strlit<>("sort ") >> r_ident[&addSort] >> *(',' >> r_ident[&addSort]) >> ';';

			decl_op     = strlit<>("op ")[&inicOp] >>
						  !(mod_op[&saveMod]) >>
						  !('(' >> int_p[&savePred] >> ')') >>
						  r_oper[&saveName] >> ':' >>
						  dom_op >> strlit<>(":=>") >>
						  r_ident[&saveImg]  >> ';';
			dom_op      = r_ident[&saveDom] >> *(',' >> r_ident[&saveDom]);
			mod_op      = strlit<>("infix") | strlit<>("prefix") | strlit<>("sufix");

			////////////////////////////////////////////////////////////
			// Grammar's Attribute
			////////////////////////////////////////////////////////////

			r_attributes = strlit<>("attributes")>> '{' >> +decl_att >> '}';

			decl_att     = r_ident[&pepito] >> *(',' >> r_ident[&pepito]) >> // Sort membership
					       ':' >> !(r_type_att[&pepito]) >> '<' >> r_ident[&pepito] >> '>' >>
					       strlit<>("of")[&pepito] >>
					       ((r_ident[&pepito] >> *(',' >> r_ident[&pepito])) | strlit<>("all")[&pepito]) >> ';';

			r_type_att   = (strlit<>("inh") | strlit<>("syn"));

			////////////////////////////////////////////////////////////
			// Attribute Grammar
			////////////////////////////////////////////////////////////

			r_att_grammar = r_semantics >> r_attributes;
		}

		rule<ScannerT> r_ident, r_oper, r_id_op;

		rule<ScannerT> r_semantics, bloq_sem, decl_sort, decl_op, dom_op,mod_op;
		rule<ScannerT> r_attributes, decl_att, r_type_att;

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
	return parse(str,gramatica,space_p).full;
}

////////////////////////////////////////////////////////////////////////////
//
//  Main program
//
////////////////////////////////////////////////////////////////////////////
int main()
{
	FILE * pFile;
	char buffer[MAX_INPUT_LINE];
	string texto;

//	pFile = fopen ("/home/gonza/TesisLic/repositorio/genevalmag/GenEvalAG/src/grammar.txt" , "r");
	pFile = fopen ("/home/gera/tesisLic/genevalmag/GenEvalAG/src/grammar.txt" , "r");
	if (pFile == NULL)
		perror ("Error opening file");
	else
	{
		while ( !feof (pFile) )
		{
	          fgets (buffer , 100 , pFile);
	          texto += buffer;
	    }
		fclose (pFile);
	}

    if (parse_grammar(texto.c_str()))
    {
		cout << "-------------------------\n";
		cout << "Parsing succeeded\n";
		cout << texto << "\nParses OK: \n" <<  endl;
		cout << "-------------------------\n";
		cout << sem_domain.to_string();

    }
	else
	{
		cout << "-------------------------\n";
		cout << texto << "Parsing failed\n";
		cout << "-------------------------\n";
	}

    cout << "Bye... :-) \n\n";
    return 0;
}


