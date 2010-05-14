/**
  *  \file      Expr_function.h
  *  \brief     Function element of an Expression.
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef EXPR_FUNCTION_H_
#define EXPR_FUNCTION_H_

#include "Expr_node.h"
#include "../Attr_grammar/Function.h"

namespace genevalmag
{

/**
  * This constant is used for set a function on operator.
  */
const bool IS_OPERATOR (true);

class Expr_function: public Expr_node
{
    private:
		/**
		  * \var func.
		  * \brief Function associates with Expr_function.
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
          * Method of copy the Expr_function, STL-like C++.
          * @param other
          */
        void copy(const Expr_function &other);
        /**
          * Method destroy Expr_function, STL-like C++.
          */
        void destroy();

    public:
        /**
          * Constructor empty of Expr_function.
          * @return
          */
        Expr_function();
        /**
          * Constructor copy of Expr_function.
          * @param other
          * @return
          */
        Expr_function(const Expr_function &other);

        /**
          * Destructor of Expr_function.
          * @return
          */
        virtual ~Expr_function();

        /**
          * Operator assign(=) of Expr_function.
          * @param other
          * @return
          */
        Expr_function &operator=(const Expr_function &other);

        /**
          * Returns the function pointer of the Expr_function.
          * @return
          */
        const Function *get_function() const;
        /**
          * Returns the precedence level of the Expr_function.
          * @return
          */
        unsigned short get_precedence_level() const;
        /**
          * Returns the syntax order of the Expr_function.
          * @return
          */
        unsigned short get_syntax_order() const;

        /**
          * Sets the function pointer of the Expr_function.
          * @param function
          */
        void set_function(const Function *function);
        /**
          * Sets the precedence level of the Expr_function.
          * @param p_level
          */
        void set_precedence_level(unsigned short p_level);
        /**
          * Sets the syntax order of the Expr_function.
          * @param s_order
          */
        void set_syntax_order(unsigned short s_order);

        /**
          * Returns if the function of Expr_function is prefix.
          * @return
          */
        bool is_prefix() const;
        /**
          * Returns if the function of Expr_function is infix.
          * @return
          */
        bool is_infix() const;
        /**
          * Returns if the function of Expr_function is postfix.
          * @return
          */
        bool is_postfix() const;

        /**
          * Returns if both Expr_functions are in the same precedence level.
          * @param other
          * @return
          */
        bool is_comparable(const Expr_function *other) const;
        /**
          * Returns:\n
          *        \= O        when is same precedence\n
          *        \< 0        when other have great precedence\n
          *        \> 0        when other have small precedence\n
          * @param other
          * @return
          */
        int compare_precedence(const Expr_function *other) const;
        /**
          * Returns:\n
          *        \= O        when is same order\n
          *        \< 0        when other have great order\n
          *        \> 0        when other have small order\n
          * @param other
          * @return
          */
        int compare_order(const Expr_function *other) const;

        /**
          * Generate and return a string reprensentation of a Expr_function.\n
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

#endif /* EXPR_FUNCTION_H_ */
