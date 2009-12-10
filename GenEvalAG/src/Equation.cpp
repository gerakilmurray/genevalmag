/**
  *  \file		Equation.cpp
  *  \brief		Implementation of the methods the Equation.h
  *  \date		05/11/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include "Equation.h"
#include <sstream>
#include <iostream>

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
instance_attr Equation::get_l_value () const
{
	return l_value;
}

/**
  * Return the r_value of the equation.
  */
tree<node_ast> Equation::get_r_value () const
{
	return r_value;
}

/**
  * Set the left value of the equation.
  */
void Equation::set_l_value(instance_attr lvalue)
{
	l_value = lvalue;
}

/**
  * Set the left value of the equation.
  */
void Equation::set_r_value(tree<node_ast> rvalue)
{
	r_value = rvalue;
}


/**
  * Generate and return a string reprensentation of a instance.
  *
  * Result= <symbol>[number].<attribute>
  *
  * Ex: E[0].valor
  */
string to_string_instance(instance_attr instance)
{
	string inst;
	// Save symbol's name.
	inst.append (instance.i_symb->get_name());
	// Save instance number.
	inst.append("[");
	std::stringstream ins;
	ins << instance.i_num;
	inst.append (ins.str ());
	inst.append("]");
	inst.append(".");
	// Save attribute's name.
	inst.append (instance.i_attr->get_name());
	return inst;
}
/**
  * Generate and return a string reprensentation of a function
  *
  * Result= <symbol>[number].<attribute>
  *
  * Ex: E[0].valor
  */
string to_string_literal(literal_node literal)
{
	string lit;
	lit.append("'");
	lit.append("puta");
	switch (literal.type_lit)
	{
		case k_int:
		{
			std::stringstream lit_int;
			lit_int << literal.value_lit.int_l;
			lit.append (lit_int.str ());
			break;
		}
		case k_float:
		{
			std::stringstream lit_float;
			lit_float << literal.value_lit.flt_l;
			lit.append (lit_float.str ());
			break;
		}
		case k_char:
		{
			std::stringstream lit_char;
			lit_char << literal.value_lit.ch_l;
			lit.append (lit_char.str ());
			break;
		}
		case k_string: 	lit.append(*(literal.value_lit.str_l));break;
	}
	lit.append("'");
	return lit;
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
	eq.append (to_string_instance(l_value));
	eq.append ("\t::=\t");
	// save r_value.

	for (tree<node_ast>::iterator it = r_value.begin(); it != r_value.end(); it++)
	{
	    switch (it.node->data.n_type_node)
		{
	    case k_intance: eq.append (to_string_instance(*(it.node->data.n_data.instance)));	break;
	    case k_function: eq.append (it.node->data.n_data.func->to_string());				break;
	    case k_operator: eq.append (it.node->data.n_data.oper->to_string());				break;
	    case k_literal:	eq.append (to_string_literal(*(it.node->data.n_data.literal)));		break;
	    }
		cout << "print tree" << endl;
		if (it != r_value.end ())
			eq.append (" ");
	}
	eq.append (";");
	return eq;
}

string Equation::print_literal(literal_node lit)
{
	return to_string_literal(lit);
}


} // end genevalmag
