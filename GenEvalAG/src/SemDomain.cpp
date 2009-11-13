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
template <class T> bool search(T& elem, const vector <T>& vec)
{
	for (size_t i = 0; i < vec.size(); i++)
		if (vec[i].equals(elem))
			return true;
	return false;
}

template <class T> bool add(T& elem, vector<T>& vec)
{
	if (search<T>(elem, vec))
		return false;
	vec.push_back(elem);
	return true;
}

template <class T> string to_string_vec(vector<T>& vec)
{
	string elem;
	for (size_t i = 0; i < vec.size(); ++i)
	{
		elem.append("\t");
		elem.append(vec[i].to_string());
		elem.append("\n");
	}
	return elem;
}

///////////////////////////////////////////////
// Add's Operations
///////////////////////////////////////////////
bool SemDomain::add_sort( Sort& s)
{
	return add <Sort> (s, v_sort);
}

bool SemDomain::add_op( Operator& op)
{
	return add <Operator> (op, v_oper);
}

bool SemDomain::add_att( Attribute& attr)
{
	return add <Attribute> (attr, v_attr);
}

bool SemDomain::add_symb(Symbol& symb)
{
	bool not_repeat = add <Symbol> (symb, v_symb);
	if (not_repeat && symb.is_non_terminal())
		load_attrs(v_symb[v_symb.size()-1]);
//		load_attrs(symb);
	return not_repeat;
}
bool SemDomain::add_rule( Rule& rule)
{
	return add <Rule> (rule, v_rule);
}

///////////////////////////////////////////////
// Search's Operations
///////////////////////////////////////////////
bool SemDomain::search_sort( Sort& sort) const
{
	return search <Sort> (sort, v_sort);
}

bool SemDomain::search_op( Operator& op) const
{
	return search <Operator> (op, v_oper);
}

bool SemDomain::search_att( Attribute& attr) const
{
	return search <Attribute> (attr, v_attr);
}

bool SemDomain::search_symb( Symbol& symb) const
{
	return search <Symbol> (symb, v_symb);
}
bool SemDomain::search_rule( Rule& rule) const
{
	return search <Rule> (rule, v_rule);
}

///////////////////////////////////////////////
// seach sort and return it. else create a sort and return.
///////////////////////////////////////////////
Sort& SemDomain::return_sort(string name)
{
	for (vector<Sort>::size_type i = 0; i < v_sort.size(); i++)
		if (v_sort.at(i).get_name().compare(name) == 0)
			return v_sort.at(i);
	// the sort not exist and so create it.
	cout << "ERROR: sort no existe" << endl;
	exit(0);
	return v_sort[0];
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
	semdomain.append(to_string_vec<Attribute>(v_attr));
	semdomain.append("\nsymbols\n");
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
	for (vector<Attribute>::size_type i = 0; i < v_attr.size(); ++i)
	{
		if (belong(symb, v_attr[i].get_member_symbol()))
		{
			symb.add_attr(v_attr[i]);
		}
	}
}

Symbol* SemDomain::get_symbol(string name_symbol)
{
	for (vector<Symbol>::size_type i = 0; i < v_symb.size(); ++i)
	{
		if (v_symb[i].get_name().compare(name_symbol) == 0)
		{
			return &(v_symb[i]);
		}
	}
	return NULL;
}

}
