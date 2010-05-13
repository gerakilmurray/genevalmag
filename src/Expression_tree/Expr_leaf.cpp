/**
  *  \file      Expr_leaf.cpp
  *  \brief     Implementation element of an Attribute Syntax Tree (AST).
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include "../../include/Expression_tree/Expr_leaf.h"

namespace genevalmag
{

Expr_leaf::Expr_leaf():Expression(){}

/**
  * Destructor of Expr_leaf.
  */
Expr_leaf::~Expr_leaf(){};

/**
  * Compares the Expr_leaf with other.
  */
bool Expr_leaf::equals(const Expr_leaf *other) const
{
    return (to_string().compare(other->to_string()) == 0);
}

}
