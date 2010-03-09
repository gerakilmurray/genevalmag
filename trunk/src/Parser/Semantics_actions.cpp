/**
  *  \file		Semantics_actions.cpp
  *  \brief		Implementation of the methods the Semantics_actions.h
  *  \date		09/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>
#include <sstream>

#include <boost/algorithm/string/erase.hpp>

#include "Semantics_actions.h"
#include "../Ast/Ast_instance.h"
#include "../Ast/Ast_literal.h"
#include "../Ast/Ast_function.h"
#include "../Util/Utilities.h"

using namespace std;

namespace genevalmag
{

Attr_grammar *attr_grammar;

void set_at(Attr_grammar *at_grammar)
{
	attr_grammar = at_grammar;
}

Semantic_check *sem_check;

void set_s_check(Semantic_check *s_check)
{
	sem_check = s_check;
}

/**
  * Pointer that reference a new function in the grammar.
  */
Function *current_func;

/**
  * Type that represent the structure of a full declaration of one Attribute.
  */
struct decl_attribute
{
	vector<string>	d_names;
	string			d_sort_type;
	type_attr		d_mod_type;
	string			d_member_symbol;
} *new_attrs;

/**
  * Pointer that reference a current rule parsed in the grammar.
  */
Rule *current_rule;

/**
  * Pointer to the last instance of attribute to parse successfully.
  */
Ast_instance	*current_instance;
Ast_literal		*current_literal;
Ast_function	*current_ast_function;
Equation		*current_eq;

/**
  * Stacks for expression precedence manager.
  */
vector<Ast_node*> 			stack_node;
vector<Ast_inner_node*> 	stack_inner_node;

/**
  * Methods and functions for parse Sort class.
  */
void create_sort(char const *str, char const *end)
{
	string name(str, end);
	Sort sort(name);
	if(!attr_grammar->add_sort(sort))
	{
		cerr << "WARNING: Sort duplicate was ignored: --> " << sort.to_string() << endl;
	}
}

/**
  * Methods and functions for parse Function.
  */
void inic_func(char const *str, char const *end)
{
	/* Ignore the string parsed. */
	current_func = new Function();
}

void add_function(char const *str, char const *end)
{
	if(!attr_grammar->add_function(*current_func))
	{
		cerr << "WARNING: Declaration duplicate was ignored: --> " << current_func->to_string() << endl;
	}
	delete(current_func);
	current_func = NULL;
}

void save_name_func(char const *str, char const *end)
{
	string name(str, end);
	current_func->set_name(name);
}

void save_domain_func(char const *str, char const *end)
{
	string domain(str, end);
	current_func->add_domain(&(attr_grammar->return_sort(domain)));
}

void save_image_func(char const *str, char const *end)
{
	string image(str, end);
	current_func->set_image(&(attr_grammar->return_sort(image)));
}

/**
  * Methods and functions for parse Operator.
  */
void add_operator(char const *str, char const *end)
{
	current_func->set_is_operator(IS_OPERATOR);
	add_function(str, end);
}

void save_mode_op(char const *str, char const *end)
{
	string mode(str, end);
	current_func->set_mode(mode);
}

void save_prec_op(int const prec)
{
	current_func->set_prec(prec);
}

void save_assoc_op(char const *str, char const *end)
{
	string assoc(str, end);
	current_func->set_oper_assoc(assoc);
}

/**
  * Methods and functions for parse Attribute class.
  */
void add_attribute(char const *str, char const *end)
{
	string name(str, end);
	if(new_attrs == NULL)
	{
		/* New declaration. Must be allocate new memory. */
		new_attrs = new decl_attribute;
	}
	/* Enqueue the name of new attribute. */
	new_attrs->d_names.push_back(name);
	if(new_attrs->d_names.size() == 1)
	/* First attribute name. */
	{
		/* Setting default values. */
		new_attrs->d_mod_type = k_synthetize;
		new_attrs->d_member_symbol = "\0";
	}
}

void save_sort_attr(char const *str, char const *end)
{
	string sort(str, end);
	new_attrs->d_sort_type = sort;
}

void save_type_attr(char const *str, char const *end)
{
	string mod_type(str, end);
	if(mod_type.compare("inh") == 0)
	{
		new_attrs->d_mod_type = k_inherit;
	}
}

