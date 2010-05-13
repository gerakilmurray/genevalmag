/**
  *  \file      Expression.cpp
  *  \brief     Implementation of an Expression.
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include "../../include/Expression_tree/Expression.h"

namespace genevalmag
{

/**
  * Contructor of Expression.
  */
Expression::Expression()
{
	parent 				= NULL;
	conflict    		= -1;
	type_synthetized 	= "";
}

/**
  * Destructor of Expression.
  */
Expression::~Expression(){};

/**
  * Returns the parent pointer of the Expression.
  */
const Expression *Expression::get_parent() const
{
	return parent;
}

/**
  * Returns the type synthetized of the Expression.
  */
const string Expression::get_type_synthetized() const
{
	return type_synthetized;
}

/**
  * Returns the precendence wath produces the conflict.
  */
int Expression::get_conflict() const
{
	return conflict;
}

/**
  * Sets the parent pointer of the Expression.
  */
void Expression::set_parent(const Expression *new_parent)
{
	parent = new_parent;
}

/**
  * Returns the type synthetized of the Expression.
  */
void Expression::set_type_synthetized(string new_type_synthetized)
{
	type_synthetized = new_type_synthetized;
}

/**
  * Sets the parent pointer of the Expression in NULL.
  */
void Expression::delete_parent()
{
	parent = NULL;
}

/**
  * Turn on the conflict flag with the precendence wath produces.
  */
void Expression::active_conflict(int prec_conflict)
{
	conflict = prec_conflict;
}

/**
  * Turn off the conflict flag with negative precendence.
  */
void Expression::desactive_conflict()
{
	conflict = -1;
}

} /* end namespace */
