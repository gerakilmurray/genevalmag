/**
  *  \file      Ast_node.h
  *  \brief     Abstract element of an Attribute Syntax Tree (AST).
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef AST_NODE_H_
#define AST_NODE_H_

#include <string>

#include "../Attr_grammar/Sort.h"

using namespace std;

namespace genevalmag
{

class Ast_node
{
    protected:
		/**
		  * \var parent.
		  * \brief Father of node.
		  */
        const Ast_node    *parent;
        /**
		  * \var type_synthetized.
		  * \brief Type of node: Obtains of parse.
		  */
        string            type_synthetized;
        /**
		  * \var conflict.
		  * \brief Mark when conflicted node.\n
		  *        This conflict is a conflict in the parse.\n
		  *        Used for define the precedence of function.\n
		  */
        int               conflict;

    public:
        /**
          * Constructor of Ast_node.
          * @return
          */
        Ast_node();

        /**
          * Destructor of Ast_node.
          * @return
          */
        virtual ~Ast_node();

        /**
          * Returns the parent pointer of the Ast_node.
          * @return
          */
        const Ast_node *get_parent() const;

        /**
          * Returns the type synthetized of the Ast_node.
          * @return
          */
        const string get_type_synthetized() const;

        /**
          * Returns the precendence wath produces the conflict.
          * @return
          */
        int get_conflict() const;

        /**
          * Sets the parent pointer of the Ast_node.
          * @param new_parent
          */
        void set_parent(const Ast_node *new_parent);

        /**
          * Returns the type synthetized of the Ast_node.
          * @param new_type_synthetized
          */
        void set_type_synthetized(string new_type_synthetized);

        /**
          * Sets the parent pointer of the Ast_node in NULL.
          */
        void delete_parent();

        /**
          * Turn on the conflict flag with the precendence wath produces.
          * @param prec_conflict
          */
        void active_conflict(int prec_conflict);

        /**
          * Turn off the conflict flag with negative precendence.
         */
        void desactive_conflict();

        /**
          * Generate and return a string reprensentation of a Ast_node.
          * @return
          */
        virtual string to_string() const = 0;
};

} /* end genevalmag */

#endif /* AST_NODE_H_ */