void save_member_list_attr(char const *str, char const *end)
{
	string members(str, end);
	boost::erase_all(members, " ");
	boost::erase_all(members, "\t");
	boost::erase_all(members, "\n");
	new_attrs->d_member_symbol = members;
}

void create_attributes(char const *str, char const *end)
{
	for(vector<string>::size_type i = 0; i < new_attrs->d_names.size(); i++)
	{
		Attribute attr;
		attr.set_name(new_attrs->d_names[i]);
		attr.set_sort_type(&(attr_grammar->return_sort(new_attrs->d_sort_type)));
		attr.set_mod_type(new_attrs->d_mod_type);
		attr.set_member_symbol(new_attrs->d_member_symbol);
		attr_grammar->add_attribute(attr);
	}
	/* Free space memory and assign NULL at pointer. */
	delete(new_attrs);
	new_attrs = NULL;
}

/**
  * Methods and functions for parse Symbol class.
  */
void create_new_non_terminal(char const *str, char const *end)
{
	string name(str, end);
	Symbol symb(name, k_non_terminal);
	attr_grammar->add_symbol(symb);
}

void create_new_terminal(char const *str, char const *end)
{
	string name(str, end);
	Symbol symb(name, k_terminal);
	attr_grammar->add_symbol(symb);
}

/**
  * Methods and functions for parse Rule class.
  */
void create_rule(char const *str, char const *end)
{
	string left_side_symbol(str, end);
	current_rule = new Rule();
	current_rule->set_left_symbol(&(attr_grammar->get_symbol(left_side_symbol)));
}

void save_right_side_rule(char const *str, char const *end)
{
	string right_side_symbol(str, end);
	current_rule->add_right_symbol(&(attr_grammar->get_symbol(right_side_symbol)));
}

void create_abbreviated_rule(char const *str, char const *end)
{
	current_rule = new Rule();
	current_rule->set_left_symbol(current_rule->get_left_symbol());
}

void save_rule(char const *str, char const *end)
{
	attr_grammar->add_rule(*current_rule);
	delete(current_rule);
}

/**
  * Methods and functions for parse Equation class of Rule.
  */
void create_instance(char const *str, char const *end)
{
	string name(str, end);

	const Symbol *symb(&(attr_grammar->get_symbol(name)));

	if (!current_rule->belongs_non_terminal(*symb))
	{
		cerr << "ERROR: non-terminal symbol \"" << name << "\" used does not belong to the rule: \"" << utilities::cleaning_tabs(current_rule->to_string_not_eqs())<< "\"."<< endl;
		exit(-1);
	}

	if(current_instance == NULL)
	{
		current_instance = new Ast_instance();
	}
	current_instance->set_symb(symb);
}

void save_index_ins(int const index)
{
	if (index >= current_rule->count_non_terminal(current_instance->get_symb()))
	{
		cerr << "ERROR: Index of symbol incorrect."<< index << current_instance->get_symb()->get_name() << endl;
		exit(-1);
	}
	current_instance->set_num(index);
}

void save_attr_ins(char const *str, char const *end)
{
	string attr(str, end);
	current_instance->set_attr(current_instance->get_symb()->get_attribute(attr));
	if(current_instance->get_attr() == NULL)
	{
		cerr << "ERROR:" << attr << "Attribute non-existent. Check the attributes used in the symbols." << endl;
		exit(1);
	}
}

void create_lit_number(char const *str, char const *end)
{
	string num(str, end);

	if(current_literal == NULL)
	{
		current_literal = new Ast_literal();
	}

	size_t pos = num.find('.',0);
	if (pos > num.length())
	{
		current_literal->set_type(k_int);
		current_literal->set_type_synthetized("int");
		current_literal->set_value(num);
	}
	else
	{
		current_literal->set_type(k_float);
		current_literal->set_type_synthetized("float");
		current_literal->set_value(num);
	}
}

void create_lit_ch(char const *ch, char const *end)
{
	if(current_literal == NULL)
	{
		current_literal = new Ast_literal();
	}
	/* The pointer +1 and -1 for remove the single quotes. Ex: 'u' --> u. */
	string ch_l(ch+1,end-1);
	current_literal->set_type(k_char);
	current_literal->set_type_synthetized("char");
	current_literal->set_value(ch_l);
}

