/**
  *  \file      Ast_leaf.h
  *  \brief     Abstract final element of an Attribute Syntax Tree (AST).
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef AST_LEAF_H_
#define AST_LEAF_H_

#include "Ast_node.h"

namespace genevalmag
{

class Ast_leaf: public Ast_node
{
    public:
		/**
		  * constructor of Ast_leaf.
		  */
		Ast_leaf();
        /**
          * Destructor of Ast_leaf.
          */
        virtual ~Ast_leaf();

        /**
          * Generate and return a string reprensentation of a Ast_leaf.
          */
        virtual string to_string() const = 0;

        /**
          * Compares the Ast_leaf with other.
          */
        bool equals(const Ast_leaf *other) const;
};

} /* end genevalmag */

#endif /* AST_LEAF_H_ */
