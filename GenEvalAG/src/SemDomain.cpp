/**
 * \file SemDomain.cpp
 * 	\brief Implements SemDomain.h
 *  \date 28/09/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#include "SemDomain.h"
#include <iostream>

using namespace std;
namespace genevalmag {

///////////////////////////////////////////////
// contructors
///////////////////////////////////////////////
SemDomain::SemDomain()
{

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

///////////////////////////////////////////////
// add sort at vector sort
///////////////////////////////////////////////
void SemDomain::add_sort(Sort s)
{
	if (!search_sort(s))
		this->v_sort.push_back(s);
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
// semantic block to string
///////////////////////////////////////////////
string SemDomain::to_string()
{
	string semdomain("\nsemantics domains{\n");
	semdomain.append(this->to_string_sorts());
	semdomain.append("\n");
	semdomain.append(this->to_string_ops());
	semdomain.append("}\n");
	return semdomain;
}
}
