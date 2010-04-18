/**
  *  \file      Sort.cpp
  *  \brief     Implementation of the methods the Sort.h
  *  \date      28/09/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>
#include <sstream>

#include "../../include/Attr_grammar/Sort.h"

namespace genevalmag
{

#ifdef _DEBUG
    /* Numbers of sorts current in the system. */
    static unsigned short sorts(0);
#endif

/**
  * Contructor empty of Sort.
  */
Sort::Sort()
{
    s_ins = 1;

    #ifdef _DEBUG
        sorts++;
    #endif
}

/**
  * Contructor with the name of the Sosrt.
  */
Sort::Sort(string name)
{
    s_ins            = 1;
    s_name           = name;
    s_type_basic     = false;

    #ifdef _DEBUG
        sorts++;
    #endif
}

/**
  * Contructor copy of Sort.
  */
Sort::Sort(const Sort &other)
{
    copy(other);

    #ifdef _DEBUG
        sorts++;
    #endif
}

/**
  * Destructor of Sort.
  */
Sort::~Sort()
{
    destroy();

    #ifdef _DEBUG
        sorts--;
        if(sorts == 0)
        {
            cout << sorts << " -> Sorts" << endl;
        }
    #endif
}

/**
  * Operator assign(=) of Sort.
  */
Sort &Sort::operator=(const Sort &other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

/**
  * Method of copy the Sort, STL-like C++.
  */
void Sort::copy(const Sort &other)
{
    s_name          = other.get_name();
    s_type_basic    = other.is_type_basic();

    /* Increment the instance of sort. */
    s_ins           = other.s_ins + 1;
}

/**
  * Method destroy Sort, STL-like C++.
  */
void Sort::destroy()
{
}

/**
  * Return the name of the Sort.
  */
const string Sort::get_name() const
{
    return s_name;
}

/**
  * Set the name of the Sort.
  */
void Sort::set_name(const string name)
{
    s_name = name;
}
/**
  * Set if the Sort is basic.
  */
void Sort::set_type_basic(const bool type_basic)
{
    s_type_basic = type_basic;
}
/**
  * Generates and returns a string reprensentation of a Sort.
  *
  * Result = "sort" \<name\> ["(" \<instance\> ")" IF DEBUG IS ON] ";"
  */
const string Sort::to_string() const
{
    string sort;
    if (is_type_basic())
    {
        sort.append("//");
    }
    sort.append("sort\t\t");
    sort.append(s_name);

	#ifdef _DEBUG
		sort.append("(");
		stringstream ins;
		ins << s_ins;
		sort.append(ins.str());
		sort.append(")");
	#endif

    sort.append(";");

    if (is_type_basic())
    {
        sort.append("\t-> Type Basic");
    }
    return sort;
}

/**
  * Compares the Sort with other.
  */
const bool Sort::equals(const Sort &other) const
{
    return (key().compare(other.key()) == 0);
}

/**
  * Return if the Sort is basic.
  */
const bool Sort::is_type_basic() const
{
    return s_type_basic;
}

/**
  * Generate and return the string key that identifies a Sort definitely.
  *
  * Result = \<name\>
  */
const string Sort::key() const
{
    return s_name;
}

} /* end genevalmag */
