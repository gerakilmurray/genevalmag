/**
  *  \file		Ast_leaf.h
  *  \brief
  *  \date		21/12/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef AST_LEAF_H_
#define AST_LEAF_H_

#include "Ast_node.h"

namespace genevalmag
{

class Ast_leaf: public Ast_node
{
public:
	virtual ~Ast_leaf(){};
	virtual string to_string() const = 0;
	virtual string value_s() const = 0;
	virtual bool equals(const Ast_leaf * node) const = 0;
};

} // end genevalmag

#endif /* AST_LEAF_H_ */
