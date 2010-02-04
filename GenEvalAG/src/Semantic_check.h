/**
  *  \file		Semantic_check.h
  *  \brief		Header method semantic check of Attribute grammar.
  *  \date		28/09/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */
#ifndef SEMCKECK_H_
#define SEMCKECK_H_

#include "ast/Ast_function.h"
#include "Rule.h"

using namespace genevalmag;

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
bool check_reachability(const map <string, Rule> rules, const map <string, Symbol> symbols, string init_rule);

/**
  * Increment the level because a new parenthesis opening.
  */
void increment_level(char name);

/**
  * Decrement the level because a parenthesis closing.
  */
void decrement_level(char name);

/**
  * Resets all variables that affect in the precedence analisys.
  */
void reset_semantic_context();

#endif
