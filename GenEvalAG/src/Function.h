/**
  *  \file		Function.h
  *  \brief		Class of the function of the grammar parsed.
  *  \date		26/11/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <string>
#include <vector>

#include "Sort.h"

namespace genevalmag
{

/**
  * Enumeration of operation's mode.
  */
enum oper_mode
{
	k_prefix,
	k_infix,
	k_postfix
};

/**
  * Enumeration of operation's associative modes.
  */
enum oper_assoc
{
	k_left,
	k_right,
	k_nonassoc
};

class Function
{
private:
	string 			f_name;
	vector <Sort*>	f_domain;
	Sort*			f_image;
	oper_mode		f_mod;
	unsigned int	f_prec;
	oper_assoc 		f_assoc;
	/**
	  * If that value is TRUE then the object function is a operator.
	  * This can be: prefix, infix or postfix.
	  */
	bool			f_is_operator;

	/**
	  * Method of copy the function, STL-like C++.
	  */
	void copy(const Function& other);
	/**
	  * Method destroy function, STL-like C++.
	  */
	void destroy();
public:
	/**
	  * Contructor empty of function.
	  */
	Function();
	/**
	  * Contructor copy of function.
	  */
	Function(Function const & other);

	/**
	  * Destructor of the function.
	  */
	virtual ~Function();

	/**
	  * Operator assign(=) of function.
	  */
	Function& operator=(Function const & other);

	/**
	  * Return the name of the function.
	  */
	string get_name() const;
	/**
	  * Return the domain of the function.
	  */
	vector<Sort*> get_domain() const;
	/**
	  * Return the image of the function.
	  */
	Sort* get_image() const;
	/**
	  * Return the name of the operator.
	  */
	oper_mode get_mode() const;
	/**
	  * Return the precedence of the operator.
	  */
	int get_prec() const;
	/**
	  * Return the associativity of the operator.
	  */
	oper_assoc get_oper_assoc() const;
	/**
	  * Return the arity of function.
	  */
	int get_arity() const;

	/**
	  * Set the name of the function.
	  */
	void set_name(string name);
	/**
	  * Set the full sort domain of the function.
	  */
	void set_domain(vector<Sort*> domain);
	/**
	  * Set the sort image of the function.
	  */
	void set_image(Sort* image);
	/**
	  * Set the mode of the operator.
	  * @param mode: string
	  */
	void set_mode(string mode);
	/**
	  * Set the precedence of the operator.
	  */
	void set_prec(int prec);
	/**
	  * Set the associativity of the operator.
	  */
	void set_oper_assoc(string assoc);
	/**
	  * Set the boolean attribute with the parameter.
	  */
	void set_is_operator(bool value);
	/**
	  * Enqueue a sort in the domain of the function.
	  */
	void add_domain(Sort* sort);

	/**
	  * Generate and return a string reprensentation of a function.
	  *
	  * Result= "function" <name> ":" <domain> "->" <image> ";"
	  *
	  * where <domain> is= <sort_1> ["(" <instance> ")" IF DEBUG IS ON] "," ... "," <sort_n> ["(" <instance> ")" IF DEBUG IS ON]
	  */
	string to_string() const;

	/**
	  * Return true if the function is a Operator.
	  */
	bool is_operator() const;
	/**
	  * Compares the function with other.
	  */
	bool equals(Function const & other) const;

	/**
	  * Generate and return the string key that identifies a function definitely.
	  *
	  * Result= <name> <domain> <image>
	  *
	  * where <domain> is= <sort_1> ... <sort_n>
	  */
	string key() const;

//	void purge();

};

} // end genevalmag

#endif /* FUNCTION_H_ */
