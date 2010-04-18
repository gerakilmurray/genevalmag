/**
  *  \file      Ast_literal.h
  *  \brief     Literal element of an Attribute Syntax Tree (AST).
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef AST_LITERAL_H_
#define AST_LITERAL_H_

#include "Ast_leaf.h"

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
    k_string
};

class Ast_literal: public Ast_leaf
{
    private:
		/**
		  * /var value.
		  * /brief literal value.
		  */
        string          value;
        /**
		  * /var type.
		  * /brief literal type: this type may be k_int, k_float, k_char, k_string.
		  */
        literal_type    type;

        /**
          * Method of copy the Ast_literal, STL-like C++.
          */
        void copy(const Ast_literal &other);
        /**
          * Method destroy Ast_literal, STL-like C++.
          */
        void destroy();

    public:
        /**
          * Constructor empty of Ast_literal.
          */
        Ast_literal();
        /**
          * Constructor copy of Ast_literal.
          */
        Ast_literal(const Ast_literal &other);

        /**
          * Destructor of Ast_literal.
          */
        virtual ~Ast_literal();

        /**
          * Operator assign(=) of Ast_literal.
          */
        Ast_literal &operator=(const Ast_literal &other);

        /**
          * Returns the type of the Ast_literal.
          */
        literal_type get_type() const;

        /**
          * Returns the value of the Ast_literal.
          */
        string get_value() const;

        /**
          * Sets the type of the Ast_literal.
          */
        void set_type(literal_type new_type);

        /**
          * Sets the value of the Ast_literal.
          */
        void set_value(string new_value);

        /**
          * Generate and return a string reprensentation of a Ast_literal.
          *
          * Result= literal
          *
          * Ex: 1      -> int
          *     1.0    -> float
          *     '1'    -> char
          *     "1"    -> string
          */
        string to_string() const;
};

} /* end genevalmag */

#endif /* AST_LITERAL_H_ */
