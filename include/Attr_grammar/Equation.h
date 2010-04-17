/**
  *  \file      Equation.h
  *  \brief     Class of the equations of the grammar parsed.
  *  \date      05/11/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef EQUATION_H_
#define EQUATION_H_

#include "../Ast/Ast_node.h"
#include "../Ast/Ast_inner_node.h"
#include "../Ast/Ast_instance.h"

namespace genevalmag
{

class Equation
{
    private:
        unsigned short      eq_id;
        Ast_instance        l_value;
        const Ast_node      *r_value;

        /**
          * Similar to a Smart Pointer to manage the release of the memory tree.
          * When this is 0, all memory is freed from the tree.
          */
        unsigned short      *count_ref;

        /**
          * Method of copy the equation, STL-like C++.
          */
        void copy(const Equation &other);
        /**
          * Method destroy equation, STL-like C++.
          */
        void destroy();

        /**
          * Return the count reference.
          */
        unsigned short *_get_count_ref() const;

        /**
          * Traverse the equation tree while saves only the Ast_instance nodes in the vector result.
          */
        void inorder_only_instance(const Ast_node *head, vector<const Ast_instance*> &result) const;

    public:
        /**
          * Constructor empty of equation.
          */
        Equation();
        /**
          * Contructor copy of Equation.
          */
        Equation(const Equation &other);

        /**
          * Destructor of equation.
          */
        virtual ~Equation();

        /**
          * Operator assign(=) of Equation.
          */
        Equation &operator=(const Equation &other);

        /**
          * Returns the l_value of the equation.
          */
        const Ast_instance *get_l_value() const;
        /**
          * Returns the r_value of the equation.
          */
        const Ast_node *get_r_value() const;
        /**
          * Returns the id of the equation.
          */
        const unsigned short get_id() const;

        /**
          * Sets the id of the equation.
          */
        void set_id(const unsigned short id);
        /**
          * Sets the left value of the equation.
          */
        void set_l_value(const Ast_instance &lvalue);
        /**
          * Sets the rigth value of the equation: is a tree.
          */
        void set_r_value(const Ast_node *rvalue);

        /**
          * Traverse the equation tree while saves only the Ast_leaf nodes in the vector result.
          */
        void inorder_only_leaf(const Ast_node *head, vector<const Ast_leaf*> &result) const;

        /**
          * Returns the Ast_instance nodes of the right side of Ast tree.
          */
        const vector<const Ast_instance*> get_instance_right_side() const;

        /**
          * Generate and return a string reprensentation of an Equation.
          *
          * Result = \<l_value\> "=" \<r_value\> ";"
          *
          * where \<l_value\> = "instance_attr" and \<r_value\> is= "list of node_ast"
          */
        const string to_string() const;

        /**
          * Compares the equation with other.
          */
        const bool equals(const Equation &other) const;

        /**
          * Generate and return the string key that identifies an Equation definitely.
          *
          * Result = \<l_value\>\<r_value\>
          *
          * where \<l_value\> = "instance_attr" and \<r_value\> is= "list of node_ast"
          */
        const string key() const;
};

} /* end genevalmag */

#endif /* EQUATION_H_ */
