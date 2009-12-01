/**
  *  \file	 	Operator.h
  *  \brief		Class of the operator of the grammar parsed.
  *  \date		28/09/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef OPERATOR_H_
#define OPERATOR_H_

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

class Operator
{
private:
	string 			o_name;
	oper_mode		o_mod;
	unsigned int	o_prec;
	oper_assoc 		o_assoc;
	vector <Sort*>	o_domain;
	Sort*			o_image;

	/**
	  * Method of copy the operator, STL-like C++.
	  */
	void copy (Operator const & other);
	/**
	  * Method destroy operator, STL-like C++.
	  */
	void destroy ();

public:
	/**
	  * Contructor empty of operator.
	  */
	Operator ();
	/**
	  * Contructor copy of operator.
	  */
	Operator (Operator const & other);

	/**
	  * Destructor of the operator.
	  */
	virtual ~Operator ();

	/**
	  * Operator assign (=) of operator.
	  */
	Operator& operator= (Operator const & other);

	/**
	  * Return the name of the operator.
	  */
	string get_name () const;
	/**
	  * Return the name of the operator.
	  */
    oper_mode get_mode () const;
    /**
      * Return the precedence of the operator.
      */
    int get_prec () const;
    /**
      * Return the associativity of the operator.
      */
    oper_assoc get_oper_assoc () const;
    /**
      * Return the domain of the operator.
      */
    vector<Sort*> get_domain () const;
    /**
      * Return the image of the operator.
      */
	Sort* get_image () const;

    /**
      * Set the name of the operator.
      */
    void set_name (string name);
    /**
      * Set the mode of the operator.
      * @param mode: string
      */
    void set_mode (string mode);
    /**
      * Set the precedence of the operator.
      */
    void set_prec (int prec);
    /**
      * Set the associativity of the operator.
      */
    void set_oper_assoc (string assoc);
    /**
      * Set the full sort domain of the operator.
      */
    void set_domain (vector<Sort*> domain);
    /**
      * Set the sort image of the operator.
      */
    void set_image (Sort* image);

    /**
      * Enqueue a sort in the domain of the operator.
      */
    void add_domain (Sort* sort);

    /**
      * Generate and return a string reprensentation of a operator.
      *
      * Result= "op" <oper_mode> " (" <precedence> "," <associativity> ")" <name> ":" <domain> "->" <image> ";"
      *
      * where <domain> is= <sort_1> [" (" <instance> ")" IF DEBUG IS ON] "," ... "," <sort_n> [" (" <instance> ")" IF DEBUG IS ON]
      */
    string to_string () const;

    /**
      * Compares the operator with other.
      */
    bool equals (Operator const & other) const;

    /**
      * Generate and return the string key that identifies a operator definitely.
      *
      * Result= <mode> <name> <domain> <image>
      *
      * where <domain> is= <sort_1> ... <sort_n>
      */
    string key () const;

//    void purge ();
};

} // end genevalmag

#endif /* OPERADOR_H_ */
