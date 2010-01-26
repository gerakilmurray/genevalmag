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

#include "SemDomain.h"
#include "ast/Ast_instance.h"
#include "ast/Ast_literal.h"
#include "ast/Ast_function.h"

using namespace std;
using namespace BOOST_SPIRIT_CLASSIC_NS;
using namespace genevalmag;

#define PATH_INPUT_FILE "./src/grammar.txt"
/**
  * Constant that represent the maximum size of the file buffer.
  */
#define MAX_INPUT_FILE 32000
/**
  * Constant that represent the maximum size of the line read.
  */
#define MAX_INPUT_LINE 256

/**
  * /var sem_domain
  * /brief Variable to represent Semantic domain.
  */
SemDomain sem_domain;

/**
  * Methods and functions for parse Sort class.
  */
void add_sort(char const *str, char const *end)
{
	string  name(str, end);
	Sort sort(name);
	sem_domain.add_sort(sort);
}

/**
  * Methods and functions for parse Operator.
  */
/**
  * Pointer that reference a new operator in the grammar.
  */
Function  *current_oper;

void add_operator(char const *str, char const *end)
{
	sem_domain.add_operator(*current_oper);
	delete(current_oper);
	current_oper = NULL;
}

void inic_operator(char const *str, char const *end)
{
	// Ignore the string parsed.
	current_oper = new Function();
}

void save_name_op(char const *str, char const *end)
{
	string name(str, end);
	current_oper->set_name(name);
}

void save_mode_op(char const *str, char const *end)
{
	string mode(str, end);
	current_oper->set_mode(mode);
}

void save_prec_op(int const prec)
{
	current_oper->set_prec(prec);
}

void save_assoc_op(char const *str, char const *end)
{
	string assoc(str, end);
	current_oper->set_oper_assoc(assoc);
}

void save_domain_op(char const *str, char const *end)
{
	string domain(str, end);
	current_oper->add_domain(&(sem_domain.return_sort(domain)));
}

void save_image_op(char const *str, char const *end)
{
	string image(str, end);
	current_oper->set_image(&(sem_domain.return_sort(image)));
}

/**
  * Methods and functions for parse Function.
  */
/**
  * Pointer that reference a new function in the grammar.
  */
Function  *current_func;

void add_function(char const *str, char const *end)
{
	sem_domain.add_function(*current_func);
	delete(current_func);
	current_func = NULL;
}

void save_name_func(char const *str, char const *end)
{
	current_func = new Function();
	string name(str, end);
	current_func->set_name(name);
}

void save_domain_func(char const *str, char const *end)
{
	string domain(str, end);
	current_func->add_domain(&(sem_domain.return_sort(domain)));
}

void save_image_func(char const *str, char const *end)
{
	string image(str, end);
	current_func->set_image(&(sem_domain.return_sort(image)));
}

/**
  * Methods and functions for parse Attribute class.
  */
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

void add_attr(char const *str, char const *end)
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
	{
		// First attribute name.
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
		new_attrs->d_mod_type = k_inherit;
}

void save_member_list(char const *str, char const *end)
{
	string members(str, end);
	boost::erase_all(members, " ");
	new_attrs->d_member_symbol = members;
}

void save_decl_attrs(char const *str, char const *end)
{
	for(vector<string>::size_type i = 0; i < new_attrs->d_names.size(); i++)
	{
		Attribute attr;
		attr.set_name(new_attrs->d_names[i]);
		attr.set_sort_type(&(sem_domain.return_sort(new_attrs->d_sort_type)));
		attr.set_mod_type(new_attrs->d_mod_type);
		attr.set_member_symbol(new_attrs->d_member_symbol);
		sem_domain.add_attribute(attr);
	}
	// Free space memory and assign NULL at pointer.
	delete(new_attrs);
	new_attrs = NULL;
}

/**
  * Methods and functions for parse Symbol class.
  */
void save_non_terminal(char const *str, char const *end)
{
	string name(str, end);
	Symbol symb(name, k_non_terminal);
	sem_domain.add_symbol(symb);
}

void save_terminal(char const *str, char const *end)
{
	string name(str, end);
	// The string is 'char'
	Symbol symb(name, k_terminal);
	sem_domain.add_symbol(symb);
}

