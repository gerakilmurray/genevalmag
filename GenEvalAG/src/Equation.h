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

	literal_node& operator= (literal_node const & other)
	{
		if (this != &other)
		{
			destroy ();
			copy (other);
		}
		return *this;
	}
	void destroy()
	{
		if (type_lit==k_string)
			free(value_lit.str_l);
	}
	void copy (literal_node const & other)
	{
		type_lit = other.type_lit;
		switch (other.type_lit)
		{
			case k_int:
				value_lit.int_l = other.value_lit.int_l;
				break;
			case k_float:
				value_lit.flt_l = other.value_lit.flt_l;
				break;
			case k_char:
				value_lit.ch_l = other.value_lit.ch_l;
				break;
			case k_string:
				value_lit.str_l = other.value_lit.str_l;
				break;
		}
	}
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

	node_ast& operator= (node_ast const & other)
	{
		if (this != &other)
		{
			destroy ();
			copy (other);
		}
		return *this;
	}

	void destroy()
	{
		if (n_type_node == k_intance)
			free(n_data.instance);
		if (n_type_node == k_literal)
			free(n_data.literal);
	}

	void copy (node_ast const & other)
	{
		n_type_synthetized = other.n_type_synthetized;
		n_type_node = other.n_type_node;
		switch (other.n_type_node)
		{
			case k_intance:
				n_data.instance = other.n_data.instance;
				break;
			case k_function:
				n_data.func = other.n_data.func;
				break;
			case k_operator:
				n_data.oper = other.n_data.oper;
				break;
			case k_literal:
				n_data.literal = other.n_data.literal;
				break;
		}
	}

};

class Equation
{
	private:
		instance_attr	l_value;
		tree<node_ast>	r_value;

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
		instance_attr get_l_value () const;
		/**
		  * Return the r_value of the equation.
		  */
		tree<node_ast> get_r_value () const;
		/**
		  * Set the left value of the equation.
		  */
		void set_l_value(instance_attr lvalue);

		/**
		  * Set the rigth value of the equation: is a tree.
		  */
		void set_r_value(tree<node_ast> rvalue);
		/**
		  * Generate and return a string reprensentation of a Equation.
		  *
		  * Result= <l_value> "::=" <r_value> ";"
		  *
		  * where <l_value> = "instance_attr" and <r_value> is= "list of node_ast"
		  */
		string to_string () const;
		string print_literal(literal_node lit);
		string print_instance(instance_attr lit);
};

} // end genevalmag

#endif /* EQUATION_H_ */
