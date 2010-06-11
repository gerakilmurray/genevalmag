/**
  *  \file		Semantics_checks.h
  *  \brief		Header method Semantics checks of Attribute grammar.
  *  \date      11/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef SEMANTICS_CKECKS_H_
#define SEMANTICS_CKECKS_H_

#include <string>
#include <map>

#include "../Expression_tree/Expr_function.h"
#include "../Attr_grammar/Rule.h"
#include "../Attr_grammar/Symbol.h"

namespace genevalmag
{

class Semantics_checks
{
	private:
		/**
		  * \var current_precedence_level
		  * \brief Level current of precedence.
		  */
		unsigned short precedence_level;

		/**
		  * \var index_syntax_order
		  * \brief Counter of syntax order.
		  */
		unsigned short index_syntax_order;

		/**
		  * Check and correct the precendence of the operator in a subtree.
		  * @param subtree
		  * @param index_root_subtree
		  */
		void correct_subtree(Expr_function **subtree, int index_root_subtree);

	public:
		/**
		  * Contructor empty of Semantics checks.
		  */
		Semantics_checks();

		/**
		  * Destructor of Semantics checks.
		  */
		~Semantics_checks();

		/**
		  * Returns the precedence level.
		  * @return
		  */
		unsigned short get_precedence_level() const;
		/**
		  * Returns the current index of the syntax order.
		  * @return
		  */
	    unsigned short get_index_syntax_order() const;

	    /**
		  * Increments the level because a new parenthesis opening.
		  */
		void increment_precedence_level();
		/**
		  * Decrements the level because a parenthesis closing.
		  */
		void decrement_precedence_level();
		/**
		  * Increments the syntax order global.
		  */
		void increment_index_syntax_order();

	    /**
		  * Resets all variables that affect in the precedence analisys.
		  */
		void reset_semantic_context();

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
		  *
		  * @param root_tree
		  */
		void correct_precedence(Expr_function **root_tree);

		/**
		  * Controls around the tree, that any operator who applies more than once on
		  * the same level is associated according to the signature.
		  * If it detects conflicts modifying the expression tree with rotations and
		  * resources to continue controlling.
		  *
		  * @param root_tree
		  */
		void correct_associativity(Expr_function **root_tree);

		/**
		  * Verifies that all non-terminals in the grammar has defines in a rule.
		  * That is, it is the left value of some rule of grammar.
		  *
		  * @param rules
		  * @param non_terminals
		  * @return
		  */
		bool check_all_defined_non_terminal(const map <unsigned short, Rule> &rules, const map <string, Symbol> &non_terminals);

		/**
		  * Computes the boolean adjacency matrix of all the rules of the attributes grammar,
		  * then computes the Warshall algorithm for transitive closure and thus can identify
		  * from the initial symbol all symbols reachable.
		  *
		  * @param rules
		  * @param non_terminals
		  * @param init_symbol
		  * @return
		  */
		bool check_reachability(const map <unsigned short, Rule> &rules, const map <string, Symbol> &non_terminals, const Symbol *init_symbol);

		/**
		  * Checks that all synthetized attributes of the left symbols of all rule are defined with an equation.
		  * And all inherit attributes of all right symbol too.
		  *
		  * @param rules
		  * @return
		  */
		bool check_well_defined_AG(const map <unsigned short, Rule> &rules);
};

} /* end genevalmag */

#endif /* SEMANTICS_CKECKS_H_ */
