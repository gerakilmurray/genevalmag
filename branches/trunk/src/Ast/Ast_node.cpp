/**
  *  \file      Ast_node.cpp
  *  \brief     Implementation of an Attribute Syntax Tree (AST).
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include "../../include/Ast/Ast_node.h"

namespace genevalmag
{

/**
  * Contructor of Ast_node.
  */
Ast_node::Ast_node()
{
	parent 				= NULL;
	conflict    		= -1;
	type_synthetized 	= "";
}

/**
  * Destructor of Ast_node.
  */
Ast_node::~Ast_node(){};

/**
  * Returns the parent pointer of the Ast_node.
  */
const Ast_node *Ast_node::get_parent() const
{
	return parent;
}

/**
  * Returns the type synthetized of the Ast_node.
  */
const string Ast_node::get_type_synthetized() const
{
	return type_synthetized;
}

/**
  * Returns the precendence wath produces the conflict.
  */
int Ast_node::get_conflict() const
{
	return conflict;
}

/**
  * Sets the parent pointer of the Ast_node.
  */
void Ast_node::set_parent(const Ast_node *new_parent)
{
	parent = new_parent;
}

/**
  * Returns the type synthetized of the Ast_node.
  */
void Ast_node::set_type_synthetized(string new_type_synthetized)
{
	type_synthetized = new_type_synthetized;
}

/**
  * Sets the parent pointer of the Ast_node in NULL.
  */
void Ast_node::delete_parent()
{
	parent = NULL;
}

/**
  * Turn on the conflict flag with the precendence wath produces.
  */
void Ast_node::active_conflict(int prec_conflict)
{
	conflict = prec_conflict;
}

/**
  * Turn off the conflict flag with negative precendence.
  */
void Ast_node::desactive_conflict()
{
	conflict = -1;
}

} /* end namespace */
