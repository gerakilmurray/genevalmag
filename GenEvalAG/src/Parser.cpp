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
using namespace genevalmag;
using namespace BOOST_SPIRIT_CLASSIC_NS;

/** Vectors with each part of the attibute grammar
  */
vector<string> extends;
vector<string> attributes;
vector<string> semantics;
vector<string> rules;
SemDomain sem_domain;

void v_extend (char const* str, char const* end)
{
    string  s(str, end);
    extends.push_back(s);
}

void v_semantic (char const* str, char const* end)
{
    string  s(str, end);
    semantics.push_back(s);
}

void v_attribute (char const* str, char const* end)
{
    string  s(str, end);
    attributes.push_back(s);
}

void v_rule (char const* str, char const* end)
{
    string  s(str, end);
    rules.push_back(s);
}

void addSort (char const* str, char const* end)
{
    string  s(str, end);
	Sort s_new(s);
	sem_domain.add_sort(s_new);
}


void imprimir()
{
sem_domain.print_sort();


//	cout << "Extend\n";
//    for (vector<string>::size_type i = 0; i < extends.size(); ++i)
//        cout << i << ": " << extends[i] << endl;
//	cout << "Semantic\n";
//    for (vector<string>::size_type i = 0; i < semantics.size(); ++i)
//        cout << i << ": " << semantics[i] << endl;
//	cout << "Attribute\n";
//    for (vector<string>::size_type i = 0; i < attributes.size(); ++i)
//        cout << i << ": " << attributes[i] << endl;
//	cout << "Rule\n";
//    for (vector<string>::size_type i = 0; i < rules.size(); ++i)
//        cout << i << ": " << rules[i] << endl;
}

struct att_grammar: public grammar<att_grammar>
    {
        template <typename ScannerT>
        struct definition
        {
            definition(att_grammar const &self)
            {
            	r_ident = (alpha_p | ch_opt) >> *(alnum_p | ch_opt);

            	r_semantics = strlit<>("semantics domains{") >> +bloq_sem >> strlit<>("}");
            	bloq_sem = decl_op | decl_sort;
            	decl_sort = strlit<>("sort ") >> r_ident[&addSort] >> *(',' >> r_ident[&addSort]) >> ';';
            	decl_op = strlit<>("op ") >> !(mod_op >> '(' >> int_p >> ')') >>
						  r_ident >> ':' >> dom_op >> strlit<>(":=>") >> r_ident  >> ';';
            	dom_op = r_ident >> *(',' >> r_ident);
            	mod_op = strlit<>("infix") | strlit<>("prefix") | strlit<>("sufix");
            	ch_opt = ch_p ('+')|'_'|'*'|'/'|'^'|'%'|'&'|'<'|'='|'-'|'>';
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
	char buffer[100];
	string texto;

	pFile = fopen ("/home/gonza/TesisLic/repositorio/genevalmag/GenEvalAG/src/grammar.txt" , "r");
	if (pFile == NULL) perror ("Error opening file");
	else
	{
		while ( ! feof (pFile) )
		{
	          fgets (buffer , 100 , pFile);
	          texto += buffer;
	    }
		fclose (pFile);
	}
	string c;

//	texto = "extends:standart,numeric,vergamota;semantics:f,g,d,pepito,lafuncion;attributes:a,valor,simb,b,nose;rules:r1,laregla,yosoynueva;";
//	texto = "semantics domains{sort int;sort string,character;op mas:int,int->int;op sqr:int->int;sort pepe;}";
//	cout << texto << endl;
//	getline(cin, c);
//	if (c=="q") return 0;
    if (parse_grammar(texto.c_str()))
    {
		cout << "-------------------------\n";
		cout << "Parsing succeeded\n";
		cout << texto << "\nParses OK: \n" <<  endl;
		cout << "-------------------------\n";
		imprimir();
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
