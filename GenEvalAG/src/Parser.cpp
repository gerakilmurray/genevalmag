/**
  *  \file		Parser.cpp
  *  \brief		Parsing module of Attribute Grammar.
  *  \date		13/09/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

//#define BOOST_SPIRIT_DEBUG  ///$$$ DEFINE THIS BEFORE ANYTHING ELSE $$$///

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_symbols.hpp>
#include <boost/spirit/include/classic_attribute.hpp>

#include <boost/algorithm/string/erase.hpp>

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>

#include "Attr_grammar.h"
#include "ast/Ast_instance.h"
#include "ast/Ast_literal.h"
#include "ast/Ast_function.h"

#include "Semantic_check.h"

using namespace std;
using namespace BOOST_SPIRIT_CLASSIC_NS;
using namespace genevalmag;

#define PATH_INPUT_FILE "./src/test/aritmetic.txt"
/**
  * Constant that represent the maximum size of the file buffer.
  */
#define MAX_INPUT_FILE 32000
/**
  * Constant that represent the maximum size of the line read.
  */
#define MAX_INPUT_LINE 256

/**
  * /var attr_grammar
  * /brief Variable to represent Semantic domain.
  */
Attr_grammar attr_grammar;

/**
  * Pointer that reference a new function in the grammar.
  */
Function  *current_func;

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
Rule  *current_rule;

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

string cleaning_tabs(const string str)
{
	string aux = "";
	for(int i=0; str[i] != '\0'; i++)
	{
		aux.push_back((str[i] == '\t')? ' ': str[i]);
	}
	return aux;
}

/**
  * Methods and functions for parse Sort class.
  */
void create_sort(char const *str, char const *end)
{
	string  name(str, end);
	Sort sort(name);
	if(!attr_grammar.add_sort(sort))
	{
		cerr << "WARNING: Sort duplicate was ignored: --> " << sort.to_string() << endl;
	}
}

/**
  * Methods and functions for parse Function.
  */
void inic_func(char const *str, char const *end)
{
	// Ignore the string parsed.
	current_func = new Function();
}

void add_function(char const *str, char const *end)
{
	if(!attr_grammar.add_function(*current_func))
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
	current_func->add_domain(&(attr_grammar.return_sort(domain)));
}

void save_image_func(char const *str, char const *end)
{
	string image(str, end);
	current_func->set_image(&(attr_grammar.return_sort(image)));
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
		// New declaration. Must be allocate new memory.
		new_attrs = new decl_attribute;
	}
	// Enqueue the name of new attribute.
	new_attrs->d_names.push_back(name);
	if(new_attrs->d_names.size() == 1)
	// First attribute name.
	{
		// Setting default values.
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
		attr.set_sort_type(&(attr_grammar.return_sort(new_attrs->d_sort_type)));
		attr.set_mod_type(new_attrs->d_mod_type);
		attr.set_member_symbol(new_attrs->d_member_symbol);
		attr_grammar.add_attribute(attr);
	}
	// Free space memory and assign NULL at pointer.
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
	attr_grammar.add_symbol(symb);
}

void create_new_terminal(char const *str, char const *end)
{
	string name(str, end);
	Symbol symb(name, k_terminal);
	attr_grammar.add_symbol(symb);
}

/**
  * Methods and functions for parse Rule class.
  */
void create_rule(char const *str, char const *end)
{
	string left_side_symbol(str, end);
	current_rule = new Rule();
	current_rule->set_left_symbol(&(attr_grammar.get_symbol(left_side_symbol)));
}

void save_right_side_rule(char const *str, char const *end)
{
	string right_side_symbol(str, end);
	current_rule->add_right_symbol(&(attr_grammar.get_symbol(right_side_symbol)));
}

void create_abbreviated_rule(char const *str, char const *end)
{
	current_rule = new Rule();
	current_rule->set_left_symbol(current_rule->get_left_symbol());
}