/**
  * Methods and functions for parse Rule class.
  */
/**
  * Pointer that reference a current rule parsed in the grammar.
  */
Rule  *current_rule;

void save_rule(char const *str, char const *end)
{
	sem_domain.add_rule(*current_rule);
	delete(current_rule);
}

void add_left_symbol_rule(char const *str, char const *end)
{
	string left_side_symbol(str, end);
	current_rule = new Rule();
	current_rule->set_left_symbol(&(sem_domain.get_symbol(left_side_symbol)));
}

void add_right_side_rule(char const *str, char const *end)
{
	string right_side_symbol(str, end);
	current_rule->add_right_symbol(&(sem_domain.get_symbol(right_side_symbol)));
}

void abbreviated_rule(char const *str, char const *end)
{
	current_rule = new Rule();
	current_rule->set_left_symbol(current_rule->get_left_symbol());
}

/**
  * Methods and functions for parse Equation class of Rule.
  */

/**
  * Pointer to the last instance of attribute to parse successfully.
  */
Ast_instance    *current_instance;
Ast_literal     *current_literal;
Ast_function    *current_koperation;
Ast_function    *current_kfunction;

Equation        *current_eq;

/****** Stack for expresion *******/
vector<Ast_node*> 			stack_node;
vector<Ast_inner_node*> 	stack_inner_node;

void save_literal_node(char const *str, char const *end)
{
	stack_node.push_back(current_literal);
	current_literal = NULL;
}

void save_instance_node(char const *str, char const *end)
{
	current_instance->set_type_synthetized(current_instance->get_attr()->get_sort_type()->get_name());
	stack_node.push_back(current_instance);
	current_instance = NULL;
};

void save_symb_ins(char const *str, char const *end)
{
	string symb(str, end);
	if(current_instance == NULL)
	{
		current_instance = new Ast_instance();
	}
	current_instance->set_symb(&(sem_domain.get_symbol(symb)));
}

void save_index_ins(int const index)
{
	current_instance->set_num(index);
}

void save_attr_ins(char const *str, char const *end)
{
	string attr(str, end);
	current_instance->set_attr(current_instance->get_symb()->get_attribute(attr));
	if(current_instance->get_attr() == NULL)
	{
		cerr << "ERROR:" << attr <<"Atribute inexistente. Verifique los atributos usados en los symbolos." << endl;
		exit(1);
	}
}

void save_lit_int(int const int_lit)
{
	if(current_literal == NULL)
	{
		current_literal = new Ast_literal();
	}
	current_literal->set_type(k_int);
	current_literal->set_type_synthetized("int");
	stringstream literal_int;
	literal_int << int_lit;
	current_literal->set_value(literal_int.str());
}

void save_lit_flt(double const flt_lit)
{
	if(current_literal == NULL)
	{
		current_literal = new Ast_literal();
	}
	current_literal->set_type(k_float);
	current_literal->set_type_synthetized("float");
	stringstream literal_float;
	literal_float << flt_lit;
	current_literal->set_value(literal_float.str());
}

void save_lit_ch(char const *ch, char const *end)
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

void save_lit_str(char const *str, char const *end)
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

void save_operator(char const *str, char const *end)
{
	current_oper = new Function();
	save_name_op(str, end);
	current_oper->set_is_operator(IS_OPERATOR);
}

void save_function(char const *str, char const *end)
{
	save_name_func(str, end);
}

void save_oper_node(char const *str, char const *end)
{
	current_koperation = new Ast_function();
	current_koperation->set_function(current_oper);
	current_oper = NULL;

	stack_inner_node.push_back(current_koperation);
	current_koperation = NULL;
};

void save_func_node(char const *str, char const *end)
{
	current_kfunction = new Ast_function();
	current_kfunction->set_function(current_func);
	current_func = NULL;

	stack_inner_node.push_back(current_kfunction);
	current_kfunction = NULL;
};

void save_lvalue(char const *str, char const *end)
{
	current_eq = new Equation();
	current_eq->set_l_value(*current_instance);
	delete(current_instance);
	current_instance = NULL;
}

