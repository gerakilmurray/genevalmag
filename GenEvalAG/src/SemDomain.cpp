/**
 * \file SemDomain.cpp
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 28/09/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#include "SemDomain.h"
#include <iostream>

using namespace std;
namespace genevalmag {

SemDomain::SemDomain()
{

}

SemDomain::~SemDomain()
{
	// TODO Auto-generated destructor stub
}

bool SemDomain::search_sort(Sort sort)
{
	for (vector<Sort>::size_type i = 0; i < this->v_sort.size(); i++)
		if (this->v_sort.at(i).equals(sort))
			return true;
	return false;
}
bool SemDomain::search_op(Operator op)
{
	for (vector<Operator>::size_type i = 0; i < this->v_op.size(); i++)
		if (this->v_op.at(i).equals(op))
			return true;
	return false;
}

void SemDomain::add_sort(Sort s)
{
	if (!search_sort(s))
		this->v_sort.push_back(s);
}

// devuelve true si agrega una operacion nueva.
bool SemDomain::add_op(Operator op)
{
	if (!search_op(op))
	{
		this->v_op.push_back(op);
		return true;
	}else
		return false;
}

Operator * SemDomain::get_last_op()
{
	return &(this->v_op.at(v_op.size()-1));
}

Sort  SemDomain::get_sort(string name)
// seach sort and return it else create and return
{
	for (vector<Sort>::size_type i = 0; i < this->v_sort.size(); i++)
		if (this->v_sort.at(i).getName().compare(name) == 0)
			return v_sort.at(i);
	Sort sort(name);
	this->v_sort.push_back(sort);
	return sort;
}
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
