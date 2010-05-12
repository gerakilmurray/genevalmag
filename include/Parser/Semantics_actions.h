/**
  *  \file		Semantics_actions.h
  *  \brief		Header semantics actions for parse of Attribute grammar.
  *  \date		09/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef SEMANTICS_ACTIONS_H_
#define SEMANTICS_ACTIONS_H_

#include <string>

#include "../Attr_grammar/Attr_grammar.h"

#include "Semantics_checks.h"
#include "Parser_AG.h"

using namespace std;

namespace genevalmag
{

/**
  * Sets attribute attr_grammar.
  * @param at_grammar
  */
void set_attr_grammar(Attr_grammar *at_grammar);

/**
  * Sets attribute sem_check.
  * @param s_check
  */
void set_sem_check(Semantics_checks *s_check);

/**
  * Methods and functions for parse Sort class.
  */
void create_sort(const iterator_t str, const iterator_t end);

/**
  * Methods and functions for parse Function.
  */
void inic_func(const iterator_t str, const iterator_t end);
void add_function(const iterator_t str, const iterator_t end);
void save_name_func(const iterator_t str, const iterator_t end);
void save_domain_func(const iterator_t str, const iterator_t end);
void save_image_func(const iterator_t str, const iterator_t end);

/**
  * Methods and functions for parse Operator.
  */
void add_operator(const iterator_t str, const iterator_t end);
void save_mode_op(const iterator_t str, const iterator_t end);
void save_prec_op(int const prec);
void save_assoc_op(const iterator_t str, const iterator_t end);

/**
  * Methods and functions for parse Attribute class.
  */
void add_attribute(const iterator_t str, const iterator_t end);
void save_sort_attr(const iterator_t str, const iterator_t end);
void save_type_attr(const iterator_t str, const iterator_t end);
void save_member_list_attr(const iterator_t str, const iterator_t end);
void create_attributes(const iterator_t str, const iterator_t end);

/**
  * Methods and functions for parse Symbol class.
  */
void create_new_non_terminal(const iterator_t str, const iterator_t end);
void create_new_terminal(const iterator_t str, const iterator_t end);

/**
  * Methods and functions for parse Rule class.
  */
void create_rule(const iterator_t str, const iterator_t end);
void save_right_side_rule(const iterator_t str, const iterator_t end);
void create_abbreviated_rule(const iterator_t str, const iterator_t end);
void save_rule(const iterator_t str, const iterator_t end);

/**
  * Methods and functions for parse Equation class of Rule.
  */
void create_instance(const iterator_t str, const iterator_t end);
void save_index_ins(int const index);
void save_attr_ins(const iterator_t str, const iterator_t end);
void create_lit_number(const iterator_t str, const iterator_t end);
void create_lit_ch(const iterator_t ch, const iterator_t end);
void create_lit_str(const iterator_t str, const iterator_t end);
void create_bool(const iterator_t str, const iterator_t end);
void create_function(const iterator_t str, const iterator_t end);
void create_operator(const iterator_t str, const iterator_t end);
void create_equation(const iterator_t str, const iterator_t end);
void save_rvalue(const iterator_t str, const iterator_t end);
void push_mark(char name);

/**
  * Creation AST nodes.
  */

void create_literal_node(const iterator_t str, const iterator_t end);
void create_instance_node(const iterator_t str, const iterator_t end);
void create_func_node(const iterator_t str, const iterator_t end);
void create_root_infix_node(const iterator_t str, const iterator_t end);
void create_root_function_node(const iterator_t str, const iterator_t end);
void create_root_postfix_node(const iterator_t str, const iterator_t end);
void create_root_prefix_node(const iterator_t str, const iterator_t end);
void check_well_defined(const iterator_t str, const iterator_t end);
void increment_level(char name);
void decrement_level(char name);

} /* end genevalmag */

#endif /* SEMANTICS_ACTIONS_H_ */
