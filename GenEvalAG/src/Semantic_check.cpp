/**
  *  \file		Semantic_check.cpp
  *  \brief		Implementation of the methods the Semantic_check.h
  *  \date		28/09/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>

#include "Semantic_check.h"

using namespace std;
using namespace genevalmag;

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

/*
 * Checking from the root of the expression tree to the leaves, which all
 * operators are applies according to their precedence.
 * If there are conflicts resolves them doing rotations, leaving the operator
 * with lower precedence, as the new root.
 */
void check_precedence(Ast_function ** root_tree);

void correct_subtree(Ast_function** subtree, int index_root_subtree)
{
	Ast_function * aux = (Ast_function*)(*subtree)->get_child(index_root_subtree);
	correct_precedence(&aux);

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
void correct_precedence(Ast_function ** root_tree)
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
			correct_subtree(&subtree,0);

			// Updates the main tree, with the new root of subtree.
			(*root_tree)->replace_child(i_subtree,subtree);

			// Only requires checking the main tree root with his new son.
			correct_precedence(root_tree);
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
				correct_subtree(root_tree,index_child);
			}
		}
		i_child++;
	} // end while.
}

void increment_level(char name)
{
	current_precedence_level++;
}

void decrement_level(char name)
{
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
void correct_associativity(Ast_function ** root_tree)
{
	// Detecting if the child is of Ast_function type.
	Ast_function* child = dynamic_cast<Ast_function*>((*root_tree)->get_child(0));
	if(child)
	{
		if((*root_tree)->get_function()->equals(*(child->get_function())))
		{
			if((*root_tree)->is_comparable(child) &&
			   (*root_tree)->is_infix())
			{
				if ((*root_tree)->get_function()->get_oper_assoc() == k_right)
				{
					swap_root_child(root_tree,0);
					correct_associativity(root_tree);
				}
				else if ((*root_tree)->get_function()->get_oper_assoc() == k_non_assoc)
				{
					cerr << "ERROR: operator non-associtive using wrong use: " << (*root_tree)->get_function()->get_name() << endl;
					exit(-1);
				}
			}
		}
		else
		{
			correct_associativity(&child);
			(*root_tree)->replace_child(0,child);
		}
	}
	if((*root_tree)->is_infix())
	{
		Ast_function *child_rec = dynamic_cast<Ast_function*>((*root_tree)->get_child(1));
		if (child_rec)
		{
			correct_associativity(&child_rec);
			(*root_tree)->replace_child(1,child_rec);
		}
	}
}


bool check_all_defined_non_terminal(const map <string, Rule> rules, const map <string, Symbol> non_terminals)
{
	bool left_symbol_defined;

	for (map<string,Symbol >::const_iterator it_s = non_terminals.begin(); it_s != non_terminals.end(); it_s++)
	{
		left_symbol_defined = false;

		map<string,Rule >::const_iterator it_r =rules.begin();
		while (it_r != rules.end())
		{
			if (it_s->second.equals(*(it_r->second.get_left_symbol())))
			{
				left_symbol_defined = true;
				break;
			}

			it_r++;
		}

		if (!left_symbol_defined)
		{
			cerr << "ERROR: Symbol Non-Teminal \""<< it_s->second.get_name() << "\" uses in the right part without rule." << endl;
			return false;
		}
	}
	return true;
}

void warshall_algorithm(const unsigned int size, bool *matrix_plain)
{
	for (size_t k = 0; k < size; k++)
	{
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j=0; j < size; j++)
			{
				// Assign new value from: M[i][j] = M[i][j] OR (M[i][k] AND M[k][j])
				(matrix_plain + (size*i))[j] =
						(matrix_plain + (size*i))[j] ||
						((matrix_plain + (size*i))[k] && (matrix_plain + (size*k))[j]);
			}
		}
	}
}

int get_index(string name_symb,vector<string> non_term)
{
	for (size_t i=0; i< non_term.size();i++)
	{
		if (name_symb.compare(non_term[i]) == 0)
		{
			// Elem found. Return index of elem.
			return i;
		}
	}
	// The elem isn't in the vector.
	return -1;
}

