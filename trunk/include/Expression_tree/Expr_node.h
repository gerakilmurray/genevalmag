/**
  *  \file      Expr_node.h
  *  \brief     Abstract recursive element of an Attribute Syntax Tree (AST).
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef AST_INNER_NODE_H_
#define AST_INNER_NODE_H_

#include <vector>

#include "Expression.h"

namespace genevalmag
{

class Expr_node: public Expression
{
    protected:
	/**
	  * \var childs.
	  * \brief Childs's vector of node.
	  */
        vector <Expression*> childs;

    public:
        /**
		  * Constructor of Expr_node.
          * @return
          */
        Expr_node();

        /**
          * Destructor of Expr_node.
          * @return
          */
        virtual ~Expr_node();

        /**
          * Returns the vector with all children of the Expr_function.
          * @return
          */
        const vector<Expression*> &get_childs() const;

        /**
          * Returns the index-child of the Expr_function.
          * @param index
          * @return
          */
        Expression *get_child(int index) const;

        /**
          * Replaces index-child of the Expr_function with other.\n
          * Updates the parent of the child.
          * @param index
          * @param other
          */
        void replace_child(int index, Expression *other);

        /**
          * Adds a child in Expr_function.\n
          * Updates the parent of the child.
          * @param new_child
          */
        void add_child(Expression *new_child);

        /**
          * Generate and return a string reprensentation of an Expr_node.
          * @return
          */
        virtual string to_string() const = 0;
};

} /* end genevalmag */

#endif /* AST_INNER_NODE_H_ */
