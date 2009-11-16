/**
 * \file SemDomain.cpp
 * 	\brief Implements SemDomain.h
 *  \date 28/09/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#include "SemDomain.h"
#include <iostream>
#include <boost/tokenizer.hpp>

using namespace std;
namespace genevalmag {

///////////////////////////////////////////////
// contructors
///////////////////////////////////////////////
SemDomain::SemDomain()
{
	// TODO Auto-generated constructor stub
}

///////////////////////////////////////////////
// destructors
///////////////////////////////////////////////
SemDomain::~SemDomain()
{
	// TODO Auto-generated destructor stub
}

///////////////////////////////////////////////
// Operation Templates
///////////////////////////////////////////////
template <class T> bool add(T elem, map<string,T >& vec)
{
	pair<string,T > new_p(elem.key(),elem);
	pair<typename map<string,T >::iterator, bool > result = vec.insert(new_p);
	return result.second;
}

template <class T> string to_string_vec(map<string,T >& vec)
{
	string elem;
	for (typename map<string,T >::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		elem.append("\t");
		elem.append(it->second.to_string());
		elem.append("\n");
	}
	return elem;
}

///////////////////////////////////////////////
// Add's Operations
///////////////////////////////////////////////
bool SemDomain::add_sort(Sort& sort)
{
	return add<Sort>(sort, v_sort);
}

bool SemDomain::add_op( Operator& oper)
{
	return add<Operator>(oper, v_oper);
}

bool SemDomain::add_att( Attribute& attr)
{
	return add<Attribute>(attr, v_attr);
}

bool SemDomain::add_symb(Symbol& symb)
{
	bool not_repeat = add <Symbol> (symb, v_symb);
	if (not_repeat && symb.is_non_terminal())
	{
		map<string, Symbol>::iterator it = v_symb.find(symb.key());
		load_attrs(it->second);
	}
	return not_repeat;
}

bool SemDomain::add_rule( Rule& rule)
{
	return add <Rule> (rule, v_rule);
}

///////////////////////////////////////////////
// seach sort and return it. else create a sort and return.
///////////////////////////////////////////////
Sort& SemDomain::return_sort(string name)
{
	Sort sort_new(name);
	add_sort(sort_new);

	map<string,Sort>::iterator it = v_sort.find(name);

	return it->second;
}

///////////////////////////////////////////////
// semantic block to string
///////////////////////////////////////////////
string SemDomain::to_string()
{
	string semdomain("\nsemantics domains\n");
	semdomain.append(to_string_vec<Sort>(v_sort));
	semdomain.append("\n");
	semdomain.append(to_string_vec<Operator>(v_oper));
	semdomain.append("\nattributes\n");
//	map<string,Attribute>::iterator it1 = v_attr.find("valorsynintall");
//	it1->second.set_name("valores");
	semdomain.append(to_string_vec<Attribute>(v_attr));
	semdomain.append("\nsymbols\n");
//	map<string,Symbol>::iterator it = v_symb.find("id");
//	it->second.set_name("ident");
	semdomain.append(to_string_vec<Symbol>(v_symb));
	semdomain.append("\nrules\n");
	semdomain.append(to_string_vec<Rule>(v_rule));
	semdomain.append("\n");
	return semdomain;
}

///////////////////////////////////////////////
// Symbol's operation
///////////////////////////////////////////////

bool belong(Symbol s, string exprAtts)
{
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep("{},-");
	tokenizer tokens(exprAtts, sep);
	tokenizer::iterator tok_iter = tokens.begin();

	if ((*tok_iter).compare("all") == 0)
	{
		for (++tok_iter;tok_iter != tokens.end(); ++tok_iter)
		{
			if (s.get_name().compare(*tok_iter) == 0)
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		for (;tok_iter != tokens.end(); ++tok_iter)
		{
			if (s.get_name().compare(*tok_iter) == 0)
			{
				return true;
			}
		}
		return false;
	}
}

void SemDomain::load_attrs(Symbol& symb)
{
	for (map<string,Attribute>::iterator it = v_attr.begin(); it != v_attr.end(); ++it)
	{
		if (belong(symb, it->second.get_member_symbol()))
		{
			symb.add_attr(&(it->second));
		}
	}
}

Symbol& SemDomain::get_symbol(string name_symbol)
{
	map<string,Symbol>::iterator it = v_symb.find(name_symbol);
	return it->second;
}

}
