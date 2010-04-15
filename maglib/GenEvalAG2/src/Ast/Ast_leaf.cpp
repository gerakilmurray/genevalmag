/**
  *  \file      Ast_leaf.cpp
  *  \brief     Implementation element of an Attribute Syntax Tree (AST).
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include "../../include/Ast/Ast_leaf.h"

namespace genevalmag
{

Ast_leaf::Ast_leaf():Ast_node(){}

/**
  * Destructor of Ast_leaf.
  */
Ast_leaf::~Ast_leaf(){};

/**
  * Compares the Ast_leaf with other.
  */
bool Ast_leaf::equals(const Ast_leaf *other) const
{
    return (to_string().compare(other->to_string()) == 0);
}

}
