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
    k_string,
    k_bool
};

class Ast_literal: public Ast_leaf
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
          * Method of copy the Ast_literal, STL-like C++.
          * @param other
          */
        void copy(const Ast_literal &other);
        /**
          * Method destroy Ast_literal, STL-like C++.
          */
        void destroy();

    public:
        /**
          * Constructor empty of Ast_literal.
          * @return
          */
        Ast_literal();
        /**
          * Constructor copy of Ast_literal.
          * @param other
          * @return
          */
        Ast_literal(const Ast_literal &other);

        /**
          * Destructor of Ast_literal.
          * @return
          */
        virtual ~Ast_literal();

        /**
          * Operator assign(=) of Ast_literal.
          * @param other
          * @return
          */
        Ast_literal &operator=(const Ast_literal &other);

        /**
          * Returns the type of the Ast_literal.
          * @return
          */
        literal_type get_type() const;

        /**
          * Returns the value of the Ast_literal.
          * @return
          */
        string get_value() const;

        /**
          * Sets the type of the Ast_literal.
          * @param new_type
          */
        void set_type(literal_type new_type);

        /**
          * Sets the value of the Ast_literal.
          * @param new_value
          */
        void set_value(string new_value);

        /**
          * Generate and return a string reprensentation of a Ast_literal.\n
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
