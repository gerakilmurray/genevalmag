/**
  *  \file		Sort.h
  *  \brief		Class of the sort of the grammar parsed.
  *  \date		28/09/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef SORT_H_
#define SORT_H_

/**
  * Enable/disable all output debuger in all class
  */
//#define _DEBUG

#include <string>

using namespace std;

namespace genevalmag
{

class Sort
{
private:
	string			s_name;
	unsigned int	s_ins;

	/**
	  * Method of copy the sort, STL-like C++.
	  */
	void copy(Sort const& other);
	/**
	  * Method destroy sort, STL-like C++.
	  */
	void destroy();

public:
	/**
	  * Contructor empty of sort.
	  */
	Sort();
	/**
	  * Contructor with the name of the sort.
	  */
	Sort(string name);
	/**
	  * Contructor copy of sort.
	  */
	Sort(Sort const & other);

	/**
	  * Destructor of sort.
	  */
	virtual ~Sort();

	/**
	  * Operator assign(=) of sort.
	  */
	Sort& operator=(Sort const & other);

	/**
	  * Return the name of the sort.
	  */
	string get_name() const;
	/**
	  * Return the instance of the sort.
	  */
	int get_ins() const;

	/**
	  * Set the name of the sort.
	  */
	void set_name(string name);

	/**
	  * Generate and return a string reprensentation of a attribute.
	  *
	  * Result= "sort" <name> ["(" <instance> ")" IF DEBUG IS ON] ";"
	  */
	string to_string() const;

	/**
	  * Compares the sort with other.
	  */
	bool equals(Sort const & other) const;

	/**
	  * Generate and return the string key that identifies a sort definitely.
	  *
	  * Result= <name>
	  */
	string key() const;
};

} // end genevalmag

#endif /* SORT_H_ */
