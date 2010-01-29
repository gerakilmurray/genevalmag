/**
  *  \file		Semantic_check.cpp
  *  \brief		Implementation of the methods the Semantic_check.h
  *  \date		28/09/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <stdio.h>
#include <iostream>

#include "Semantic_check.h"

/**
  * Precedence Section.
  */

/**
  * /var current_precedence_level
  * /brief Level current of precedence.
  */
unsigned short current_precedence_level = 0;

/**
  * /var index_syntax_order
  * /brief Counter of syntax order.
  */
unsigned short index_syntax_order = 0;

/**
  *	    A(op)                	 B(op)
  *    / \                	    / \
  *   B   C    -------->       D   A
  *  / \					      / \
  * D   E                        E   C
  *
  *     A(op)                 	 C(op)
  *    / \                	    / \
  *   B   C    -------->       A   E
  *      / \			      / \
  *     D   E                B   D
  */
int swap_root_child(Ast_function** old_root, int i_new_root)
{
	Ast_function *new_root = (Ast_function*)(*old_root)->get_child(i_new_root);
	new_root->set_parent((*old_root)->get_parent());

	int index_swap = -1;
	if (new_root->is_infix())
		index_swap = (i_new_root == 0)? 1: 0;
	else
		index_swap = 0;

	// Get E.  // Get D.
	Ast_node * aux = new_root->get_child(index_swap);
	// Set child E to A // Set child D to A.
	(*old_root)->replace_child(i_new_root, aux);
	// Set child A to B // Set child A to C.
	new_root->replace_child(index_swap, (*old_root));
	// Set new root B or C.
	(*old_root) = new_root;

	return index_swap;
}

/**
  *     A (op)                	 B(op)
  *    / \                	    / \
  *   B   C    -------->       D   E
  *  / \			                \
  * D   E(op)                        A
  *      \                          / \
  *       F                        F   C
  */
int swap_root_grandson(Ast_function** old_root)
{
	Ast_function *new_root = (Ast_function *)(*old_root)->get_child(0);

	int index_swap = -1;
	if (new_root->is_infix())
		index_swap = 1;
	else
		// VER CASO DE PREFIJA.
		index_swap = 0;

	Ast_function *swap = (Ast_function *)new_root->get_child(index_swap);
	new_root->set_parent((*old_root)->get_parent());
	Ast_node *grandson = swap->get_child(0);
	(*old_root)->replace_child(0, grandson);
	swap->replace_child(0, (*old_root));
	(*old_root) = new_root;
	return index_swap;
}

void check_precedence(Ast_function ** root_tree);

void check_subtree(Ast_function** subtree, int index_root_subtree)
{
	Ast_function * aux = (Ast_function*)(*subtree)->get_child(index_root_subtree);
	check_precedence(&aux);

	// Update new son by the result of recursion.
	(*subtree)->replace_child(index_root_subtree,aux);

	if (((*subtree)->compare_precedence(aux) > 0) && ((*subtree)->is_comparable(aux)))
	// The root and the child are at the same level of precedence.
	// The root should be applied first.
	{
		if ((((*subtree)->compare_order(aux) > 0) && aux->is_prefix()) ||
			(((*subtree)->compare_order(aux) < 0) && aux->is_postfix()))
		// It makes the change only if does not change the syntactic order.
		// An operation should be introduced within a prefix or postfix.
		{
			swap_root_child(subtree, index_root_subtree);
		}
	}
}

/**
  * Checking the precedence of the operators of the parcial tree.
  * If is necesary modifies the struct of tree.
  *
  * Obs: Se realizan controles sobre casos que se deben
  *
  * Solamente se realizan cambios en la estructura del arbol, si se cumplen las siguientes 3 condiciones:
  *   - Las operaciones a cambiar estan en el mismo nivel de precedencia (con respecto a los parentesis).
  *   - No se rompe el orden sintactico de la expresion.
  *   - La operacion con mayor precedencia se aplica primero.
  */
