/**
  *  \file      Ast_inner_node.cpp
  *  \brief     Implementation element of an Attribute Syntax Tree (AST).
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include "../../include/Ast/Ast_inner_node.h"

namespace genevalmag
{

Ast_inner_node::Ast_inner_node():Ast_node(){}

/**
  * Destructor of Ast_inner_node.
  */
Ast_inner_node::~Ast_inner_node()
{
	for (unsigned int i(0); i < childs.size(); i++)
	{
		delete(childs[i]);
	}
}

/**
  * Returns the vector with all children of the Ast_function.
  */
const vector<Ast_node*> &Ast_inner_node::get_childs() const
{
	return childs;
}

/**
  * Returns the index-child of the Ast_function.
  */
Ast_node *Ast_inner_node::get_child(int index) const
{
	return childs[index];
}

/**
  * Replaces index-child of the Ast_function with other.
  * Updates the parent of the child.
  */
void Ast_inner_node::replace_child(int index, Ast_node *other)
{
	childs[index] = other;
	other->set_parent(this);
}

/**
  * Adds a child in Ast_function.
  * Updates the parent of the child.
  */
void Ast_inner_node::add_child(Ast_node *new_child)
{
	childs.insert(childs.begin(), new_child);
	new_child->set_parent(this);
}

} /* end genevalmag */
