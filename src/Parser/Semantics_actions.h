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
#include "Semantic_check.h"

using namespace std;

namespace genevalmag
{

void set_at(Attr_grammar *at_grammar);

void set_s_check(Semantic_check *s_check);

/**
  * Methods and functions for parse Sort class.
  */
void create_sort(char const *str, char const *end);

/**
  * Methods and functions for parse Function.
  */
void inic_func(char const *str, char const *end);

void add_function(char const *str, char const *end);

void save_name_func(char const *str, char const *end);

void save_domain_func(char const *str, char const *end);

void save_image_func(char const *str, char const *end);

/**
  * Methods and functions for parse Operator.
  */
void add_operator(char const *str, char const *end);

void save_mode_op(char const *str, char const *end);

void save_prec_op(int const prec);

void save_assoc_op(char const *str, char const *end);

/**
  * Methods and functions for parse Attribute class.
  */
void add_attribute(char const *str, char const *end);

void save_sort_attr(char const *str, char const *end);

void save_type_attr(char const *str, char const *end);

void save_member_list_attr(char const *str, char const *end);

void create_attributes(char const *str, char const *end);

/**
  * Methods and functions for parse Symbol class.
  */
void create_new_non_terminal(char const *str, char const *end);

void create_new_terminal(char const *str, char const *end);

/**
  * Methods and functions for parse Rule class.
  */
void create_rule(char const *str, char const *end);

void save_right_side_rule(char const *str, char const *end);

void create_abbreviated_rule(char const *str, char const *end);

void save_rule(char const *str, char const *end);

/**
  * Methods and functions for parse Equation class of Rule.
  */
void create_instance(char const *str, char const *end);

void save_index_ins(int const index);

void save_attr_ins(char const *str, char const *end);

void create_lit_number(char const *str, char const *end);

void create_lit_ch(char const *ch, char const *end);

void create_lit_str(char const *str, char const *end);

void create_function(char const *str, char const *end);

void create_operator(char const *str, char const *end);

void create_equation(char const *str, char const *end);

void save_rvalue(char const *str, char const *end);

void push_mark(char name);

/**
  * Creation AST nodes.
  */

void create_literal_node(char const *str, char const *end);

void create_instance_node(char const *str, char const *end);

void create_func_node(char const *str, char const *end);

void create_root_infix_node(char const *str, char const *end);

void create_root_function_node(char const *str, char const *end);

void create_root_postfix_node(char const *str, char const *end);

void create_root_prefix_node(char const *str, char const *end);

void check_well_defined(char const *str, char const *end);

string cleaning_tabs(const string str);

void increment_level(char name);

void decrement_level(char name);

} // namespace

#endif
