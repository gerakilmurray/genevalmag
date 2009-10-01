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

/** Variable to represent Semantic domain
  */
SemDomain sem_domain;
Operator * new_op;

void addSort (char const* str, char const* end)
{
    string  s(str, end);
	Sort sort(s);
	sem_domain.add_sort(sort);
}
void inicOp (char const* str, char const* end)
{
	new_op = new Operator();
}
void addOp (char const* str, char const* end)
{
	if (!sem_domain.add_op(*new_op))
	{
		free(new_op);
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

struct att_grammar: public grammar<att_grammar>
{
	template <typename ScannerT>
	struct definition
	{
		definition(att_grammar const &self)
		{
			r_ident = (alpha_p | ch_opt) >> *(alnum_p | ch_opt);
			ch_opt = ch_p ('+')|'_'|'*'|'/'|'^'|'%'|'&'|'<'|'='|'-'|'>';

			r_semantics = strlit<>("semantics domains")>> '{' >> +bloq_sem >> '}';

			bloq_sem = decl_op[&addOp] | decl_sort;

			decl_sort = strlit<>("sort ") >> r_ident[&addSort] >> *(',' >> r_ident[&addSort]) >> ';';

			decl_op = strlit<>("op ")[&inicOp] >>
					  !(mod_op[&saveMod]) >>
					  !('(' >> int_p[&savePred] >> ')') >>
					  r_ident[&saveName] >> ':' >>
					  dom_op >> strlit<>(":=>") >>
					  r_ident[&saveImg]  >> ';';
			dom_op = r_ident[&saveDom] >> *(',' >> r_ident[&saveDom]);
			mod_op = strlit<>("infix") | strlit<>("prefix") | strlit<>("sufix");
		}

		rule<ScannerT> r_ident, bloq_sem, r_semantics, decl_sort, decl_op, dom_op,mod_op,ch_opt;
		rule<ScannerT> const& start() const { return r_semantics; }
	};
};

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

	pFile = fopen ("/home/gonza/TesisLic/repositorio/genevalmag/GenEvalAG/src/grammar.txt" , "r");
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
		cout << "Parsing failed\n";
		cout << "-------------------------\n";
	}

    cout << "Bye... :-) \n\n";
    return 0;
}


