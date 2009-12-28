/**
  *  \file		Sort.cpp
  *  \brief		Implementation of the methods the Sort.h
  *  \date		28/09/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>
#include <sstream>

#include "Sort.h"

namespace genevalmag
{

#ifdef _DEBUG
	// Numbers of sorts current in the system.
	static int sorts= 0;
#endif

/**
  * Contructor empty of sort.
  */
Sort::Sort ()
{
	s_ins = 1;

	#ifdef _DEBUG
		sorts++;
	#endif
}

/**
  * Contructor with the name of the sort.
  */
Sort::Sort (string name)
{
	s_ins	= 1;
	s_name	= name;

	#ifdef _DEBUG
		sorts++;
	#endif
}

/**
  * Contructor copy of sort.
  */
Sort::Sort (Sort const & other)
{
	copy (other);

	#ifdef _DEBUG
		sorts++;
	#endif
}

/**
  * Destructor of sort.
  */
Sort::~Sort ()
{
	destroy ();

	#ifdef _DEBUG
		sorts--;
		if (sorts == 0)
			cout << sorts << " -> Sorts" << endl;
	#endif
}

/**
  * Operator assign (=) of sort.
  */
Sort& Sort::operator= (Sort const & other)
{
	if (this != &other)
	{
		destroy ();
		copy (other);
	}
	return *this;
}

/**
  * Method of copy the sort, STL-like C++.
  */
void Sort::copy (Sort const & other)
{
	s_name	= other.get_name ();
	 // Increment the instance of sort.
	s_ins	= other.get_ins () + 1;
}

/**
  * Method destroy sort, STL-like C++.
  */
void Sort::destroy ()
{
}

/**
  * Return the name of the sort.
  */
string Sort::get_name () const
{
    return s_name;
}

/**
  * Return the instance of the sort.
  */
int Sort::get_ins () const
{
    return s_ins;
}

/**
  * Set the name of the sort.
  */
void Sort::set_name (string name)
{
    s_name = name;
}

/**
  * Generate and return a string reprensentation of a attribute.
  *
  * Result= "sort" <name> [" (" <instance> ")" IF DEBUG IS ON] ";"
  */
string Sort::to_string () const
{
	string sort ("sort\t\t");
	sort.append (s_name);

	#ifdef _DEBUG
		sort.append (" (");
		stringstream ins;
		ins << s_ins;
		sort.append (ins.str ());
		sort.append (")");
	#endif

	sort.append (";");
	return sort;
}

/**
  * Compares the sort with other.
  */
bool Sort::equals (Sort const & other) const
{
	return key ().compare (other.key ())==0;
}

/**
  * Generate and return the string key that identifies a sort definitely.
  *
  * Result= <name>
  */
string Sort::key () const
{
	return s_name;
}

} // end genevalmag
