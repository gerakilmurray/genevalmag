/**
  *  \file      Ast_inner_node.h
  *  \brief     Abstract recursive element of an Attribute Syntax Tree (AST).
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef AST_INNER_NODE_H_
#define AST_INNER_NODE_H_

#include <vector>

#include "Ast_node.h"

namespace genevalmag
{

class Ast_inner_node: public Ast_node
{
    protected:
	/**
	  * /var childs.
	  * /brief Childs's vector of node.
	  */
        vector <Ast_node*> childs;

    public:
        /**
		  * Constructor of Ast_inner_node.
          * @return
          */
        Ast_inner_node();

        /**
          * Destructor of Ast_inner_node.
          * @return
          */
        virtual ~Ast_inner_node();

        /**
          * Returns the vector with all children of the Ast_function.
          * @return
          */
        const vector<Ast_node*> &get_childs() const;

        /**
          * Returns the index-child of the Ast_function.
          * @param index
          * @return
          */
        Ast_node *get_child(int index) const;

        /**
          * Replaces index-child of the Ast_function with other.
          * Updates the parent of the child.
          * @param index
          * @param other
          */
        void replace_child(int index, Ast_node *other);

        /**
          * Adds a child in Ast_function.
          * Updates the parent of the child.
          * @param new_child
          */
        void add_child(Ast_node *new_child);

        /**
          * Generate and return a string reprensentation of an Ast_inner_node.
          * @return
          */
        virtual string to_string() const = 0;
};

} /* end genevalmag */

#endif /* AST_INNER_NODE_H_ */
