/**
  *  \file		Semantic_check.h
  *  \brief		Header method semantic check of Attribute grammar.
  *  \date
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */
#ifndef SEMANTIC_CKECK_H_
#define SEMANTIC_CKECK_H_

#include <string>
#include <map>

#include "../Ast/Ast_function.h"
#include "../Attr_grammar/Rule.h"
#include "../Attr_grammar/Symbol.h"

namespace genevalmag
{

class Semantic_check
{
	private:
		/**
		  * /var current_precedence_level
		  * /brief Level current of precedence.
		  */
		unsigned short precedence_level;

		/**
		  * /var index_syntax_order
		  * /brief Counter of syntax order.
		  */
		unsigned short index_syntax_order;

		void correct_subtree(Ast_function** subtree, int index_root_subtree);

	public:
		Semantic_check();
		~Semantic_check();

		/**
		  * Checking from the root of the expression tree to the leaves, which all
		  * operators are applies according to their precedence.
		  * If there are conflicts resolves them doing rotations, leaving the operator
		  * with lower precedence, as the new root.
		  *
		  * Obs: The following checks are performed and only make changes in the
		  *      structure of the tree, if it fulfills the following three conditions:
		  *
		  *   - Operations that are changed are at the same level of precedence (with respect wiht parentheses).
		  *   - The syntactic order of the expression is not altered.
		  *   - The operation with higher precedence apply first.
		  */
		void correct_precedence(Ast_function ** root_tree);

		/**
		  * Controls around the tree, that any operator who applies more than once on
		  * the same level is associated according to the signature.
		  * If it detects conflicts modifying the expression tree with rotations and
		  * resources to continue controlling.
		  */
		void correct_associativity(Ast_function ** root_tree);

		/**
		  * Verifies that all non-terminals in the grammar has defines in a rule.
		  * That is, it is the left value of some rule of grammar.
		  */
		bool check_all_defined_non_terminal(const map <string, Rule> rules, const map <string, Symbol> symbols);

		/**
		  * Computes the boolean adjacency matrix of all the rules of the attributes grammar,
		  * then computes the Warshall algorithm for transitive closure and thus can identify
		  * from the initial symbol all symbols reachable.
		  */
		bool check_reachability(const map <string, Rule> &rules, const map <string, Symbol> &non_terminals, const Symbol *init_symbol);

		bool check_well_defined_AG(const map <string, Rule> rules);

		/**
		  * Increment the level because a new parenthesis opening.
		  */
		void increment_precedence_level();

		/**
		  * Decrement the level because a parenthesis closing.
		  */
		void decrement_precedence_level();

		void increment_index_syntax_order();

		/**
		  * Resets all variables that affect in the precedence analisys.
		  */
		void reset_semantic_context();

	    unsigned short get_precedence_level() const;

	    unsigned short get_index_syntax_order() const;
};

}// namespace.

#endif
