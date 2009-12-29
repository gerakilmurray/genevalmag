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
Equation::Equation()
{
	// Initialize the counter.
	count_ref = new unsigned int(1);

	#ifdef _DEBUG
		eqs++;
	#endif
}

/**
  * Contructor copy of Equation.
  */
Equation::Equation(Equation const & other)
{
	copy(other);

	#ifdef _DEBUG
		eqs++;
	#endif
}

/**
  * Destructor of equation.
  */
Equation::~Equation()
{
	// Decrement the counter.
	(*count_ref)--;

	destroy();

	#ifdef _DEBUG
		eqs--;
		if(eqs == 0)
			cout << eqs << " -> Equations" << endl;
	#endif
}

/**
  * Operator assign(=) of Equation.
  */
Equation& Equation::operator=(Equation const & other)
{
	if(this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

/**
  * Method of copy the equation, STL-like C++.
  */
void Equation::copy(Equation const & other)
{
	l_value		= other.get_l_value();
	r_value		= other.get_r_value();
	count_ref	= other._get_count_ref();

	// Increment the counter.
	(*count_ref)++;
}

/**
  * Method destroy equation, STL-like C++.
  */
void Equation::destroy()
{
	// Check if is the last reference.
	if(*count_ref == 0)
	{
		// Free all memory of the equation.
		delete(count_ref);

		//FALTA BORRAR EL NUEVO ARBOL!!
	}
}

/**
  * Return the count reference.
  */
unsigned int* Equation::_get_count_ref() const
{
	return count_ref;
}

/**
  * Return the l_value of the equation.
  */
Ast_instance Equation::get_l_value() const
{
	return l_value;
}

/**
  * Return the r_value of the equation.
  */
Ast_node* Equation::get_r_value() const
{
	return r_value;
}

/**
  * Set the left value of the equation.
  */
void Equation::set_l_value(const Ast_instance& lvalue)
{
	l_value = lvalue;
}

/**
  * Set the left value of the equation.
  */
void Equation::set_r_value(Ast_node* rvalue)
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
string Equation::to_string() const
{
	string eq;

	// Save l_value.
	eq.append(l_value.to_string());
	eq.append("\t=\t");

	// FALTA MOSTRAR EL NUEVO ARBOL.
	eq.append(r_value->to_string());

	eq.append(";");
	return eq;
}

} // end genevalmag