bool check_reachability(const map <string, Rule> rules, const map <string, Symbol> non_terminals, Symbol *init_symb)
{
	vector<string> non_term;
	// Obtain all non_terminals name.
	for (map<string,Symbol >::const_iterator it_s = non_terminals.begin(); it_s != non_terminals.end(); it_s++)
	{
		non_term.push_back(it_s->second.get_name());
	}

	int cant_non_terminal = non_term.size();

	bool matrix_reachability[cant_non_terminal][cant_non_terminal];

	// Inicializer matriz.
	for (int i=0; i<cant_non_terminal; i++)
	{
		for (int j=0;j<cant_non_terminal;j++)
		{
			matrix_reachability[i][j] = false;
		}
	}

	// Matrix W0 in Warshall Algorithm.

	// For each rule, set the adjacency relations of the non-terminals.
	for (map<string,Rule >::const_iterator it_r = rules.begin(); it_r != rules.end(); it_r++)
	{
		string symbol = it_r->second.get_left_symbol()->get_name();
		int index_i = get_index(symbol,non_term);

		// For each non-terminal in the right side, set true cell in the matrix.
		for(size_t k=0;k < it_r->second.get_right_side().size();k++)
		{
			if (it_r->second.get_right_side().at(k)->is_non_terminal())
			{
				symbol = it_r->second.get_right_side().at(k)->get_name();
				int index_j = get_index(symbol,non_term);
				matrix_reachability[index_i][index_j] = true;
			}
		}
	}

	bool * first = &matrix_reachability[0][0];
	warshall_algorithm(cant_non_terminal, first);

	// Index of initial symbol of AG.
	int index_init = get_index(init_symb->get_name(),non_term);

	for(int j=0; j<cant_non_terminal; j++)
	{
		if(!matrix_reachability[index_init][j])
		{
			cerr << "WARNING: Symbol Non-Teminal \""<< non_term[j] << "\" unreachable." << endl;
		}
	}

	return true;
}
bool check_eq_defindes_it(const Symbol *symb, const int index, const Attribute *attr, const map<int,Equation> eqs)
{
	// For each eq.
	for (map<int,Equation >::const_iterator it_eq = eqs.begin(); it_eq != eqs.end(); it_eq++)
	{
		if (symb->equals(*it_eq->second.get_l_value().get_symb()) &&
			index == it_eq->second.get_l_value().get_num() &&
			attr->equals(*it_eq->second.get_l_value().get_attr()))
		{
			return true;
		}
	}
	return false;
}

bool check_well_defined_AG(const map <string, Rule> rules)
{
	for (map<string,Rule >::const_iterator it_r = rules.begin(); it_r != rules.end(); it_r++)
	{
		// Get left Symbol.
		Symbol *symb = it_r->second.get_left_symbol();

		for(size_t i=0;i< symb->get_attrs().size();i++)
		{
			Attribute * attr_syn = symb->get_attrs()[i];

			bool result = check_eq_defindes_it(symb, 0, attr_syn, it_r->second.get_eqs());

			if (attr_syn->is_synthetize() && !result)
			// The attribute is synthetized. Must be checked if defined.
			{
				cerr << "ERROR: \"" << symb->get_name() << "["<< 0 << "]."<< attr_syn->get_name() << "\" tipo syntetize, no tiene una Eq que lo defina." << endl;
				return false;
			}

			if (attr_syn->is_inherit() && result)
			// The attribute is synthetized. Must be checked if defined.
			{
				cerr << "ERROR: \"" << symb->get_name() << "["<< 0 << "]."<< attr_syn->get_name() << "\" tipo inherit, esta definido fuera de su scope." << endl;
				return false;
			}

		}
		int index_non_terminal = 0;
		// Cover the right symbols.
		for (size_t j=0;j<it_r->second.get_right_side().size();j++)
		{
			symb = it_r->second.get_right_side()[j];
			if (symb->is_non_terminal())
			{
				index_non_terminal++;
				for(size_t k=0;k< symb->get_attrs().size();k++)
				{
					Attribute * attr_inh = symb->get_attrs()[k];
					bool result = check_eq_defindes_it(symb, index_non_terminal, attr_inh, it_r->second.get_eqs());
					if (attr_inh->is_inherit() && !result)
					{
						cerr << "ERROR: \"" << symb->get_name() << "["<< index_non_terminal << "]."<< attr_inh->get_name() << "\" tipo inherit, no tiene una Eq que lo defina." << endl;
						return false;
					}

					if (attr_inh->is_synthetize() && result)
					{
						cerr << "ERROR: \"" << symb->get_name() << "["<< index_non_terminal << "]."<< attr_inh->get_name() << "\" tipo syntetize, esta definido fuera de su scope." << endl;
						return false;
					}
				}
			}
		}
	}
	return true;
}
