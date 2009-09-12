/**
  *  \file Rule.cpp
  *      \brief Implement Rule.h - The rule of a attribute grammar.
  *  \date 31/08/2009
  *  \author Kilmurray, Gerardo Luis.
  *	 \author Picco, Gonzalo Martín.
  */

#include "Rule.h"

namespace gen_eval_mag {

Rule::Rule()
{
	// TODO Auto-generated constructor stub
}

Rule::~Rule()
{
	// TODO Auto-generated destructor stub
}

NonTerminalSymbol* Rule::getLeft_symbol()
{
	return this->left_symbol;
}

Symbol** Rule::getRight_side()
{
	return this->right_side;
}

void Rule::setLeft_symbol(NonTerminalSymbol * left_symbol)
{
    this->left_symbol = left_symbol;
}

void Rule::addSymbol(const Symbol * s)
{

}

void Rule::removeSymbol(const int index)
{

}

}
