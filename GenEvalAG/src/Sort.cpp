/**
 * \file Sort.cpp
 * 	\brief Implements Sort.h
 *  \date 28/09/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#include "Sort.h"

namespace genevalmag {

///////////////////////////////////////////////
// contructors
///////////////////////////////////////////////
Sort::Sort(string name) {
	this->s_id = 0;
	this->s_name = name;
}
Sort::Sort() {}

///////////////////////////////////////////////
// destrucors
///////////////////////////////////////////////
Sort::~Sort() {
	// TODO Auto-generated destructor stub
}

///////////////////////////////////////////////
// Setters and getters.
///////////////////////////////////////////////
int Sort::getId() const
{
    return this->s_id;
}

string Sort::getName() const
{
    return this->s_name;
}

void Sort::setId(int s_id)
{
    this->s_id = s_id;
}

void Sort::setName(string s_name)
{
    this->s_name = s_name;
}

///////////////////////////////////////////////
// compares the sort with other.
///////////////////////////////////////////////
bool Sort::equals(Sort s)
{
	return this->s_name.compare(s.s_name)== 0;
}

///////////////////////////////////////////////
// Sort to string
///////////////////////////////////////////////
string Sort::to_string()
{
	string sort("sort ");
	sort.append(this->getName());
	sort.append(";");
	return sort;
}

}