void create_lit_str(char const *str, char const *end)
{
	if(current_literal == NULL)
	{
		current_literal = new Ast_literal();
	}
	/* The pointer +1 and -1 for remove the double quotes. Ex: "uno" --> uno. */
	string str_l(str+1, end-1);
	current_literal->set_type(k_string);
	current_literal->set_type_synthetized("string");
	current_literal->set_value(str_l);
}

void create_function(char const *str, char const *end)
{
	current_func = new Function();
	save_name_func(str, end);
}

void create_operator(char const *str, char const *end)
{
	create_function(str,end);
	current_func->set_is_operator(IS_OPERATOR);
}

void create_equation(char const *str, char const *end)
{
	current_eq = new Equation();
	current_eq->set_l_value(*current_instance);
	delete(current_instance);
	current_instance = NULL;
}

void save_rvalue(char const *str, char const *end)
{
	/* Check that the type of r_value be expected from l_value. */
	if (current_eq->get_l_value()->get_attr()->get_sort_type()->get_name().compare(stack_node.back()->get_type_synthetized()))
	{
		cerr << "Type not expected from l_value." << endl;
		exit(-1);
	}

	Ast_node * root_tree(stack_node.back());
	stack_node.pop_back();

	/* Check and solve conflicts of associativity. */
	Ast_function * root_func(dynamic_cast<Ast_function*>(root_tree));
	if (root_func)
	{
		sem_check->correct_associativity(&root_func);
		root_tree = root_func;
	}

	/* Obtaining the result. */
	current_eq->set_r_value(root_tree);

	if (!current_rule->add_eq(*current_eq))
	{
		cerr << "WARNING: Ignores the eq \"" << utilities::cleaning_tabs(current_eq->to_string()) << "\" duplicate definition for \""
				<< utilities::cleaning_tabs(current_eq->get_l_value()->to_string()) << "\" in rule: --> \""
				<< utilities::cleaning_tabs(current_rule->to_string_not_eqs()) << "\"" << endl;
	}
	delete(current_eq);

	current_eq = NULL;

	sem_check->reset_semantic_context();
}

void push_mark(char name)
{
	current_literal = new Ast_literal();
	/* Mark for parameter of function. */
	current_literal->set_type_synthetized("#");
	current_literal->set_value("#");
	stack_node.push_back(current_literal);
	current_literal = NULL;
}

/**
  * Creation AST nodes.
  */

void create_literal_node(char const *str, char const *end)
{
	/* Push literal in stack. */
	stack_node.push_back(current_literal);
	current_literal = NULL;
}

void create_instance_node(char const *str, char const *end)
{
	/* Syntetize type instance. */
	current_instance->set_type_synthetized(current_instance->get_attr()->get_sort_type()->get_name());
	/* Push instance in stack. */
	stack_node.push_back(current_instance);
	current_instance = NULL;
};

void create_func_node(char const *str, char const *end)
{
	current_ast_function = new Ast_function();
	/* Set aux function. */
	current_ast_function->set_function(current_func);

	/* Set variables for check precedence and asociativity. */
	current_ast_function->set_precedence_level(sem_check->get_precedence_level());
	sem_check->increment_index_syntax_order();
	current_ast_function->set_syntax_order(sem_check->get_index_syntax_order());

	current_func = NULL;

	/* Push Ast_function in stack. */
	stack_inner_node.push_back(current_ast_function);
	current_ast_function = NULL;
};

void create_root_infix_node(char const *str, char const *end)
{
	/* Pop the infix operator. */
	Ast_function *root((Ast_function*)stack_inner_node.back());
	stack_inner_node.pop_back();

	/* Pop first parameter of operator. */
	Ast_node *r_child(stack_node.back());
	stack_node.pop_back();

	/* Pop second parameter of operator. */
	Ast_node *l_child(stack_node.back());
	stack_node.pop_back();

	string key("infix");
	key.append(root->get_function()->get_name());
	key.append(l_child->get_type_synthetized());
	key.append(r_child->get_type_synthetized());

	/* Searches of infix operator. */
	const Function *func(attr_grammar->get_function(key));
	const Function *old(root->get_function());

	/* Free aux function. */
	delete(old);

	if (func == NULL)
	{
		cerr << "ERROR: infix operator non-exist: " << key << endl;
		exit(-1);
	}

	root->set_function(func);

	/* Syntetize type infix operator. */
	root->set_type_synthetized(root->get_function()->get_image()->get_name());

	root->add_child(r_child);
	root->add_child(l_child);

	/* Check the state of precedence of operators. */
	sem_check->correct_precedence(&root);

	/* Push infix operator in stack. */
	stack_node.push_back(root);
}

