/**
  *  \file		Ast_node.h
  *  \brief		Abstract element of an Attribute Syntax Tree (AST).
  *  \date		21/12/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
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
		const Ast_node	*parent;
		string			type_synthetized;
		int				conflict;

	public:
		/**
		  * Destructor of Ast_node.
		  */
		virtual ~Ast_node(){};

		/**
		  * Returns the parent pointer of the Ast_node.
		  */
		const Ast_node *get_parent() const
		{
			return parent;
		}

		/**
		  * Returns the type synthetized of the Ast_node.
		  */
		string get_type_synthetized() const
		{
			return type_synthetized;
		}

		/**
		  * Returns the precendence wath produces the conflict.
		  */
		int get_conflict() const
		{
			return conflict;
		}

		/**
		  * Sets the parent pointer of the Ast_node.
		  */
		void set_parent(const Ast_node *new_parent)
		{
			parent = new_parent;
		}

		/**
		  * Returns the type synthetized of the Ast_node.
		  */
		void set_type_synthetized(string new_type_synthetized)
		{
			type_synthetized = new_type_synthetized;
		}

		/**
		  * Sets the parent pointer of the Ast_node in NULL.
		  */
		void delete_parent()
		{
			parent = NULL;
		}

		/**
		  * Turn on the conflict flag with the precendence wath produces.
		  */
		void active_conflict(int prec_conflict)
		{
			conflict = prec_conflict;
		}

		/**
		  * Turn off the conflict flag with negative precendence.
		  */
		void desactive_conflict()
		{
			conflict = -1;
		}

		/**
		  * Generate and return a string reprensentation of a Ast_node.
		  */
		virtual string to_string() const = 0;
};

} /* end genevalmag */

#endif /* AST_NODE_H_ */
