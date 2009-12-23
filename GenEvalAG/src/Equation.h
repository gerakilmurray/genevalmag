/**
  *  \file		Equation.h
  *  \brief		Class of the equations of the grammar parsed.
  *  \date		05/11/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef EQUATION_H_
#define EQUATION_H_

#include "tree/tree.hh"

#include "ast/Ast_node.h"
#include "ast/Ast_instance.h"

namespace genevalmag
{
class Equation
{
	private:
		Ast_instance*	l_value;
		tree<Ast_node*>	r_value;

		/**
		  * Method of copy the equation, STL-like C++.
		  */
		void copy (Equation const& other);
		/**
		  * Method destroy equation, STL-like C++.
		  */
		void destroy ();

	public:
		/**
		  * Constructor empty of equation.
		  */
		Equation ();

		/**
		  * Contructor copy of Equation.
		  */
		Equation (Equation const & other);

		/**
		  * Destructor of equation.
		  */
		virtual ~Equation ();
		/**
		  * Operator assign (=) of Equation.
		  */
		Equation& operator= (Equation const & other);
		/**
		  * Return the l_value of the equation.
		  */
		Ast_instance* get_l_value () const;
		/**
		  * Return the r_value of the equation.
		  */
		tree<Ast_node*> get_r_value () const;
		/**
		  * Set the left value of the equation.
		  */
		void set_l_value(Ast_instance* lvalue);

		/**
		  * Set the rigth value of the equation: is a tree.
		  */
		void set_r_value(const tree<Ast_node*>& rvalue);
		/**
		  * Generate and return a string reprensentation of a Equation.
		  *
		  * Result= <l_value> "::=" <r_value> ";"
		  *
		  * where <l_value> = "instance_attr" and <r_value> is= "list of node_ast"
		  */
		string to_string () const;
};

} // end genevalmag

#endif /* EQUATION_H_ */
