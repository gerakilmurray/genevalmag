/**
  *  \file      Expr_leaf.h
  *  \brief     Abstract final element of an Expression.
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef EXPR_LEAF_H_
#define EXPR_LEAF_H_

#include "Expression.h"

namespace genevalmag
{

class Expr_leaf: public Expression
{
    public:
		/**
		  * Constructor of Expr_leaf.
	      * @return
          */
		Expr_leaf();
        /**
          * Destructor of Expr_leaf.
		  * @return
		  */
        virtual ~Expr_leaf();

        /**
          * Generates and returns a string reprensentation of a Expr_leaf.
          * @return
          */
        virtual string to_string() const = 0;

        /**
          * Compares the Expr_leaf with other.
          * @param other
          * @return
          */
        bool equals(const Expr_leaf *other) const;
};

} /* end genevalmag */

#endif /* EXPR_LEAF_H_ */