void save_rvalue(char const *str, char const *end)
{
	// CHECK QUE EL TIPO DEL L_VALUE SEA EL ESPERADO PARA EL R_VALUE.
	if (current_eq->get_l_value().get_attr()->get_sort_type()->get_name().compare(stack_node.back()->get_type_synthetized()))
	{
		cerr << "Type no esperado para l_value." << endl;
		exit(-1);
	}
	current_eq->set_r_value(stack_node.back());
	//Limpieza del resultado y la basura.
	stack_node.pop_back();
	while(!stack_node.empty())
	{
		Ast_literal* aux = (Ast_literal*)stack_node.back();
		stack_node.pop_back();
		delete(aux);
	}
	current_rule->add_eq(*current_eq);
	delete(current_eq);
	current_eq = NULL;
}

/**
  *
  */
void check_precedence(Ast_function ** root_tree)
{
	cout << (*root_tree)->to_string() << "adentro" << endl;

	int i_child = 0;
	bool recursive = false;

	static int precedence_case_op_prefix = -1;

	if ((*root_tree)->get_function()->get_mode() == k_infix && precedence_case_op_prefix > -1)
	{

		if (precedence_case_op_prefix < (*root_tree)->get_function()->get_prec())
		{
			Ast_function * new_root = (Ast_function *)(*root_tree)->get_child(0);
			new_root->set_parent((*root_tree)->get_parent());
			int index_swap = -1;
			if (new_root->get_function()->get_mode()!= k_infix)
				index_swap = 0;
			else
				index_swap = 1;
			Ast_function * swap = (Ast_function *) new_root->get_child(index_swap);
			Ast_node * grandson = swap->get_child(0);
			(*root_tree)->replace_child(0, grandson);
			swap->replace_child(0, *root_tree);
			new_root->replace_child(index_swap, swap);


			*root_tree = new_root;
		}
		precedence_case_op_prefix = -1;
		return;
	}

	while (i_child < (*root_tree)->get_function()->get_arity())
	{
		Ast_function* node = NULL;
		node = dynamic_cast<Ast_function*>((*root_tree)->get_childs()[i_child]);

		if (node)
		{
			// Cast succeeded. Is a function.
			if ((*root_tree)->get_function()->get_prec() > node->get_function()->get_prec())
			{
				if ((*root_tree)->get_function()->get_mode() == k_infix &&
					node->get_function()->get_mode() == k_postfix &&
					i_child == 0)
				{
					cout << "omite infix postfix" << endl;
					i_child++;
					continue;
				}
				if (node->get_function()->get_mode() == k_prefix)
				{
					if ((*root_tree)->get_function()->get_mode() == k_infix)
					{
						if (i_child == 1)
						{
							cout << "omite infix prefix OJO" << endl;
							precedence_case_op_prefix = node->get_function()->get_prec();
							i_child++;
							continue;
						}
						if (i_child == 0)
						{
							// caso de hijo izq menor prec
							recursive = true;
						}
					}
					if ((*root_tree)->get_function()->get_mode() == k_prefix)
					{
						cout << "omite prefix prefix" << endl;
						precedence_case_op_prefix = node->get_function()->get_prec();
						i_child++;
						continue;
					}
				}

				cout << "tenemos que cambiar" << (*root_tree)->to_string() << endl;

				int child_child = -1;
				if (node->get_function()->get_mode() == k_infix)
					child_child = 1;
				else
					child_child = 0;

				Ast_node * aux = node->get_child(child_child);
				node->set_parent((*root_tree)->get_parent());
				(*root_tree)->replace_child(i_child,aux);
				node->replace_child(child_child,*root_tree);
				*root_tree = node;

				Ast_function * aux1 = (Ast_function*)(*root_tree)->get_child(child_child);
				check_precedence(&aux1);
				(*root_tree)->replace_child(i_child,aux1);

				if(recursive)
				{
					Ast_function * rec = (Ast_function*)node->get_child(0);
					check_precedence(&rec);
					(*root_tree)->replace_child(i_child,rec);
					// sabemos que a lo sumo el cambio esta entre la nueva raiz y sus hijos.
					check_precedence(root_tree);
					recursive = false;
				}
			}
		}
		i_child++;
	}
}

/**
  * Section of AST creation.
  */