void check_precedence(Ast_function ** root_tree)
{
	if (!(*root_tree)->is_prefix() && ((*root_tree)->get_child(0)->get_conflict() > -1))
	// Special case which must complete a check of some sub-level of the tree.
	{
		if (((*root_tree)->get_function()->get_prec() > (*root_tree)->get_child(0)->get_conflict()) &&
			((*root_tree)->is_comparable((Ast_function*)(*root_tree)->get_child(0))))
		// Same level precedence and change is needed to correct conflict of precedence.
		{
			int i_subtree = swap_root_grandson(root_tree);

			// Checks that the subtree with the older root is well formed.
			Ast_function * subtree = (Ast_function*)(*root_tree)->get_child(i_subtree);
			check_subtree(&subtree,0);

			// Updates the main tree, with the new root of subtree.
			(*root_tree)->replace_child(i_subtree,subtree);

			// Only requires checking the main tree root with his new son.
			check_precedence(root_tree);
		}
		// Turn off the flag.
		(*root_tree)->get_child(0)->desactive_conflict();
		// Don't necesary continue with normal behavior, because the special case performs all change.
		return;
	}

	// Normal behavior.
	int i_child = 0;
	while (i_child < (*root_tree)->get_function()->get_arity())
	// It covers all children.
	{
		// Detecting if the child is of Ast_function type.
		Ast_function* node = dynamic_cast<Ast_function*>((*root_tree)->get_child(i_child));

		if (node)
		// The node is the Ast_function because the dynamic cast was successfully.
		{
			if (((*root_tree)->compare_precedence(node) > 0) && ((*root_tree)->is_comparable(node)))
			// Same level precedence and detection of posible swap.
			{
				if (((*root_tree)->is_prefix() && node->is_prefix()) ||
					((*root_tree)->is_postfix() && node->is_postfix()))
				// Case of nested prefix or postfix operations.
				{
					i_child++;
					continue;
				}

				if (((*root_tree)->compare_order(node) < 0) && node->is_prefix())
				// Discart swap because affect the syntax order.
				{
					// It turns on the flag of conflict to check into special case.
					(*root_tree)->active_conflict(node->get_function()->get_prec());
					i_child++;
					continue;
				}

				if (((*root_tree)->compare_order(node) > 0) && node->is_postfix())
				// Discart swap because affect the syntax order.
				{
					i_child++;
					continue;
				}

				// Performs the swap in normal conditions.
				int index_child = swap_root_child(root_tree, i_child);

				// Recursion is sent for organize the tree with the new root.
				check_subtree(root_tree,index_child);
			}
		}
		i_child++;
	} // end while.
}

void increment_level(char name)
{
	// Increment the level because a new parenthesis opening.
	current_precedence_level++;
}

void decrement_level(char name)
{
	// Decrement the level because a parenthesis closing.
	current_precedence_level--;
}

void reset_semantic_context()
{
	current_precedence_level = 0;
	index_syntax_order = 0;
}

/**
  * Asociative Section.
  */
void check_associativity(Ast_function ** root_tree)
{
	// Detecting if the child is of Ast_function type.
	Ast_function* child = dynamic_cast<Ast_function*>((*root_tree)->get_child(0));
	if(child)
	{
		if((*root_tree)->get_function()->equals(*(child->get_function())))
		{
			if((*root_tree)->is_comparable(child) &&
			   (*root_tree)->is_infix() &&
			   (*root_tree)->get_function()->get_oper_assoc() == k_right)
			{
				swap_root_child(root_tree,0);
				check_associativity(root_tree);
			}
		}
		else
		{
			check_associativity(&child);
			(*root_tree)->replace_child(0,child);
		}
	}
	if((*root_tree)->is_infix())
	{
		Ast_function *child_rec = dynamic_cast<Ast_function*>((*root_tree)->get_child(1));
		if (child_rec)
		{
			check_associativity(&child_rec);
			(*root_tree)->replace_child(1,child_rec);
		}
	}
}

