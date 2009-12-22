/**
  *  \file		Equation.cpp
  *  \brief		Implementation of the methods the Equation.h
  *  \date		05/11/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */


#include <sstream>
#include <iostream>

#include "Equation.h"
#include "ast/Ast_literal.h"

namespace genevalmag
{

#ifdef _DEBUG
	// Numbers of operators current in the system.
	static int eqs = 0;
#endif

/**
  * Constructor empty of equation.
  */
Equation::Equation ()
{
	#ifdef _DEBUG
		eqs++;
	#endif
}

/**
  * Contructor copy of Equation.
  */
Equation::Equation (Equation const & other)
{
	copy (other);

	#ifdef _DEBUG
		eqs++;
	#endif
}

/**
  * Destructor of equation.
  */
Equation::~Equation ()
{
	destroy ();

	#ifdef _DEBUG
		eqs--;
		cout << "Equations: " << eqs << endl;
	#endif
}

/**
  * Method of copy the equation, STL-like C++.
  */
void Equation::copy (Equation const & other)
{
	l_value = other.get_l_value();
	r_value = other.get_r_value();
}

/**
  * Operator assign (=) of Equation.
  */
Equation& Equation::operator= (Equation const & other)
{
	if (this != &other)
	{
		destroy ();
		copy (other);
	}
	return *this;
}

/**
  * Method destroy equation, STL-like C++.
  */
void Equation::destroy ()
{
// ANALIZAR ACA, PERO CREO QUE NO DEBERIAMOS HACER NADA PORQUE LOS PUNTEROS SE DESTRUYEN SOLOS Y LA MEMORIA
// APUNTADA NO SE DEBE BORRAR YA QUE ES PROPIEDAD DE LOS MAP.
}


/**
  * Return the l_value of the equation.
  */
Ast_instance* Equation::get_l_value () const
{
	return l_value;
}

/**
  * Return the r_value of the equation.
  */
tree<Ast_node*> Equation::get_r_value () const
{
	return r_value;
}

/**
  * Set the left value of the equation.
  */
void Equation::set_l_value(Ast_instance* lvalue)
{
	l_value = lvalue;
}

/**
  * Set the left value of the equation.
  */
void Equation::set_r_value(tree<Ast_node*> rvalue)
{
	r_value = rvalue;
}

/**
  * Generate and return a string reprensentation of a Equation.
  *
  * Result= <l_value> "::=" <r_value> ";"
  *
  * where <l_value> = "instance_attr" and <r_value> is= "list of node_ast"
  */
string Equation::to_string () const
{
	string eq;

	// Save l_value.
	eq.append (l_value->to_string());
	eq.append ("\t::=\t");

	// save r_value.

	tree<Ast_node*>::pre_order_iterator it = r_value.end();
	tree<Ast_node*>::pre_order_iterator begin = r_value.begin();

	if(!r_value.is_valid(begin))
	{
		cerr << "todo mal" << endl;
		return "todo mal";
	}

	int rootdepth = r_value.depth(it);

	while(it != begin)
	{
		for(int i=0; i<r_value.depth(it)-rootdepth; ++i)
		{
			eq.append((*it)->to_string());
		}
		if (--it != begin) eq.append (" ");
	}
	eq.append (";");
	return eq;
}

} // end genevalmag
