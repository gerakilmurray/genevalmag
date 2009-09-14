/**
  *  \file NumberList.cpp
  *      \brief Example of Spirit Librarie.
  *  \date 13/09/2009
  *  \author    Kilmurray, Gerardo Luis.
  *  \author    Picco, Gonzalo Martín.
  */

/*=============================================================================
    Copyright (c) 2002-2003 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  This sample demontrates a parser for a comma separated list of numbers
//  This is discussed in the "Quick Start" chapter in the Spirit User's Guide.
//
//  [ JDG 5/10/2002 ]
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_push_back_actor.hpp>
#include <iostream>
#include <vector>
#include <string>

///////////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace BOOST_SPIRIT_CLASSIC_NS;

///////////////////////////////////////////////////////////////////////////////
//
//  Our comma separated list parser
//
///////////////////////////////////////////////////////////////////////////////
bool
parse_numbers(char const* str, vector<double>& v)
{
    return parse(str,

        //  Begin grammar
        (
            real_p[push_back_a(v)] >> *(',' >> real_p[push_back_a(v)])
        )
        ,
        //  End grammar

        space_p).full;
}

bool
parse_extends(char const* str, vector<string>& v)
{
	return true;
}
bool
parse_semantic(char const* str, vector<string>& v)
{
	return true;
}
bool
parse_attributes(char const* str, vector<string>& v)
{
	return true;
}
bool
parse_rules(char const* str, vector<string>& v)
{
return true;
}

bool
parse_grammar(char const* str, vector<string>& v)
{
	rule<> r_ident, r_extends, r_semantics, r_rules, r_attributes, at_grammar;
	r_ident = alnum_p >> *(alnum_p);
	r_extends = strlit<>("extends:") >> r_ident >> *(',' >> r_ident)>> ';';
	r_semantics = strlit<>("semantics:") >> r_ident >> *(',' >> r_ident)>> ';';
	r_rules = strlit<>("rules:") >> r_ident >> *(',' >> r_ident)>> ';';
	r_attributes = strlit<>("attributes:") >> r_ident >> *(',' >> r_ident) >> ';';
	at_grammar = !(r_extends) >> r_semantics >> r_attributes >> r_rules;
    return parse(str,

        //  Begin grammar

        	at_grammar[push_back_a(v)]

        ,
        space_p).full;
}
////////////////////////////////////////////////////////////////////////////
//
//  Main program
//
////////////////////////////////////////////////////////////////////////////
int
main()
{
    cout << "/////////////////////////////////////////////////////////\n\n";
    cout << "\t\tA comma separated list parser for Spirit...\n\n";
    cout << "/////////////////////////////////////////////////////////\n\n";

    cout << "Give me a comma separated list of words.\n";
    cout << "The  will be inserted in a vector of numbers\n";
    cout << "Type [q or Q] to quit\n\n";

    string str;
    while (getline(cin, str))
    {
        if (str[0] == 'q' || str[0] == 'Q')
            break;

        vector<string> v;
        if (parse_grammar(str.c_str(), v))
        {
            cout << "-------------------------\n";
            cout << "Parsing succeeded\n";
            cout << str << " Parses OK: " << endl;

            for (vector<string>::size_type i = 0; i < v.size(); ++i)
                cout << i << ": " << v[i] << endl;

            cout << "-------------------------\n";
        }
        else
        {
            cout << "-------------------------\n";
            cout << "Parsing failed\n";
            cout << "-------------------------\n";
        }
    }

    cout << "Bye... :-) \n\n";
    return 0;
}
