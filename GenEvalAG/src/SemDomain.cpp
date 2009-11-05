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
template <class T> bool search(const T& elem, const vector <T>& vec)
{
	for (size_t i = 0; i < vec.size(); i++)
		if (vec[i].equals(elem))
			return true;
	return false;
}

template <class T> bool add(const T& elem, vector<T>& vec)
{
	if (search<T>(elem, vec))
		return false;

	vec.push_back(elem);
	return true;
}

template <class T> string to_string_vec(const vector<T>& vec)
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
bool SemDomain::add_sort(const Sort& s)
{
	return add <Sort> (s, this->v_sort);
}

bool SemDomain::add_op(const Operator& op)
{
	return add <Operator> (op, this->v_oper);
}

bool SemDomain::add_att(const Attribute& attr)
{
	return add <Attribute> (attr, this->v_attr);
}

bool SemDomain::add_symb(const Symbol& symb)
{
	return add <Symbol> (symb, this->v_symb);
}

///////////////////////////////////////////////
// Search's Operations
///////////////////////////////////////////////
bool SemDomain::search_sort(const Sort& sort) const
{
	return search <Sort> (sort, this->v_sort);
}

bool SemDomain::search_op(const Operator& op) const
{
	return search <Operator> (op, this->v_oper);
}

bool SemDomain::search_att(const Attribute& attr) const
{
	return search <Attribute> (attr, this->v_attr);
}

bool SemDomain::search_symb(const Symbol& symb) const
{
	return search <Symbol> (symb, this->v_symb);
}

///////////////////////////////////////////////
// seach sort and return it. else create a sort and return.
///////////////////////////////////////////////
Sort  SemDomain::get_sort(string name)
{
	for (vector<Sort>::size_type i = 0; i < this->v_sort.size(); i++)
		if (this->v_sort.at(i).getName().compare(name) == 0)
			return v_sort.at(i);
	// the sort not exist and so create it.
	Sort sort(name);
	this->v_sort.push_back(sort);
	return sort;
}

///////////////////////////////////////////////
// semantic block to string
///////////////////////////////////////////////
string SemDomain::to_string() const
{
	string semdomain("\nsemantics domains\n");
	semdomain.append(to_string_vec<Sort>(this->v_sort));
	semdomain.append("\n");
	semdomain.append(to_string_vec<Operator>(this->v_oper));
	semdomain.append("\nattributes\n");
	semdomain.append(to_string_vec<Attribute>(this->v_attr));
	semdomain.append("\nsymbols\n");
	semdomain.append(to_string_vec<Symbol>(this->v_symb));
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
	if ((*tok_iter).compare("all"))
	{
		for (++tok_iter;tok_iter != tokens.end(); ++tok_iter)
		{
			if (s.getName().compare(*tok_iter) == 0) return false;
		}
		return true;
	}
	else
	{
		for (;tok_iter != tokens.end(); ++tok_iter)
		{
			if (s.getName().compare(*tok_iter) == 0) return true;
		}
		return false;
	}
}

void SemDomain::load_atts(Symbol& symb) const
{
	for (vector<Attribute>::size_type i = 0; i < this->v_attr.size(); ++i)
	{
		if (belong(symb, v_attr[i].getMember_symbol()))
		{
			symb.addAttr(v_attr[i]);
		}
	}
}
}