void save_rule(char const *str, char const *end)
{
	attr_grammar.add_rule(*current_rule);
	delete(current_rule);
}

/**
  * Methods and functions for parse Equation class of Rule.
  */
void create_instance(char const *str, char const *end)
{
	string name(str, end);

	Symbol *symb = &(attr_grammar.get_symbol(name));

	if (!current_rule->belongs_non_terminal(*symb))
	{
		cerr << "ERROR: non-terminal symbol \"" << name << "\" used does not belong to the rule: \"" << cleaning_tabs(current_rule->to_string_not_eqs())<< "\"."<< endl;
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
	// The pointer +1 and -1 for remove the single quotes. Ex: 'u' --> u.
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
	// The pointer +1 and -1 for remove the double quotes. Ex: "uno" --> uno.
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
	// Check that the type of r_value be expected from l_value.
	if (current_eq->get_l_value().get_attr()->get_sort_type()->get_name().compare(stack_node.back()->get_type_synthetized()))
	{
		cerr << "Type not expected from l_value." << endl;
		exit(-1);
	}

	Ast_node * root_tree = stack_node.back();
	stack_node.pop_back();

	// Check and solve conflicts of associativity
	Ast_function * root_func = dynamic_cast<Ast_function*>(root_tree);
	if (root_func)
	{
		correct_associativity(&root_func);
		root_tree = root_func;
	}

	// Obtaining the result.
	current_eq->set_r_value(root_tree);

	if (!current_rule->add_eq(*current_eq))
	{
		cerr << "WARNING: Ignores the eq \"" << cleaning_tabs(current_eq->to_string()) << "\" duplicate definition for \""
				<< cleaning_tabs(current_eq->get_l_value().to_string()) << "\" in rule: --> \""
				<< cleaning_tabs(current_rule->to_string_not_eqs()) << "\"" << endl;
	}
	delete(current_eq);

	current_eq = NULL;

	reset_semantic_context();
}

void push_mark(char name)
{
	current_literal = new Ast_literal();
	// Mark for parameter of function.
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
	stack_node.push_back(current_literal); // Push literal in stack.
	current_literal = NULL;
}

void create_instance_node(char const *str, char const *end)
{
	// Syntetize type instance.
	current_instance->set_type_synthetized(current_instance->get_attr()->get_sort_type()->get_name());
	stack_node.push_back(current_instance); // Push instance in stack.
	current_instance = NULL;
};

void create_func_node(char const *str, char const *end)
{
	current_ast_function = new Ast_function();

	extern unsigned short current_precedence_level;
	extern unsigned short index_syntax_order;

	current_ast_function->set_function(current_func);// Set aux function.

	// Set variables for check precedence and asociativity.
	current_ast_function->set_precedence_level(current_precedence_level);
	current_ast_function->set_syntax_order(++index_syntax_order);

	current_func = NULL;

	stack_inner_node.push_back(current_ast_function); // Push Ast_function in stack.
	current_ast_function = NULL;
};

void create_root_infix_node(char const *str, char const *end)
{
	Ast_function *root = (Ast_function*)stack_inner_node.back();
	stack_inner_node.pop_back(); // Pop the infix operator.

	Ast_node *r_child = stack_node.back();
	stack_node.pop_back(); // First parameter of operator

	Ast_node *l_child = stack_node.back();
	stack_node.pop_back(); // Second parameter of operator

	string key = "infix";
	key.append(root->get_function()->get_name());
	key.append(l_child->get_type_synthetized());
	key.append(r_child->get_type_synthetized());

	Function  *func = attr_grammar.get_function(key); // Searches of infix operator.

	Function  *old = root->get_function();
	delete(old); // Free aux function.

	if (func == NULL)
	{
		cerr << "ERROR: infix operator non-exist: " << key << endl;
		exit(-1);
	}

	root->set_function(func);

	root->set_type_synthetized(root->get_function()->get_image()->get_name());// Syntetize type infix operator.

	root->add_child(r_child);
	root->add_child(l_child);

	// Check the state of precedence of operators.
	correct_precedence(&root);

	stack_node.push_back(root); // Push infix operator in stack.
}

void create_root_function_node(char const *str, char const *end)
{
	Ast_function *root = (Ast_function*)stack_inner_node.back();
	stack_inner_node.pop_back(); // Pop the function.

	Ast_node *child;
	string key;
	unsigned int i = stack_node.size()-1;
	while (i > 0)
		// The cicle searches the parameters until that finds the mark.
	{
		child = stack_node.back();
		stack_node.pop_back(); // Parameter of function
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

	Function *func = attr_grammar.get_function(key); // Searches function.

	if (func == NULL)
	{
		cerr << "ERROR: Function non-exist: " << key << endl;
		exit(-1);
	}

	Function *old = root->get_function();
	root->set_function(func);
	delete(old); // Free aux function.

	root->set_type_synthetized(root->get_function()->get_image()->get_name()); // Syntetize type function.

	stack_node.push_back(root); // Push function in stack.
}

void create_root_postfix_node(char const *str, char const *end)
{
	Ast_function *root = (Ast_function*)stack_inner_node.back();
	stack_inner_node.pop_back(); // Pop the postfix operator.

	Ast_node *child = stack_node.back();
	stack_node.pop_back(); // Parameters of operator.

	string key = "postfix";
	key.append(root->get_function()->get_name());
	key.append(child->get_type_synthetized());

	Function  *func = attr_grammar.get_function(key); // Searches posfix operator.

	if (func == NULL)
	{
		cerr << "ERROR: postfix operator non-exist: " << key << endl;
		exit(-1);
	}

	Function  *old = root->get_function();
	root->set_function(func);
	delete(old); // Free aux function.

	root->set_type_synthetized(root->get_function()->get_image()->get_name()); // Syntetize type postfix operator.

	root->add_child(child);

	// Check the state of precedence of operators.
	correct_precedence(&root);

	stack_node.push_back(root);// Push postfix operator in stack.
}

void create_root_prefix_node(char const *str, char const *end)
{
	Ast_function *root = (Ast_function*)stack_inner_node.back();
	stack_inner_node.pop_back(); // Pop the prefix operator.

	Ast_node *child = stack_node.back();
	stack_node.pop_back(); // Parameter of operator.

	string key = "prefix";
	key.append(root->get_function()->get_name());
	key.append(child->get_type_synthetized());

	// Searches prefix operator
	Function  *func = attr_grammar.get_function(key);

	if (func == NULL)
	{
		cerr << "ERROR: prefix operator non-exist: " << key << endl;
		exit(-1);
	}

	Function  *old = root->get_function();
	root->set_function(func);
	delete(old); // Free aux function.

	// Syntetize type prefix operator.
	root->set_type_synthetized(root->get_function()->get_image()->get_name());

	root->add_child(child);

	// Correct the state of precedence of operators.
	correct_precedence(&root);

	// Push prefix operator in stack.
	stack_node.push_back(root);
}

void check_well_defined(char const *str, char const *end)
{
	check_all_defined_non_terminal(attr_grammar.get_rules(), attr_grammar.get_non_terminal_symbols());

	check_reachability(attr_grammar.get_rules(), attr_grammar.get_non_terminal_symbols(), attr_grammar.get_initial_symb());

	check_well_defined_AG(attr_grammar.get_rules());
}

/**
  * Declaration of a parser for imputs that ignore within
  * an Attribute Grammar file, with the Spirit library of Boost.
  */
struct skip_parser: public grammar<skip_parser>
{
	template <typename ScannerT>
	struct definition
	{
		definition(skip_parser const &self)
		{
			skip = space_p
				 | "//" >> *(anychar_p - '\n')
				 | "/*" >> *(anychar_p - "*/") >> "*/"
				 ;
		}

		rule<ScannerT> skip;

		rule<ScannerT> const &start() const
		{
			return skip;
		}
	};
};

/**
  * Declaration of the Attribute Grammar structure
  * with the Spirit library of Boost.
  */
struct attritute_grammar: public grammar<attritute_grammar>
{
	template <typename ScannerT>
	struct definition
	{
		definition(attritute_grammar const &self)
		{
			// Common declarations.

			r_ident			= lexeme_d[ (alpha_p | '_') >> *(alnum_p | '_') ] - r_reserved_word;

			r_oper			= lexeme_d[ (alpha_p | '_' | r_id_op) >> *(alnum_p | '_' | r_id_op) ];

			r_id_op			= ch_p('+')|'*'|'/'|'^'|'%'|'&'|'<'|'='|'-'|'>';

			r_char			= lexeme_d[ ch_p('\'') >> (alnum_p | r_id_op) >> ch_p('\'') ];

			char_pp			= lexeme_d[ ch_p('\'') >> (anychar_p) >> ch_p('\'') ];

			r_string		= lexeme_d[ ch_p('\"') >> r_string_lit >> ch_p('\"') ];

			r_string_lit	= +((anychar_p - (ch_p('\"') | "\\" | '\'' )) | r_esc_seq);

			r_esc_seq		= ch_p('\\') >>
							  ( oct_p |
								as_lower_d['x'] >> hex_p |
								(anychar_p - ch_p('\n'))
							  )
				;

			r_reserved_word = strlit<>("compute") 	|
									   "all"	  	|
									   "int" 		|
									   "string" 	|
									   "float"	 	|
									   "char"
							  ;

			r_basic_types	= strlit<>("int") | "float" | "string" | "char";

			/**
			  * Declaration of Semantic Domain.
			  */

			r_semantic_domain = lexeme_d[ strlit<>("semantic domain") >> space_p ] >> +r_bloq_sem;

			r_bloq_sem		  = r_decl_sort | r_decl_oper[&add_operator] | r_decl_func[&add_function];

			// Declaration of Sorts.

			r_decl_sort		  = lexeme_d[ strlit<>("sort") >> space_p ] >>
								(r_ident[&create_sort][st_sorts.add] % ',') >> ';';

			// Declaration of Operators.

			r_decl_oper	= lexeme_d[ strlit<>("op") >> space_p ][&inic_func] >>
							(r_oper_infix | r_oper_postfix | r_oper_prefix) >>
							 strlit<>("->") >>
							 r_sort_st[&save_image_func] >> ';';

			r_oper_infix   = strlit<>("infix")[&save_mode_op] >> !r_oper_mode >>
							 r_oper[&save_name_func][st_op_infix.add] >> ':' >>
							 r_sort_st[&save_domain_func] >> ',' >> r_sort_st[&save_domain_func];

			r_oper_postfix = strlit<>("postfix")[&save_mode_op] >> !r_oper_mode >>
							 r_oper[&save_name_func][st_op_postfix.add] >> ':' >>
							 r_sort_st[&save_domain_func];

			r_oper_prefix  = !(strlit<>("prefix")[&save_mode_op]) >> !r_oper_mode >>
							 r_oper[&save_name_func][st_op_prefix.add] >> ':' >>
							 r_sort_st[&save_domain_func];

			r_oper_mode	   = '(' >>(uint_p[&save_prec_op] | '_') >> ',' >>(r_oper_assoc[&save_assoc_op] | '_') >> ')';

			r_oper_assoc   = strlit<>("left") | strlit<>("right") | strlit<>("non-assoc");

			// Declaration of Functions.

			r_decl_func	= lexeme_d[ strlit<>("function")>> space_p ] >>
							 r_oper[&inic_func][&save_name_func][st_functions.add] >> ':' >>
							 !r_dom_func >> strlit<>("->") >>
							 r_sort_st[&save_image_func] >> ';';

			r_dom_func	= r_sort_st[&save_domain_func] % ',';

			/**
			  * Declaration of Attributes.
			  */
			r_attributes = lexeme_d[ strlit<>("attributes")>> space_p ] >> +r_decl_attr[&create_attributes];

			r_decl_attr  =(r_ident[&add_attribute][st_attributes.add] % ',') >>
						   ':' >> !(r_type_attr[&save_type_attr]) >> '<' >> r_sort_st[&save_sort_attr] >> '>' >>
						   lexeme_d[ strlit<>("of")>> space_p ] >>
						  (r_conj_symb |
						  (strlit<>("all") >> !('-' >> r_conj_symb)))[&save_member_list_attr] >> ';';

			r_conj_symb	 = '{' >>(r_ident % ',') >> '}';

			r_type_attr  =(strlit<>("inh") | strlit<>("syn"));

			/**
			  * Declaration of Rules.
			  */

			r_rules		  = lexeme_d[ strlit<>("rules")>> space_p ] >> (+r_decl_rule) >> eps_p[&check_well_defined];

			r_decl_rule	  = r_ident[&create_new_non_terminal][&create_rule][st_non_terminal.add] >>
							strlit<>("::=") >>
							r_right_rule[&save_rule] >>
							*(strlit<>("|")[&create_abbreviated_rule] >> r_right_rule[&save_rule]) >> ';';

			r_right_rule  = +( r_ident[&create_new_non_terminal][st_non_terminal.add]
			                 | r_terminal[&create_new_terminal]
							 )[&save_right_side_rule] >>
							!(strlit<>("compute") >>
								+(r_equation) >>
							  strlit<>("end")
							 );

			r_terminal	  = lexeme_d[ ch_p('\'') >> r_string_lit >> ch_p('\'') ];

			r_equation	  = r_instance[&create_equation] >> '=' >> r_expression[&save_rvalue] >> ';';

			/**
			  * expression's Grammar non ambiguos based in
			  *
			  * 	E = T *(<op_infix> T)
			  *		T = F *(<op_postfix>) | (<op_prefix>) T
			  *		F = (E) | function | literal | instance
			  */
			r_expression 		= r_expr_prime >> *(r_op_infix_st[&create_operator][&create_func_node] >> r_expr_prime[&create_root_infix_node])
								;

			r_expr_prime		= r_expr_prime_prime >> *(r_op_postfix_st[&create_operator][&create_func_node][&create_root_postfix_node])
								| r_op_prefix_st[&create_operator][&create_func_node] >> r_expr_prime[&create_root_prefix_node]
								;

			r_expr_prime_prime  = ch_p('(')[&increment_level] >> r_expression >> ch_p(')')[&decrement_level]
								| r_function[&create_root_function_node]
								| r_literal[&create_literal_node]
								| r_instance[&create_instance_node]
								;

			/**
			  * The functions accept a list of expressions.
			  */
			r_function			= r_function_st[&create_function][&create_func_node] >> ch_p('(')[&push_mark][&increment_level] >>!(r_expression % ',') >> ch_p(')')[&decrement_level];

			/**
			  * Literals accepted: Integer and Float numbers, characters and string,
			  * between signs ' and " respectively.
			  */
			r_literal			= longest_d[ real_p | int_p ][&create_lit_number]
					 			| r_char[&create_lit_ch]
								| r_string[&create_lit_str]
							    ;

			/**
			  * An instance is, the symbol with the number of occurrences in square brackets within
			  * the rule, with the specific attribute with which it operates.
			  *
			  * Example: E[0].value
			  */
			r_instance			= lexeme_d[ r_non_term_st[&create_instance] >>
					  						'[' >> int_p[&save_index_ins] >> ']' >>
					  						'.' >> r_attribute_st[&save_attr_ins]
					  					  ];

			/**
			  * Declaration of Attribute Grammar.
			  */
			r_att_grammar		= r_semantic_domain >> r_attributes >> r_rules >> end_p ;

			/**
			  * Parsers based in the symbol tables.
			  */
			r_sort_st			= st_sorts | r_basic_types;
			r_op_prefix_st		= st_op_prefix;
			r_op_infix_st		= st_op_infix;
			r_op_postfix_st		= st_op_postfix;
			r_function_st		= st_functions;
			r_attribute_st		= st_attributes;
			r_non_term_st		= st_non_terminal;
		}
		/**
		  * Symbols's Table for the elements of an Attribute Grammar.
		  */
		symbols <> st_sorts;
		symbols <> st_op_prefix;
		symbols <> st_op_infix;
		symbols <> st_op_postfix;
		symbols <> st_functions;
		symbols <> st_attributes;
		symbols <> st_non_terminal;

		/**
		  * Variables using in parsing time.
		  */
		typedef rule<ScannerT> rule_exp;

		 // Rule in lexeme_d.
		typedef rule<typename lexeme_scanner<ScannerT>::type> rule_lexeme;

		// Basic rules: characters, strings and identifiers.
		rule_exp r_reserved_word, r_ident, r_oper, r_char, r_string, r_basic_types, char_pp;

		rule_lexeme r_id_op, r_string_lit, r_esc_seq;

		// Semantic domain's rule: Sort, Operator and Function.
		rule_exp r_semantic_domain, r_bloq_sem, r_decl_sort, r_decl_oper, r_decl_func,
				 r_oper_assoc, r_oper_mode, r_oper_prefix, r_oper_infix, r_oper_postfix,
				 r_dom_func;

		// Atribute's rule.
		rule_exp r_attributes, r_decl_attr, r_type_attr, r_conj_symb;

		// Rule's rule.
		rule_exp r_rules, r_decl_rule, r_equation, r_right_rule, r_terminal;

		// Expresion's rule: Compute. Add context for type expresion.
		rule_exp r_expression,  r_expr_prime, r_expr_prime_prime, r_function, r_literal, r_instance;

		// Translate for symbol table.
		rule_exp r_sort_st, r_op_prefix_st, r_op_infix_st, r_op_postfix_st,
				 r_function_st, r_attribute_st, r_non_term_st, r_sort_stable;

		// Main rule.
		rule_exp r_att_grammar;

		rule_exp const &start() const
		{
			return r_att_grammar;
		}
	};
};

/**
  * This method invokes the method 'parse' of the library Spitir included in Boost.
  * Returns true if could parse all the input.
  */
bool parse_grammar(char const *txt_input)
{
	attritute_grammar	attr_grammar_decl;
	skip_parser			skip_p;

	parse_info<> info =  parse(txt_input, attr_grammar_decl, skip_p);

	#ifdef _DEBUG
		cout << "STOP: " << info.stop << "fin-STOP" << endl;
	#endif
	return info.full;
}

/**
  * Reads the contents of the file and save it in the
  * string passed as parameter.
  */
void read_file_in(string &txt_output)
{
	FILE*	p_file;
	char	buffer[MAX_INPUT_FILE];

	p_file = fopen(PATH_INPUT_FILE, "r");
	if(p_file == NULL)
		perror("Error opening file");
	else
	{
		while(!feof(p_file))
		{
			  fgets(buffer, MAX_INPUT_LINE, p_file);
			  txt_output += buffer;
		}
		fclose(p_file);
	}
}

/**
  * Main method of the parsing.
  */
int main()
{
	string input_grammar;
	read_file_in(input_grammar);
	cout << "-------------------------\n";
	if(parse_grammar(input_grammar.c_str()))
	{
		cout << attr_grammar.to_string();
		cout << "-------------------------\n";
		cout << "Parsing OK\n";
	}
	else
	{
		cout << "Parsing FAILED\n";
	}
	cout << "-------------------------\n";
	cout << "Bye... :-D" << endl;
	return 0;
}
