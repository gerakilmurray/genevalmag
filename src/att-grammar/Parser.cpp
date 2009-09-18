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

using namespace std;
using namespace BOOST_SPIRIT_CLASSIC_NS;

/** Vectors with each part of the attibute grammar
  */
vector<string> extends;
vector<string> attributes;
vector<string> semantics;
vector<string> rules;

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

void add2vector (char const* str, char const* end, vector<string>* vec)
{
    string  s(str, end);
    vec->push_back(s);
}


void imprimir(){
	cout << "Extend\n";
    for (vector<string>::size_type i = 0; i < extends.size(); ++i)
        cout << i << ": " << extends[i] << endl;
	cout << "Semantic\n";
    for (vector<string>::size_type i = 0; i < semantics.size(); ++i)
        cout << i << ": " << semantics[i] << endl;
	cout << "Attribute\n";
    for (vector<string>::size_type i = 0; i < attributes.size(); ++i)
        cout << i << ": " << attributes[i] << endl;
	cout << "Rule\n";
    for (vector<string>::size_type i = 0; i < rules.size(); ++i)
        cout << i << ": " << rules[i] << endl;
}

struct att_grammar: public grammar<att_grammar>
    {
        template <typename ScannerT>
        struct definition
        {
            definition(att_grammar const &self)
            {
            		r_ident = (+alpha_p) >> *(alnum_p);
            		r_extends = strlit<>("extends:") >> r_ident[&v_extend] >> *(',' >> r_ident[&v_extend])>> ';';
            		r_semantics = strlit<>("semantics:") >> r_ident[&v_semantic] >> *(',' >> r_ident[&v_semantic])>> ';';
            		r_rules = strlit<>("rules:") >> r_ident[&v_rule] >> *(',' >> r_ident[&v_rule])>> ';';
            		r_attributes = strlit<>("attributes:") >> r_ident[&v_attribute] >> *(',' >> r_ident[&v_attribute]) >> ';';
            		at_grammar = !(r_extends) >> r_semantics >> r_attributes >> r_rules;
            }

            rule<ScannerT> r_ident, r_extends, r_semantics, r_rules, r_attributes, at_grammar;
            rule<ScannerT> const&
            start() const { return at_grammar; }
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
//	FILE * pFile;
//	char buffer[100];
	string texto;

//	pFile = fopen ("/home/gonza/grammar.txt" , "r");
//	if (pFile == NULL) perror ("Error opening file");
//	else
//	{
//		while ( ! feof (pFile) )
//		{
//	          fgets (buffer , 100 , pFile);
//	          texto += buffer;
//	    }
//		fclose (pFile);
//	}
//	string c;

	texto = "extends:standart,numeric,vergamota;semantics:f,g,d,pepito,lafuncion;attributes:a,valor,simb,b,nose;rules:r1,laregla,yosoynueva;";
	cout << texto << endl;
//	getline(cin, c);
//	if (c=="q") return 0;
    if (parse_grammar(texto.c_str()))
    {
		cout << "-------------------------\n";
		cout << "Parsing succeeded\n";
		cout << texto << " Parses OK: " << endl;
		imprimir();
		cout << "-------------------------\n";
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
