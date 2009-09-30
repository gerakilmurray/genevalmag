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

void SemDomain::add_sort(Sort s)
{
	if (!search_sort(s))
		this->v_sort.push_back(s);
}

void SemDomain::add_op(Operator op)
{
	this->v_op.push_back(op);
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
void SemDomain::print_ops()
{
	for (vector<Sort>::size_type i = 0; i < this->v_op.size(); ++i)
		cout << "\t" << this->v_op[i].to_string() << endl;

}
void SemDomain::print_sorts()
{
	for (vector<Sort>::size_type i = 0; i < this->v_sort.size(); ++i)
	   cout << "\t" <<  "sort " << this->v_sort[i].getName() << endl;
}
void SemDomain::print_sem_dom()
{
	cout << "\nsemantics domains {\n";
	this->print_sorts();
	cout << "\n";
	this->print_ops();
	cout << "}\n";
}
}
