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
		  * Constructor of Ast_leaf.
	      * @return
          */
		Ast_leaf();
        /**
          * Destructor of Ast_leaf.
		  * @return
		  */
        virtual ~Ast_leaf();

        /**
          * Generates and returns a string reprensentation of a Ast_leaf.
          * @return
          */
        virtual string to_string() const = 0;

        /**
          * Compares the Ast_leaf with other.
          * @param other
          * @return
          */
        bool equals(const Ast_leaf *other) const;
};

} /* end genevalmag */

#endif /* AST_LEAF_H_ */
