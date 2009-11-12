/**
 * \file Sort.cpp
 * 	\brief Implements Sort.h
 *  \date 28/09/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#include <iostream>

#include "Sort.h"

namespace genevalmag {

static int nm= 0;

///////////////////////////////////////////////
// contructors
///////////////////////////////////////////////
Sort::Sort(string name) {
	s_id = 0;
	s_name = name;
	nm++;
}
Sort::Sort() {	nm++;}

Sort::Sort(Sort const & other)
{
	copy(other);
	nm++;
}

///////////////////////////////////////////////
// destrucors
///////////////////////////////////////////////
Sort::~Sort() {
	destroy();
	nm--;
	cout << nm << " sorts" << endl;
}

Sort& Sort::operator= (Sort const& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

void Sort::copy(Sort const& other)
{
	s_name = other.get_name();
	s_id = other.get_id();
}

void Sort::destroy()
{
}

///////////////////////////////////////////////
// Setters and getters.
///////////////////////////////////////////////
int Sort::get_id() const
{
    return s_id;
}

string Sort::get_name() const
{
    return s_name;
}

void Sort::set_id(int id)
{
    s_id = id;
}

void Sort::set_name(string name)
{
    s_name = name;
}

///////////////////////////////////////////////
// compares the sort with other.
///////////////////////////////////////////////
bool Sort::equals(Sort s) const
{
	return s_name.compare(s.s_name)== 0;
}

///////////////////////////////////////////////
// Sort to string
///////////////////////////////////////////////
string Sort::to_string() const
{
	string sort("sort\t");
	sort.append(get_name());
	sort.append(";");
	return sort;
}

}