void create_root_function_node(char const *str, char const *end)
{
	/* Pop the function. */
	Ast_function *root((Ast_function*)stack_inner_node.back());
	stack_inner_node.pop_back();

	string key;
	unsigned int i(stack_node.size() - 1);
	while (i > 0)
	/* The cycle searches the parameters until that finds the mark. */
	{
		/* Parameter of function. */
		Ast_node *child(stack_node.back());
		stack_node.pop_back();

		if (child->get_type_synthetized().compare("#") == 0)
		{
			delete(child);
			break;
		}
		root->add_child(child);

		key = child->get_type_synthetized().append(key);
		i--;
	}
	key = root->get_function()->get_name().append(key);

	/* Searches function. */
	const Function *func(attr_grammar->get_function(key));

	if (func == NULL)
	{
		cerr << "ERROR: Function non-exist: " << key << endl;
		exit(-1);
	}

	const Function *old(root->get_function());
	root->set_function(func);
	/* Free aux function. */
	delete(old);

	/* Syntetize type function. */
	root->set_type_synthetized(root->get_function()->get_image()->get_name());

	/* Push function in stack. */
	stack_node.push_back(root);
}

void create_root_postfix_node(char const *str, char const *end)
{
	/* Pop the postfix operator. */
	Ast_function *root((Ast_function*)stack_inner_node.back());
	stack_inner_node.pop_back();

	/* Parameters of operator. */
	Ast_node *child(stack_node.back());
	stack_node.pop_back();

	string key("postfix");
	key.append(root->get_function()->get_name());
	key.append(child->get_type_synthetized());

	/* Searches posfix operator. */
	const Function *func(attr_grammar->get_function(key));

	if (func == NULL)
	{
		cerr << "ERROR: postfix operator non-exist: " << key << endl;
		exit(-1);
	}

	const Function *old(root->get_function());
	root->set_function(func);
	/* Free aux function. */
	delete(old);

	/* Syntetize type postfix operator. */
	root->set_type_synthetized(root->get_function()->get_image()->get_name());

	root->add_child(child);

	/* Check the state of precedence of operators. */
	sem_check->correct_precedence(&root);

	/* Push postfix operator in stack. */
	stack_node.push_back(root);
}

void create_root_prefix_node(char const *str, char const *end)
{
	/* Pop the prefix operator. */
	Ast_function *root((Ast_function*)stack_inner_node.back());
	stack_inner_node.pop_back();

	/* Parameter of operator. */
	Ast_node *child(stack_node.back());
	stack_node.pop_back();

	string key("prefix");
	key.append(root->get_function()->get_name());
	key.append(child->get_type_synthetized());

	/* Searches prefix operator. */
	const Function *func(attr_grammar->get_function(key));

	if (func == NULL)
	{
		cerr << "ERROR: prefix operator non-exist: " << key << endl;
		exit(-1);
	}

	const Function  *old(root->get_function());
	root->set_function(func);
	/* Free aux function. */
	delete(old);

	/* Syntetize type prefix operator. */
	root->set_type_synthetized(root->get_function()->get_image()->get_name());

	root->add_child(child);

	/* Correct the state of precedence of operators. */
	sem_check->correct_precedence(&root);

	/* Push prefix operator in stack. */
	stack_node.push_back(root);
}

void check_well_defined(char const *str, char const *end)
{
	sem_check->check_all_defined_non_terminal(attr_grammar->get_rules(), attr_grammar->get_non_terminal_symbols());

	sem_check->check_reachability(attr_grammar->get_rules(), attr_grammar->get_non_terminal_symbols(), attr_grammar->get_initial_symb());

	sem_check->check_well_defined_AG(attr_grammar->get_rules());
}

void increment_level(char name)
{
	sem_check->increment_precedence_level();
}

void decrement_level(char name)
{
	sem_check->decrement_precedence_level();
}

} /* end genevalmag */
