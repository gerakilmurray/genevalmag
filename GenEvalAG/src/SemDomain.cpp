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
// search a sort in the vector sort
///////////////////////////////////////////////
bool SemDomain::search_sort(Sort sort)
{
	for (vector<Sort>::size_type i = 0; i < this->v_sort.size(); i++)
		if (this->v_sort.at(i).equals(sort))
			return true;
	return false;
}

///////////////////////////////////////////////
// search a operation in the vector operation
///////////////////////////////////////////////
bool SemDomain::search_op(Operator op)
{
	for (vector<Operator>::size_type i = 0; i < this->v_op.size(); i++)
		if (this->v_op.at(i).equals(op))
			return true;
	return false;
}

bool SemDomain::search_att(Attribute attr)
{
	for (vector<Attribute>::size_type i = 0; i < this->v_attr.size(); i++)
		if (this->v_attr.at(i).equals(attr))
			return true;
	return false;
}

///////////////////////////////////////////////
// add sort at vector sort
///////////////////////////////////////////////
bool SemDomain::add_sort(Sort s)
{
	if (!search_sort(s))
	{
		this->v_sort.push_back(s);
		return true;
	}else
		return false;
}

///////////////////////////////////////////////
// add attribute at vector attribute
///////////////////////////////////////////////
bool SemDomain::add_att(Attribute att)
{
	if (!search_att(att))
	{
		this->v_attr.push_back(att);
		return true;
	}else
		return false;
}

///////////////////////////////////////////////
// add sort at vector sort
///////////////////////////////////////////////
bool SemDomain::add_op(Operator op)
// devuelve true si agrega una operacion nueva.
{
	if (!search_op(op))
	{
		this->v_op.push_back(op);
		return true;
	}else
		return false;
}

///////////////////////////////////////////////
// return the last operation and not out of vector
///////////////////////////////////////////////
Operator * SemDomain::get_last_op()
{
	return &(this->v_op.at(v_op.size()-1));
}

///////////////////////////////////////////////
// seach sort and return it. else create a sort and return.
///////////////////////////////////////////////
Sort  SemDomain::get_sort(string name)
{
	for (vector<Sort>::size_type i = 0; i < this->v_sort.size(); i++)
		if (this->v_sort.at(i).getName().compare(name) == 0)
			return v_sort.at(i);
	Sort sort(name);
	this->v_sort.push_back(sort);
	return sort;
}

template <typename T>
string to_string_vec(T vec)
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
// operation's vector to string
///////////////////////////////////////////////
string SemDomain::to_string_ops()
{
	string op;
	for (vector<Sort>::size_type i = 0; i < this->v_op.size(); ++i)
	{
		op.append("\t");
		op.append(this->v_op[i].to_string());
		op.append("\n");
	}
	return op;
}

///////////////////////////////////////////////
// sort's vector to string
///////////////////////////////////////////////
string SemDomain::to_string_sorts()
{
	string sort;
	for (vector<Sort>::size_type i = 0; i < this->v_sort.size(); ++i)
	{
		sort.append("\t");
		sort.append(this->v_sort[i].to_string());
		sort.append("\n");
	}
	return sort;
}

///////////////////////////////////////////////
// operation's Attribute to string
///////////////////////////////////////////////
string SemDomain::to_string_atts()
{
	string atts;
	for (vector<Attribute>::size_type i = 0; i < this->v_attr.size(); ++i)
	{
		atts.append("\t");
		atts.append(this->v_attr[i].to_string());
		atts.append("\n");
	}
	return atts;
}

///////////////////////////////////////////////
// semantic block to string
///////////////////////////////////////////////
string SemDomain::to_string()
{
	string semdomain("\nsemantics domains\n");
	semdomain.append(this->to_string_sorts());
	semdomain.append("\n");
	semdomain.append(this->to_string_ops());
	semdomain.append("\nattributes\n");
	semdomain.append(this->to_string_atts());
	semdomain.append("\n");
	semdomain.append("\nParametrizada\n");
	semdomain.append(to_string_vec<vector <Attribute> >(this->v_attr));
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

void SemDomain::add_atts(Symbol s)
{
	for (vector<Attribute>::size_type i = 0; i < this->v_attr.size(); ++i)
	{
		if (belong(s, v_attr[i].getMember_symbol()))
		{
			s.addAttr(v_attr[i]);
		}
	}
}
}
