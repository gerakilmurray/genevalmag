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

#include "Attribute.h"
#include "Symbol.h"
#include "Operator.h"
#include "Function.h"

namespace genevalmag
{

/**
  * Node's type.
  */
enum node_type
{
	k_intance,
	k_function,
	k_operator,
	k_literal
};

/**
  * Type of basics literals.
  */
enum literal_type
{
	k_int,
	k_float,
	k_char,
	k_string
};

/**
  * This structure represents a particular attribute of a
  * symbol in the equation.
  */
struct instance_attr
{
	Symbol *	i_symb;	// Symbol.
	int			i_num;	// Index instance.
	Attribute *	i_attr; // Symbol's attribute.
};

/**
  *	AST node that storing a literal.
  */
struct literal_node
{
	union
	{
		string*		str_l;
		char		ch_l;
		float		flt_l;
		int			int_l;
	}
					value_lit;
	literal_type	type_lit;
};

/**
  * An AST node of the tree stores a data field type.
  * This is a union of the 4 types as possible within the parser.
  * Also has synthesized the whole kind of tree from which it is root.
  */
struct node_ast
{
	union
	{
		Operator*		oper;
		Function*		func;
		literal_node*	literal;
		instance_attr*	instance;
	}
						n_data;
	node_type			n_type_node;
	string				n_type_synthetized;
};

class Equation
{
	private:
		instance_attr	l_value;
		tree<node_ast>	r_value;

		/**
		  * Method of copy the equation, STL-like C++.
		  */
		void copy (Attribute const& other);
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
		  * Destructor of equation.
		  */
		virtual ~Equation ();

};

} // end genevalmag

#endif /* EQUATION_H_ */
