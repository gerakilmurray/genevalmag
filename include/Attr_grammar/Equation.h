/**
  *  \file      Equation.h
  *  \brief     Class of the equations of the attribute grammar.
  *  \date      05/11/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef EQUATION_H_
#define EQUATION_H_

#include "../Expression_tree/Expression.h"
#include "../Expression_tree/Expr_node.h"
#include "../Expression_tree/Expr_instance.h"

namespace genevalmag
{

class Equation
{
    private:
		/**
		  * \var eq_id
		  * \brief Equation's identifier.
		  */
        unsigned short      eq_id;
		/**
		  * \var eq_id
		  * \brief Equation's left value.
		  */
        Expr_instance        l_value;
		/**
		  * \var eq_id
		  * \brief Equation's tree expression.
		  */
        const Expression      *r_value;

        /**
          * \var count_ref
          * \brief Similar to a Smart Pointer to manage the release of the memory tree.
          *        When this is 0, all memory is freed from the tree.
          */
        unsigned short      *count_ref;

        /**
          * Method of copy the equation, STL-like C++.
          * @param other
          */
        void copy(const Equation &other);
        /**
          * Method destroy equation, STL-like C++.
          */
        void destroy();

        /**
          * Returns the count reference.
          * @return
          */
        unsigned short *_get_count_ref() const;

        /**
          * Traverse the equation tree while saves only the Expr_instance nodes in the vector result.
          * @param head
          * @param result
          */
        void inorder_only_instance(const Expression *head, vector<const Expr_instance*> &result) const;

    public:
        /**
          * Constructor empty of equation.
          */
        Equation();
        /**
          * Contructor copy of Equation.
          * @param other
          * @return
          */
        Equation(const Equation &other);

        /**
          * Destructor of equation.
          */
        virtual ~Equation();

        /**
          * Operator assign(=) of Equation.
          * @param other
          * @return
          */
        Equation &operator=(const Equation &other);

        /**
          * Returns the l_value of the equation.
          * @return
          */
        const Expr_instance *get_l_value() const;
        /**
          * Returns the r_value of the equation.
          * @return
          */
        const Expression *get_r_value() const;
        /**
          * Returns the id of the equation.
          * @return
          */
        const unsigned short get_id() const;

        /**
          * Sets the id of the equation.
          * @param id
          */
        void set_id(const unsigned short id);
        /**
          * Sets the left value of the equation.
          * @param lvalue
          */
        void set_l_value(const Expr_instance &lvalue);
        /**
          * Sets the rigth value of the equation: is a tree.
          * @param rvalue
          */
        void set_r_value(const Expression *rvalue);

        /**
          * Traverse the equation tree while saves only the Expr_leaf nodes in the vector result.
          * @param head
          * @param result
          */
        void inorder_only_leaf(const Expression *head, vector<const Expr_leaf*> &result) const;

        /**
          * Returns the pointer of the Expression.
          * @return
          */
        const vector<const Expr_instance*> get_instance_right_side() const;

        /**
          * Generates and returns a string reprensentation of an Equation.\n
          *\n
          * Result = \<l_value\> "=" \<r_value\> ";"\n
          *\n
          * where \<l_value\> = "instance_attr" and \<r_value\> is= "list of node_ast"\n
          *
          * @return
          */
        const string to_string() const;

        /**
          * Compares the equation with other.
          * @param other
          * @return
          */
        const bool equals(const Equation &other) const;

        /**
          * Generates and returns the string key that identifies an Equation definitely.\n
          *\n
          * Result = \<l_value\>\<r_value\>\n
          *\n
          * where \<l_value\> = "instance_attr" and \<r_value\> is= "list of node_ast"\n
          *
          * @return
          */
        const string key() const;
};

} /* end genevalmag */

#endif /* EQUATION_H_ */
