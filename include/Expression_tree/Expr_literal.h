/**
  *  \file      Expr_literal.h
  *  \brief     Literal element of an Attribute Syntax Tree (AST).
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef AST_LITERAL_H_
#define AST_LITERAL_H_

#include "Expr_leaf.h"

namespace genevalmag
{

/**
  * Type of basics literals.
  */
enum literal_type
{
    k_int,
    k_float,
    k_char,
    k_string,
    k_bool
};

class Expr_literal: public Expr_leaf
{
    private:
		/**
		  * \var value.
		  * \brief literal value.
		  */
        string          value;
        /**
		  * \var type.
		  * \brief literal type: this type may be k_int, k_float, k_char, k_string.
		  */
        literal_type    type;

        /**
          * Method of copy the Expr_literal, STL-like C++.
          * @param other
          */
        void copy(const Expr_literal &other);
        /**
          * Method destroy Expr_literal, STL-like C++.
          */
        void destroy();

    public:
        /**
          * Constructor empty of Expr_literal.
          * @return
          */
        Expr_literal();
        /**
          * Constructor copy of Expr_literal.
          * @param other
          * @return
          */
        Expr_literal(const Expr_literal &other);

        /**
          * Destructor of Expr_literal.
          * @return
          */
        virtual ~Expr_literal();

        /**
          * Operator assign(=) of Expr_literal.
          * @param other
          * @return
          */
        Expr_literal &operator=(const Expr_literal &other);

        /**
          * Returns the type of the Expr_literal.
          * @return
          */
        literal_type get_type() const;

        /**
          * Returns the value of the Expr_literal.
          * @return
          */
        string get_value() const;

        /**
          * Sets the type of the Expr_literal.
          * @param new_type
          */
        void set_type(literal_type new_type);

        /**
          * Sets the value of the Expr_literal.
          * @param new_value
          */
        void set_value(string new_value);

        /**
          * Generate and return a string reprensentation of a Expr_literal.\n
          *\n
          * Result= literal\n
          *\n
          * Ex: 1      -> int, short or long\n
          *     1.0    -> float or double\n
          *     '1'    -> char or wchar_t\n
          *     "1"    -> string\n
          *     true   -> bool\n
          * @return
          */
        string to_string() const;
};

} /* end genevalmag */

#endif /* AST_LITERAL_H_ */
