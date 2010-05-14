/**
  *  \file      Expr_node.cpp
  *  \brief     Implementation element of an Expression.
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include "../../include/Expression_tree/Expr_node.h"

namespace genevalmag
{

Expr_node::Expr_node():Expression(){}

/**
  * Destructor of Expr_node.
  */
Expr_node::~Expr_node()
{
	for (unsigned int i(0); i < childs.size(); i++)
	{
		delete(childs[i]);
	}
}

/**
  * Returns the vector with all children of the Expr_function.
  */
const vector<Expression*> &Expr_node::get_childs() const
{
	return childs;
}

/**
  * Returns the index-child of the Expr_function.
  */
Expression *Expr_node::get_child(int index) const
{
	return childs[index];
}

/**
  * Replaces index-child of the Expr_function with other.
  * Updates the parent of the child.
  */
void Expr_node::replace_child(int index, Expression *other)
{
	childs[index] = other;
	other->set_parent(this);
}

/**
  * Adds a child in Expr_function.
  * Updates the parent of the child.
  */
void Expr_node::add_child(Expression *new_child)
{
	childs.insert(childs.begin(), new_child);
	new_child->set_parent(this);
}

} /* end genevalmag */
