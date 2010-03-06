/**
  *  \file		Ast_leaf.h
  *  \brief		Abstract final element of an Attribute Syntax Tree (AST).
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

		bool equals(const Ast_leaf *other) const
		{
			return (to_string().compare(other->to_string()) == 0);
		}
};

} /* end genevalmag */

#endif /* AST_LEAF_H_ */