void create_root_infix_node(char const *str, char const *end)
{
	Ast_inner_node *root = stack_inner_node.back();
	stack_inner_node.pop_back();

	Ast_node *l_child, *r_child;

	bool is_mark = false;
	do
	{
		r_child = stack_node.back();
		stack_node.pop_back();
		is_mark = r_child->get_type_synthetized().compare("#") == 0;
		if (is_mark)
		{
			delete(r_child);
		}
	} while (is_mark);
	do
	{
		l_child = stack_node.back();
		stack_node.pop_back();
		is_mark = l_child->get_type_synthetized().compare("#") == 0;
		if (is_mark)
		{
			delete(l_child);
		}
	} while (is_mark);

	string key = "infix";
	key.append(((Ast_function*)root)->get_function()->get_name());
	key.append(l_child->get_type_synthetized());
	key.append(r_child->get_type_synthetized());

	Function  *func = sem_domain.get_function(key);

	if (func == NULL)
	{
		cerr << "Operador infix no existe: " << key << endl;
		exit(-1);
	}

	Function  *old = ((Ast_function*)root)->get_function();
	((Ast_function*)root)->set_function(func);
	delete(old);

	root->set_type_synthetized(((Ast_function*)root)->get_function()->get_image()->get_name());

	root->add_child(r_child);
	root->add_child(l_child);

	// Check the state of precedence of operators.
	check_precedence((Ast_function**)&root);

	stack_node.push_back(root);
}

