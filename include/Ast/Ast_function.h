/**
  *  \file      Ast_function.h
  *  \brief     Function element of an Attribute Syntax Tree (AST).
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef AST_FUNCTION_H_
#define AST_FUNCTION_H_

#include "Ast_inner_node.h"
#include "../Attr_grammar/Function.h"

namespace genevalmag
{

/**
  * This constant is used for set a function on operator.
  */
const bool IS_OPERATOR (true);

class Ast_function: public Ast_inner_node
{
    private:
        const Function    *func;
        unsigned short    precedence_level;
        unsigned short    syntax_order;

        /**
          * Method of copy the Ast_function, STL-like C++.
          */
        void copy(const Ast_function &other);
        /**
          * Method destroy Ast_function, STL-like C++.
          */
        void destroy();

    public:
        /**
          * Constructor empty of Ast_function.
          */
        Ast_function();
        /**
          * Constructor copy of Ast_function.
          */
        Ast_function(const Ast_function &other);

        /**
          * Destructor of Ast_function.
          */
        virtual ~Ast_function();

        /**
          * Operator assign(=) of Ast_function.
          */
        Ast_function &operator=(const Ast_function &other);

        /**
          * Returns the function pointer of the Ast_function.
          */
        const Function *get_function() const;
        /**
          * Returns the precedence level of the Ast_function.
          */
        unsigned short get_precedence_level() const;
        /**
          * Returns the syntax order of the Ast_function.
          */
        unsigned short get_syntax_order() const;

        /**
          * Sets the function pointer of the Ast_function.
          */
        void set_function(const Function *func);
        /**
          * Sets the precedence level of the Ast_function.
          */
        void set_precedence_level(unsigned short p_level);
        /**
          * Sets the syntax order of the Ast_function.
          */
        void set_syntax_order(unsigned short s_order);

        /**
          * Returns if the function of Ast_function is prefix.
          */
        bool is_prefix() const;
        /**
          * Returns if the function of Ast_function is infix.
          */
        bool is_infix() const;
        /**
          * Returns if the function of Ast_function is postfix.
          */
        bool is_postfix() const;

        /**
          * Returns if both Ast_functions are in the same precedence level.
          */
        bool is_comparable(const Ast_function *other) const;
        /**
          * Return:
          *        = O        when is same precedence
          *        < 0        when other have great precedence
          *        > 0        when other have small precedence
          */
        int compare_precedence(const Ast_function *other) const;
        /**
          * Return:
          *        = O        when is same order
          *        < 0        when other have great order
          *        > 0        when other have small order
          */
        int compare_order(const Ast_function *other) const;

        /**
          * Generate and return a string reprensentation of a Ast_function.
          *
          * If is a pure function:
          *     Result= \<func_name\> "(" child[0], ... , child[n] ")"
          *
          * If is an infix binary operator:
          *     Result= "(" child[0] \<op_name\> child[1] ")"
          *
          * If is an prefix unary operator:
          *     Result= \<op_name\> "(" child[0] ")"
          *
          * If is an postfix unary operator:
          *     Result= "(" child[0] ")" \<op_name\>
          */
        string to_string() const;
};

} /* end genevalmag */

#endif /* AST_FUNCTION_H_ */
