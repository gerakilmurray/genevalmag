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
		/**
		  * \var func.
		  * \brief Function associates with Ast_function.
		  */
        const Function    *func;
        /**
		  * \var precedence_level.
          * \brief Level precedence of the function.
          */
        unsigned short    precedence_level;
        /**
          * \var syntax_order.
          * \brief Syntax order in the parse.
          */
        unsigned short    syntax_order;

        /**
          * Method of copy the Ast_function, STL-like C++.
          * @param other
          */
        void copy(const Ast_function &other);
        /**
          * Method destroy Ast_function, STL-like C++.
          */
        void destroy();

    public:
        /**
          * Constructor empty of Ast_function.
          * @return
          */
        Ast_function();
        /**
          * Constructor copy of Ast_function.
          * @param other
          * @return
          */
        Ast_function(const Ast_function &other);

        /**
          * Destructor of Ast_function.
          * @return
          */
        virtual ~Ast_function();

        /**
          * Operator assign(=) of Ast_function.
          * @param other
          * @return
          */
        Ast_function &operator=(const Ast_function &other);

        /**
          * Returns the function pointer of the Ast_function.
          * @return
          */
        const Function *get_function() const;
        /**
          * Returns the precedence level of the Ast_function.
          * @return
          */
        unsigned short get_precedence_level() const;
        /**
          * Returns the syntax order of the Ast_function.
          * @return
          */
        unsigned short get_syntax_order() const;

        /**
          * Sets the function pointer of the Ast_function.
          * @param func
          */
        void set_function(const Function *func);
        /**
          * Sets the precedence level of the Ast_function.
          * @param p_level
          */
        void set_precedence_level(unsigned short p_level);
        /**
          * Sets the syntax order of the Ast_function.
          * @param s_order
          */
        void set_syntax_order(unsigned short s_order);

        /**
          * Returns if the function of Ast_function is prefix.
          * @return
          */
        bool is_prefix() const;
        /**
          * Returns if the function of Ast_function is infix.
          * @return
          */
        bool is_infix() const;
        /**
          * Returns if the function of Ast_function is postfix.
          * @return
          */
        bool is_postfix() const;

        /**
          * Returns if both Ast_functions are in the same precedence level.
          * @param other
          * @return
          */
        bool is_comparable(const Ast_function *other) const;
        /**
          * Returns:\n
          *        \= O        when is same precedence\n
          *        \< 0        when other have great precedence\n
          *        \> 0        when other have small precedence\n
          * @param other
          * @return
          */
        int compare_precedence(const Ast_function *other) const;
        /**
          * Returns:\n
          *        \= O        when is same order\n
          *        \< 0        when other have great order\n
          *        \> 0        when other have small order\n
          * @param other
          * @return
          */
        int compare_order(const Ast_function *other) const;

        /**
          * Generate and return a string reprensentation of a Ast_function.\n
          *\n
          * If is a pure function:\n
          *     Result= \<func_name\> "(" child[0], ... , child[n] ")"\n
          *\n
          * If is an infix binary operator:\n
          *     Result= "(" child[0] \<op_name\> child[1] ")"\n
          *\n
          * If is an prefix unary operator:\n
          *     Result= \<op_name\> "(" child[0] ")"\n
          *\n
          * If is an postfix unary operator:\n
          *     Result= "(" child[0] ")" \<op_name\>\n
          * @return
          */
        string to_string() const;
};

} /* end genevalmag */

#endif /* AST_FUNCTION_H_ */