void create_root_function_node(char const *str, char const *end)
{
	Ast_inner_node *root = stack_inner_node.back();
	stack_inner_node.pop_back();

	Ast_node *child;
	string key;
	unsigned int i;
	i = stack_node.size()-1;
	while (i > 0)
	{
		child = stack_node.back();
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
	key = ((Ast_function*)root)->get_function()->get_name().append(key);

	Function *func = sem_domain.get_function(key);

	if (func == NULL)
	{
		cerr << "Function no existe3: " << key << endl;
		exit(-1);
	}

	Function *old = ((Ast_function*)root)->get_function();
	((Ast_function*)root)->set_function(func);
	delete(old);

	root->set_type_synthetized(((Ast_function*)root)->get_function()->get_image()->get_name());

	stack_node.push_back(root);

}

void create_root_postfix_node(char const *str, char const *end)
{
	Ast_inner_node *root = stack_inner_node.back();
	stack_inner_node.pop_back();

	Ast_node *child;
	bool is_mark = false;
	do
	{
		child = stack_node.back();
		stack_node.pop_back();
		is_mark = child->get_type_synthetized().compare("#") == 0;
		if (is_mark)
		{
			delete(child);
		}
	} while (is_mark);

	string key = "postfix";
	key.append(((Ast_function*)root)->get_function()->get_name());
	key.append(child->get_type_synthetized());

	Function  *func = sem_domain.get_function(key);

	if (func == NULL)
	{
		cerr << "Operador postfix no existe: " << key << endl;
		exit(-1);
	}

	Function  *old = ((Ast_function*)root)->get_function();
	((Ast_function*)root)->set_function(func);
	delete(old);

	root->set_type_synthetized(((Ast_function*)root)->get_function()->get_image()->get_name());

	root->add_child(child);

	// Check the state of precedence of operators.
	check_precedence((Ast_function**)&root);

	stack_node.push_back(root);
}

void create_root_prefix_node(char const *str, char const *end)
{
	Ast_inner_node *root = stack_inner_node.back();
	stack_inner_node.pop_back();

	Ast_node *child;
	bool is_mark = false;
	do
	{
		child = stack_node.back();
		stack_node.pop_back();
		is_mark = child->get_type_synthetized().compare("#") == 0;
		if (is_mark)
		{
			delete(child);
		}
	} while (is_mark);

	string key = "prefix";
	key.append(((Ast_function*)root)->get_function()->get_name());
	key.append(child->get_type_synthetized());

	Function  *func = sem_domain.get_function(key);

	if (func == NULL)
	{
		cerr << "Operador prefix no existe: " << key << endl;
		exit(-1);
	}

	Function  *old = ((Ast_function*)root)->get_function();
	((Ast_function*)root)->set_function(func);
	delete(old);

	root->set_type_synthetized(((Ast_function*)root)->get_function()->get_image()->get_name());

	root->add_child(child);

	// Check the state of precedence of operators.
	check_precedence((Ast_function**)&root);

	stack_node.push_back(root);
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

void pepito(char const *str, char const *end)
{
	string pepe(str, end);
	cout << pepe << endl;
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
struct attr_grammar: public grammar<attr_grammar>
{
	template <typename ScannerT>
	struct definition
	{
		definition(attr_grammar const &self)
		{
			// Common declarations.

			r_ident			= lexeme_d[ (alpha_p | '_') >> *(alnum_p | '_') ] - r_reserved_word;

			r_oper			= lexeme_d[ (alpha_p | '_' | r_id_op) >> *(alnum_p | '_' | r_id_op) ];

			r_id_op			= ch_p('+')|'*'|'/'|'^'|'%'|'&'|'<'|'='|'-'|'>';

			r_char			= lexeme_d[ ch_p('\'') >> (alnum_p | r_id_op) >> ch_p('\'') ];

			r_string		= lexeme_d[ ch_p('\"') >> r_string_lit >> ch_p('\"') ];

			r_string_lit	= +((anychar_p - (ch_p('\"') | "\\")) | r_esc_seq);

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
								(r_ident[&add_sort][st_sorts.add] % ',') >> ';';

			// Declaration of Operators.

			r_decl_oper	= lexeme_d[ strlit<>("op") >> space_p ][&inic_operator] >>
							(r_oper_infix | r_oper_postfix | r_oper_prefix) >>
							 strlit<>("->") >>
							 r_sort_st[&save_image_op] >> ';';

			r_oper_infix   = strlit<>("infix")[&save_mode_op] >> !r_oper_mode >>
							 r_oper[&save_name_op][st_op_infix.add] >> ':' >>
							 r_sort_st[&save_domain_op] >> ',' >> r_sort_st[&save_domain_op];

			r_oper_postfix = strlit<>("postfix")[&save_mode_op] >> !r_oper_mode >>
							 r_oper[&save_name_op][st_op_postfix.add] >> ':' >>
							 r_sort_st[&save_domain_op];

			r_oper_prefix  = !(strlit<>("prefix")[&save_mode_op]) >> !r_oper_mode >>
							 r_oper[&save_name_op][st_op_prefix.add] >> ':' >>
							 r_sort_st[&save_domain_op];

			r_oper_mode	   = '(' >>(uint_p[&save_prec_op] | '_') >> ',' >>(r_oper_assoc[&save_assoc_op] | '_') >> ')';

			r_oper_assoc   = strlit<>("left") | strlit<>("right") | strlit<>("non-assoc");

			// Declaration of Functions.

			r_decl_func	= lexeme_d[ strlit<>("function")>> space_p ] >>
							 r_oper[&save_name_func][st_functions.add] >> ':' >>
							 !r_dom_func >> strlit<>("->") >>
							 r_sort_st[&save_image_func] >> ';';

			r_dom_func	= r_sort_st[&save_domain_func] % ',';

			/**
			  * Declaration of Attributes.
			  */
			r_attributes = lexeme_d[ strlit<>("attributes")>> space_p ] >> +r_decl_attr[&save_decl_attrs];

			r_decl_attr  =(r_ident[&add_attr][st_attributes.add] % ',') >>
						   ':' >> !(r_type_attr[&save_type_attr]) >> '<' >> r_sort_st[&save_sort_attr] >> '>' >>
						   lexeme_d[ strlit<>("of")>> space_p ] >>
						  (r_conj_symb |
						  (strlit<>("all") >> !('-' >> r_conj_symb)))[&save_member_list] >> ';';

			r_conj_symb	 = '{' >>(r_ident % ',') >> '}';

			r_type_attr  =(strlit<>("inh") | strlit<>("syn"));

			/**
			  * Declaration of Rules.
			  */

			r_rules		  = lexeme_d[ strlit<>("rules")>> space_p ] >> +r_decl_rule;

			r_decl_rule	  = r_ident[&save_non_terminal][&add_left_symbol_rule][st_symbols.add] >>
							strlit<>("::=") >>
							r_right_rule[&save_rule] >>
							*(strlit<>("|")[&abbreviated_rule] >> r_right_rule[&save_rule]) >> ';';

			r_right_rule  = +(  r_ident[&save_non_terminal][st_symbols.add]
							  | r_char[&save_terminal]
							 )[&add_right_side_rule] >>
							!(strlit<>("compute") >>
								+(r_equation) >>
							  strlit<>("end")
							 );

			r_equation	  = r_instance[&save_lvalue] >> '=' >> r_expression[&save_rvalue] >> ';';

			/**
			  * expression's Grammar non ambiguos based in
			  *
			  * 	E = T *(<op_infix> T)
			  *		T = F *(<op_postfix>) | (<op_prefix>) T
			  *		F = (E) | function | literal | instance
			  */
			r_expression 		= r_expr_prime >> *(r_op_infix_st[&save_operator][&save_oper_node] >> r_expr_prime[&create_root_infix_node])
								;

			r_expr_prime		= r_expr_prime_prime >> *(r_op_postfix_st[&save_operator][&save_oper_node][&create_root_postfix_node])
								| (r_op_prefix_st[&save_operator][&save_oper_node]) >> r_expr_prime[&create_root_prefix_node]
								;

			r_expr_prime_prime  = ch_p('(')[&push_mark] >> r_expression >> ')'
								| r_function[&create_root_function_node]
								| r_literal[&save_literal_node]
								| r_instance[&save_instance_node]
								;

			/**
			  * The functions accept a list of expressions.
			  */
			r_function			= r_function_st[&save_function][&save_func_node] >> ch_p('(')[&push_mark] >>!(r_expression % ',') >> ')';

			/**
			  * Literals accepted: Integer and Float numbers, characters and string,
			  * between signs ' and " respectively.
			  */
			r_literal			= int_p[&save_lit_int] | real_p[&save_lit_flt]
					 			| r_char[&save_lit_ch] | r_string[&save_lit_str];

			/**
			  * An instance is, the symbol with the number of occurrences in square brackets within
			  * the rule, with the specific attribute with which it operates.
			  *
			  * Example: E[0].value
			  */
			r_instance			= lexeme_d[ r_symbol_st[&save_symb_ins] >>
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
			r_symbol_st			= st_symbols;
		}
		/**
		  * Table of Symbols for the elements of an Attribute Grammar.
		  */
		symbols <> st_sorts;
		symbols <> st_op_prefix;
		symbols <> st_op_infix;
		symbols <> st_op_postfix;
		symbols <> st_functions;
		symbols <> st_attributes;
		symbols <> st_symbols;

		/**
		  * Variables using in parsing time.
		  */
		typedef rule<ScannerT> rule_exp;

		 // Rule in lexeme_d.
		typedef rule<typename lexeme_scanner<ScannerT>::type> rule_lexeme;

		// Basic rules: characters, strings and identifiers.
		rule_exp r_reserved_word, r_ident, r_oper, r_char, r_string, r_basic_types;

		rule_lexeme r_id_op, r_string_lit, r_esc_seq;

		// Semantic domain's rule: Sort, Operator and Function.
		rule_exp r_semantic_domain, r_bloq_sem, r_decl_sort, r_decl_oper, r_decl_func,
				 r_oper_assoc, r_oper_mode, r_oper_prefix, r_oper_infix, r_oper_postfix,
				 r_dom_func;

		// Atribute's rule.
		rule_exp r_attributes, r_decl_attr, r_type_attr, r_conj_symb;

		// Rule's rule.
		rule_exp r_rules, r_decl_rule, r_equation, r_right_rule;

		// Expresion's rule: Compute. Add context for type expresion.
		rule_exp r_expression,  r_expr_prime, r_expr_prime_prime, r_function, r_literal, r_instance;

		// Translate for symbol table.
		rule_exp r_sort_st, r_op_prefix_st, r_op_infix_st, r_op_postfix_st,
				 r_function_st, r_attribute_st, r_symbol_st, r_sort_stable;

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
	attr_grammar	attribute_grammar;
	skip_parser		skip_p;

	parse_info<> info =  parse(txt_input, attribute_grammar, skip_p);

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
		cout << sem_domain.to_string();
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
