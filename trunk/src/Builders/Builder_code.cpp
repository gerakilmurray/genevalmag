/**
  *  \file		Builder_code.cpp
  *  \brief		Implementation of the methods the Builder_code.h.
  *  \date		18/03/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <fstream>
#include <iostream>
#include <time.h>

#include <boost/algorithm/string.hpp>

#include "../../include/Builders/Builder_plans.h"
#include "../../include/Expression_tree/Expr_function.h"
#include "../../include/Expression_tree/Expr_literal.h"
#include "../../include/Expression_tree/Expr_instance.h"
#include "../../include/Util/Utilities.h"

#include "../../include/Builders/Builder_code.h"

using namespace std;
using namespace utilities;

namespace genevalmag
{

/**
  * Contructor with the path and name of output files to be generated.
  */
Builder_code::Builder_code
(
	const string &path_folder_output,
	const string &name_file,
	const Attr_grammar &attribute_grammar,
	const Builder_plans &builder_plan,
	const Builder_visit_sequences &builder_v_seq
)
	: attr_grammar(attribute_grammar),
	  b_plans(builder_plan),
	  b_v_seq(builder_v_seq)
{
	path_output = path_folder_output;

	file_name = name_file;
}

/**
  * Destructor of the Builder_code.
  */
Builder_code::~Builder_code()
{
}

/**
  * Create the header file of the evaluator with some information.
  */
void Builder_code::generate_header_file() const
{
	string header("/**\n");
	header.append("  * \\file    ");
	header.append(file_name);
	header.append(".hpp");
	header.append("\n");
	header.append("  * \\brief   Header of evaluator of ");
	header.append(file_name);
	header.append(".\n");

	header.append("  * \\date    ");
	time_t rawtime;
	struct tm *timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	header.append(asctime (timeinfo));

	header.append("  * \\author  Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>\n");
	header.append("  * \\author  Picco, Gonzalo Martin <gonzalopicco@gmail.com>\n");
	header.append("*/\n\n");

	string name_upper(boost::to_upper_copy(file_name));

	header.append("#ifndef _");
	header.append(name_upper);
	header.append("_HPP_\n");
	header.append("#define _");
	header.append(name_upper);
	header.append("_HPP_\n\n");

	header.append("#include <vector>\n\n");
	header.append("#include \"Node.hpp\"\n");
	header.append("#include \"Plan.hpp\"\n\n");

	header.append("using namespace std;\n");
	header.append("using namespace util_ag;\n\n");

	header.append("namespace evalmag\n");
	header.append("{\n\n");

	string path(path_output);
	path.append(file_name);
	path.append(".hpp");
	std::ofstream file_output(path.c_str());
	file_output.write(header.c_str(), header.size());
	file_output.close();
}

/**
  * Create the source code file of the evaluator with some information.
  */
void Builder_code::generate_code_file(const vector<string> &headers_file) const
{
	string code_txt("/**\n");
	code_txt.append("  * \\file    ");
	code_txt.append(file_name);
	code_txt.append(".cpp\n");
	code_txt.append("  * \\brief   Implementation of methods of the evaluator of ");
	code_txt.append(file_name);
	code_txt.append(".\n");

	code_txt.append("  * \\date    ");
	time_t rawtime;
	struct tm *timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	code_txt.append(asctime (timeinfo));

	code_txt.append("  * \\author  Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>\n");
	code_txt.append("  * \\author  Picco, Gonzalo Martin <gonzalopicco@gmail.com>\n");
	code_txt.append("*/\n\n");

	code_txt.append("#include <stdlib.h>\n");
	code_txt.append("#include <iostream>\n");
	code_txt.append("#include <sstream>\n");
	code_txt.append("#include <climits>\n");

	for (size_t i(0);i<headers_file.size();i++)
	{
		code_txt.append("#include \"");
		code_txt.append(headers_file[i]);
		code_txt.append("\"\n");
	}

	code_txt.append("#include \"");
	code_txt.append(file_name);
	code_txt.append(".hpp\"\n\n");

	code_txt.append("namespace evalmag\n");
	code_txt.append("{\n\n");

	string path(path_output);
	path.append(file_name);
	path.append(".cpp");
	std::ofstream file_output(path.c_str());
	file_output.write(code_txt.c_str(), code_txt.size());
	file_output.close();
}

/**
  * Insert the header file's footer of the evaluator.
  */
void Builder_code::generate_footer_header() const
{
	string footer("/**\n  * Main class of GenEvalMag.\n  */\n");
	footer.append("class ");
	footer.append(file_name);
	footer.append("\n{\n");

	footer.append("  private:\n");
	footer.append("    vector <Visit_sequence> v_seq;\n\n");
	footer.append("    vector <Order_rule> contexts_rule;\n\n");
	footer.append("    vector <Rule> rules;\n\n");
	footer.append("    /* \"ro\" function. Wuu Yang's paper. */\n");
	footer.append("    vector <Plan> eval_plans;\n\n");
	footer.append("    /* \"theta\" function. Wuu Yang's paper. */\n");
	footer.append("    vector <Plan_project> eval_plans_project;\n\n");
	footer.append("    void add_plan(const Key_plan &k_plan, unsigned short index_order);\n");
	footer.append("    void add_plan_project(const Key_plan_project &k_plan_p, unsigned short index_order);\n");
	footer.append("    void compute_eq(int num_eq, struct Node *root);\n");
	footer.append("    void traverse(struct Node *node, unsigned short order);\n");
	footer.append("    void eval_visiter(struct Node *root);\n\n");

	footer.append("  public:\n    ");
	footer.append(file_name);
	footer.append("();\n\n");
	footer.append("    void print_visit_seqs();\n\n");
	footer.append("    void translates_visit_segs();\n\n");
	footer.append("    void evaluator_mag(struct Node *root);\n\n");
	footer.append("};\n\n");

	footer.append("} /* end evalmag */\n\n");

	string name_upper(boost::to_upper_copy(file_name));

	footer.append("#endif /* _");
	footer.append(name_upper);
	footer.append("_HPP_ */\n\n");

	string path(path_output);
	path.append(file_name);
	path.append(".hpp");
	std::ofstream file_output(path.c_str(),ofstream::app);
	file_output.write(footer.c_str(),footer.size());
	file_output.close();
}

/**
  * Insert the source code file's footer of the evaluator.
  */
void Builder_code::generate_footer_code() const
{
	string footer("} /* end evalmag */\n\n");

	string path(path_output);
	path.append(file_name);
	path.append(".cpp");
	std::ofstream file_output(path.c_str(),ofstream::app);
	file_output.write(footer.c_str(),footer.size());
	file_output.close();
}

/**
  * Generates the initialice of an array of type T, with the elements of the vector, and create a new vector
  * with this array.
  */
template <class T> string write_vector_with_inic
(
	string &text_buffer,
	const string name_vec,
	const size_t index,
	const vector <T> &vec,
	const string type_vec,
	const string type_array
)
{
	text_buffer.append("  ");
	text_buffer.append(type_array);
	text_buffer.append(" __");
	string name (name_vec);

	stringstream index_array;
	index_array << index;
	name.append(index_array.str());

	text_buffer.append(name);
	text_buffer.append("[] = ");

	text_buffer.append("{");
	for(size_t i(0); i < vec.size(); i++)
	{
		stringstream item;
		item << vec[i];
		text_buffer.append(item.str());
		if(i < vec.size() - 1)
		{
			text_buffer.append(",");
		}
	}
	text_buffer.append("};\n  ");

	text_buffer.append(type_vec);
	text_buffer.append(" ");
	text_buffer.append(name);
	text_buffer.append("(__");
	text_buffer.append(name);
	text_buffer.append(", __");
	text_buffer.append(name);
	text_buffer.append(" + sizeof(__");
	text_buffer.append(name);
	text_buffer.append(") / sizeof(");
	text_buffer.append(type_array);
	text_buffer.append("));\n");

	return name;
}

/**
  * Generates the initialization of all visit sequences.
  */
string Builder_code::generate_initialize_v_seq() const
{
	string text("  /**\n    * Initialize of Visit Sequences.\n    */\n");

	for(size_t i(0); i < b_v_seq.get_visit_seq().size(); i++)
	{
		string name_vec(
			write_vector_with_inic<int>(
				text,
				"order_",
				i,
				b_v_seq.get_visit_seq()[i],
				"Visit_sequence",
				"int"
			)
		);
		text.append("  v_seq.push_back(");
		text.append(name_vec);
		text.append(");\n\n");
	}
	return text;
}

/**
  * Generate a key plan with the parameters.
  */
string generate_key_plan(string &text, const string &n_key, const int &num_key, const Key_plan &k_p)
{
	text.append("  Key_plan ");
	string name_key(n_key);
	stringstream str_index;
	str_index << num_key;
	name_key.append(str_index.str());
	text.append(name_key);
	text.append("(");
	stringstream context_index;
	context_index << k_p.id_plan;
	text.append(context_index.str());
	text.append(", ");
	stringstream key_plan_index;
	key_plan_index << k_p.plan;
	text.append(key_plan_index.str());
	text.append(");\n");

	return name_key;
}

/**
  * Generates the initialization of all contexts rules uniques.
  */
string Builder_code::generate_initialize_context() const
{
	string text("  /**\n    * Initialize of Contexts Rules.\n    */\n");

	for(size_t i(0); i < b_plans.get_contexts_uniques().size(); i++)
	{
		string name_vec(
			write_vector_with_inic<unsigned short>(
				text,
				"context_",
				i,
				b_plans.get_contexts_uniques()[i],
				"Order_rule",
				"unsigned short"
			)
		);
		text.append("  contexts_rule.push_back(");
		text.append(name_vec);
		text.append(");\n\n");
	}
	return text;
}

/**
  * Generates the initialization of all evaluations plans.
  */
string Builder_code::generate_initialize_plans() const
{
	string text("  /**\n    * Initialize of Evaluation Plans.\n    */\n");

	int num_key = 0;
	for(map < Key_plan, unsigned short >::const_iterator it(b_plans.get_plans().begin()); it != b_plans.get_plans().end(); it++)
	{
		/* Generate key_plan */
		string name_key(generate_key_plan(text, "key_", num_key, it->first));

		stringstream str_index;
		str_index << num_key;

		/* Generate insert in map */
		text.append("  add_plan(");
		text.append(name_key);
		text.append(" , ");

		stringstream plan_index;
		plan_index << it->second;
		text.append(plan_index.str());

		text.append(");\n\n");

		num_key++;
	}
	return text;
}

/**
  * Generates the initialization of all evaluation plan projects.
  */
string Builder_code::generate_initialize_plan_proj() const
{
	string text("  /**\n    * Initialize of Evaluation Plans Project.\n    */\n");

	int num_key = 0;
	for(map < Key_plan_project, unsigned short >::const_iterator it(b_plans.get_plans_project().begin()); it != b_plans.get_plans_project().end(); it++)
	{
		/* Generate key_plan */
		string name_key_plan(generate_key_plan(text, "key_plan_proj_", num_key, it->first.id_plan_project));

		stringstream str_index;
		str_index << num_key;

		text.append("  Key_plan_project ");
		string name_key("key_proj_");
		name_key.append(str_index.str());
		text.append(name_key);

		text.append("(");
		text.append(name_key_plan);
		text.append(", ");
		stringstream str_id_symb;
		str_id_symb << it->first.symbol_project->get_id();
		text.append(str_id_symb.str());
		text.append(", ");
		stringstream str_index_ocurrence;
		str_index_ocurrence << it->first.index_ocurrence;
		text.append(str_index_ocurrence.str());
		text.append(");\n");

		/* Generate insert in map */
		text.append("  add_plan_project(");
		text.append(name_key);
		text.append(" , ");
		stringstream plan_p_index;
		plan_p_index << it->second;
		text.append(plan_p_index.str());
		text.append(");\n\n");

		num_key++;
	}
	return text;
}

/**
  * Generates the initialization of all rules.
  */
string Builder_code::generate_initialize_rules() const
{
	string text("  /**\n    * Initialize of Rules of grammar.\n    */\n");

	const map<unsigned short, Rule> &rules = attr_grammar.get_rules();
	int index = 0;
	for (map < unsigned short, Rule >::const_iterator r_it (rules.begin()); r_it != rules.end(); r_it++)
	{
		stringstream str_index;
		str_index << index;

		vector<const Symbol*> right_side_non_terminals(r_it->second.get_non_terminals_right_side());
		vector<unsigned short> name_symbol_rule;

		name_symbol_rule.push_back(r_it->second.get_left_symbol()->get_id());
		for (size_t i(0); i < right_side_non_terminals.size(); i++)
		{
			name_symbol_rule.push_back(right_side_non_terminals[i]->get_id());
		}

		string name_vec(
			write_vector_with_inic<unsigned short>(
				text,
				"rule_non_terminal_",
				index,
				name_symbol_rule,
				"Rule",
				"unsigned short"
			)
		);

		text.append("  rules.push_back(");
		text.append(name_vec);
		text.append(");\n\n");

		index++;
	}
	return text;
}

/**
  * Generates and inserts the evaluator class's constructor.
  * With all initializations of Evaluation Plans, Evaluation Plans Project, Visit Sequences and Rules.
  */
void Builder_code::generate_constructor() const
{
	string cons_txt(file_name);
	cons_txt.append("::");
	cons_txt.append(file_name);
	cons_txt.append("()\n{\n");

	cons_txt.append(generate_initialize_context());

	cons_txt.append(generate_initialize_plans());

	cons_txt.append(generate_initialize_plan_proj());

	cons_txt.append(generate_initialize_v_seq());

	cons_txt.append(generate_initialize_rules());

	cons_txt.append("}\n\n");

	string path(path_output);
	path.append(file_name);
	path.append(".cpp");
	std::ofstream file_output(path.c_str(),ofstream::app);
	file_output.write(cons_txt.c_str(),cons_txt.size());
	file_output.close();
}

/**
  * Generates the print method, for show the all visit sequences.
  */
string Builder_code::generate_print() const
{
	string text("void ");
	text.append(file_name);
	text.append("::print_visit_seqs()\n  {\n");
	text.append("  for(size_t i(0); i < v_seq.size(); i++)\n");
	text.append("  {\n");
	text.append("    cout << \"Visit Sequence Nro \" << i+1 << \": \";\n");
	text.append("    for(size_t j(0); j < v_seq[i].size(); j++)\n");
	text.append("    {\n");
	text.append("      cout << v_seq[i][j];\n");
	text.append("      if(j < v_seq[i].size() - 1)\n");
	text.append("      {\n");
	text.append("        cout << \", \";\n");
	text.append("      }\n");
	text.append("    }\n");
	text.append("    cout << \".\" << endl;\n");
	text.append("  }\n");
	text.append("}\n\n");
	return text;
}

/**
  * Generates the print method, for show the all visit sequences in a format more descriptive.
  */
string Builder_code::generate_translate() const
{
	string text("void ");
	text.append(file_name);
	text.append("::translates_visit_segs()\n  {\n");
	text.append("  for(size_t v_s(0); v_s < v_seq.size(); v_s++)\n");
	text.append("  {\n");
	text.append("    for(size_t i(0); i < v_seq[v_s].size(); i++)\n");
	text.append("    {\n");
	text.append("      if(v_seq[v_s][i] > 0)\n");
	text.append("      {\n");
	text.append("        cout << \"Visit child \" << v_seq[v_s][i];\n");
	text.append("      }\n");
	text.append("      if(v_seq[v_s][i] == 0)\n");
	text.append("      {\n");
	text.append("        cout << \"Leave\";\n");
	text.append("      }\n");
	text.append("      if(v_seq[v_s][i] < 0)\n");
	text.append("      {\n");
	text.append("        cout << \"Compute \" << v_seq[v_s][i]*(-1);\n");
	text.append("      }\n");
	text.append("      if(i < v_seq[v_s].size() - 1)\n");
	text.append("      {\n");
	text.append("        cout << \", \";\n");
	text.append("      }\n");
	text.append("    }\n");
	text.append("    cout << \".\" << endl;\n");
	text.append("  }\n");
	text.append("}\n\n");
	return text;
}

/**
  * Generates the return_index_context method, for get the index of a context rule.
  */
string generate_return_index_context()
{
	string text("unsigned short return_index_context(const Order_rule &context, const vector < Order_rule > &v_contexts)\n");
	text.append("{\n");
	text.append("  for(size_t i(0); i < v_contexts.size(); i++)\n");
	text.append("  {\n");
	text.append("    if(context == v_contexts[i])\n");
	text.append("    {\n");
	text.append("      return i;\n");
	text.append("    }\n");
	text.append("  }\n");
	text.append("  return USHRT_MAX;\n");
	text.append("}\n\n");
	return text;
}

/**
  * Generates the method that crosses the AST and sets the evaluation plan that corresponds to each node.
  */
string Builder_code::generate_traverse() const
{
	string text("void ");
	text.append(file_name);
	text.append("::traverse(struct Node *node, unsigned short order)\n");
	text.append("{\n");
	text.append("  Order_rule context;\n");
	text.append("  context.push_back(node->rule_id);\n");
	text.append("  for(size_t i(0); i < node->childs.size(); i++)\n");
	text.append("  {\n");
	text.append("    context.push_back(node->childs[i]->rule_id);\n");
	text.append("  }\n");
	text.append("  unsigned short index_context(return_index_context(context, contexts_rule));\n");
	text.append("  if(index_context == USHRT_MAX)\n");
	text.append("  {\n");
	text.append("    cerr << \"ERROR: the AST input is wrong create. Context rule does not exist.\" << endl;\n");
	text.append("    exit(-1);\n");
	text.append("  }\n");
	text.append("  Key_plan k_plan(index_context, order);\n");
	text.append("  bool find_plan(false);\n");
	text.append("  for(size_t i(0); i < eval_plans.size(); i++)\n");
	text.append("  {\n");
	text.append("    if (eval_plans[i].first == k_plan)\n");
	text.append("    {\n");
	text.append("      node->visit_seq_index = eval_plans[i].second;\n");
	text.append("      node->pos_visit_seq = 0;\n");
	text.append("      find_plan = true;\n");
	text.append("      break;\n");
	text.append("    }\n");
	text.append("  }\n");
	text.append("  if(!find_plan)\n");
	text.append("  {\n");
	text.append("    cerr << \"ERROR: the AST input is wrong create. Evaluation plan does not exist.\" << endl;\n");
	text.append("    exit(-1);\n");
	text.append("  }\n");
	text.append("  Rule &rule(rules[node->rule_id - 1]);\n");
	text.append("  for(size_t i(0); i < node->childs.size(); i++)\n");
	text.append("  {\n");
	text.append("    Key_plan_project k_plan_proj(k_plan, rule[i+1], i);\n");
	text.append("    for(size_t j(0); j < eval_plans_project.size(); j++)\n");
	text.append("    {\n");
	text.append("      if (eval_plans_project[j].first == k_plan_proj)\n");
	text.append("      {\n");
	text.append("        traverse(node->childs[i], eval_plans_project[j].second);\n");
	text.append("        break;\n");
	text.append("      }\n");
	text.append("    }\n");
	text.append("  }\n");
	text.append("}\n\n");
	return text;
}

/**
  * Generates the plain text of a equation of this rule.
  */
string generate_expr_text(const Expression *node, const Rule &rule)
{
	string expr;
	const Expr_function *func(dynamic_cast<const Expr_function*>(node));
	if(func)
	{
		if (!func->get_function()->is_operator())
		{
			expr.append(func->get_function()->get_name());
			expr.append("(");
			for (size_t i(0); i < func->get_childs().size(); i++)
			{
				expr.append(generate_expr_text(func->get_child(i), rule));
				if (i < func->get_childs().size() - 1)
				{
					expr.append(", ");
				}
			}
			expr.append(")");
		}
		else
		{
			if(func->is_infix() || func->is_postfix())
			{
				expr.append("(");
				expr.append(generate_expr_text(func->get_child(0), rule));
				expr.append((func->is_postfix())? ") ": " ");
			}

			expr.append(func->get_function()->get_name());

			if(func->is_infix() || func->is_prefix())
			{
				expr.append((func->is_prefix())? " (": " ");
				unsigned short index_child((func->is_prefix())? 0: 1);
				expr.append(generate_expr_text(func->get_child(index_child), rule));
				expr.append(")");
			}
		}
	}
	else
	{
		const Expr_literal *lit(dynamic_cast<const Expr_literal *>(node));
		if(lit)
		{
			expr.append(lit->to_string());
		}
		else
		{
			const Expr_instance *ins((const Expr_instance *) node);

			if (ins->get_symb()->equals(*rule.get_left_symbol()) && (ins->get_num() == 0))
			{
				expr.append("node->");
			}
			else
			{
				expr.append("((");
				expr.append(ins->get_symb()->get_name());
				expr.append("*)node->childs[");
				unsigned short index = ins->get_num();

				if(ins->get_symb()->equals(*rule.get_left_symbol()))
				{
					/* It should consider that the left instance has zero index. */
					index--;
				}
				const vector<const Symbol*> vec(rule.get_non_terminals_right_side());
				for(size_t j(0); j < vec.size(); j++)
				{
					if (vec[j]->equals(*ins->get_symb()))
					{
						if (index == 0)
						{
							stringstream ins_index;
							ins_index << j;
							expr.append(ins_index.str());
							break;
						}
						index--;
					}
				}
				expr.append("])->");
			}
			expr.append(ins->get_attr()->get_name());
		}
	}
	return expr;
}

/**
  * Generates one method for each equation in the grammar, that computes it's value.
  */
string Builder_code::generate_all_methods_eqs() const
{
	string text;
	const map <unsigned short, Rule> &rules(attr_grammar.get_rules());
	for(map <unsigned short, Rule>::const_iterator r_it(rules.begin()); r_it != rules.end(); r_it++)
	{
		const map <unsigned short, Equation> &eqs(r_it->second.get_eqs());

		const Symbol *symb_rule(r_it->second.get_left_symbol());

		for(map <unsigned short, Equation>::const_iterator eq_it(eqs.begin()); eq_it != eqs.end(); eq_it++)
		{
			stringstream str_i_eq;
			str_i_eq << eq_it->second.get_id();
			text.append("// Eq ");
			text.append(cleaning_tabs(eq_it->second.to_string()));
			text.append("\nvoid compute_eq_");
			text.append(str_i_eq.str());
			text.append("(struct Node *root)\n");
			text.append("{\n  ");
			text.append(symb_rule->get_name());
			text.append(" *node((");
			text.append(symb_rule->get_name());
			text.append("*) root);\n");

			const Expr_instance *ins_left(eq_it->second.get_l_value());

			if (ins_left->get_symb()->equals(*symb_rule))
			{
				text.append("  node->");
			}
			else
			{
				text.append("  ((");
				text.append(ins_left->get_symb()->get_name());
				text.append("*)node->childs[");
				unsigned short index = ins_left->get_num();
				const vector<const Symbol*> vec(r_it->second.get_non_terminals_right_side());
				for(size_t j(0); j < vec.size(); j++)
				{
					if (vec[j]->equals(*ins_left->get_symb()))
					{
						if (index == 0)
						{
							stringstream ins_index;
							ins_index << j;
							text.append(ins_index.str());
							break;
						}
						index--;
					}
				}
				text.append("])->");
			}
			text.append(ins_left->get_attr()->get_name());
			text.append(" = ");

			string text_expr(generate_expr_text(eq_it->second.get_r_value(), r_it->second));
			text.append(text_expr);
			text.append(";\n");
			text.append("}\n\n");
		}
	}
	return text;
}

/**
  * Generates a method with a large switch with all equations, invoking in each case,
  * the method that computes.
  */
string Builder_code::generate_all_compute_eq() const
{
	string text("void ");
	text.append(file_name);
	text.append("::compute_eq(int num_eq, struct Node *root)\n");
	text.append("{\n");
	text.append("  switch ( num_eq ) {\n");

	for(size_t i(0); i < attr_grammar.get_count_eqs(); i++)
	{
		stringstream str_i;
		str_i << i+1;
		text.append("    case ");
		text.append(str_i.str());
		text.append(": compute_eq_");
		text.append(str_i.str());
		text.append("(root); break;\n");
	}
	text.append("    default: cout << \"ERROR: Fatal action.\" << endl;\n");
	text.append("  }\n");
	text.append("}\n\n");
	return text;
}

/**
  * Generates the evaluator method, which following the visit sequences drawn,
  * visit the nodes of the tree until computes it completely.
  */
string Builder_code::generate_eval_visiter() const
{
	string text("void ");
	text.append(file_name);
	text.append("::eval_visiter(struct Node *root)\n");
	text.append("{\n");
	text.append("  for(size_t i(root->pos_visit_seq); i < v_seq[root->visit_seq_index].size(); i++)\n");
	text.append("  {\n");
	text.append("    int item_visit(v_seq[root->visit_seq_index][i]);\n");
	text.append("    if (item_visit > 0)\n");
	text.append("    {\n");
	text.append("      eval_visiter(root->childs[item_visit - 1]);\n");
	text.append("    }\n");
	text.append("    else if (item_visit < 0)\n");
	text.append("    {\n");
	text.append("      compute_eq((item_visit * (-1)), root);\n");
	text.append("    }\n");
	text.append("    else\n");
	text.append("    {\n");
	text.append("      /* Saves the index of the current v_seq item. */\n");
	text.append("      root->pos_visit_seq = i+1;\n");
	text.append("      return;\n");
	text.append("    }\n");
	text.append("  }\n");
	text.append("}\n\n");
	return text;
}

/**
  * Generates the evaluating method, which performs the method invocations
  * to be computed all the attributes of the AST.
  */
string Builder_code::generate_evaluator() const
{
	string text("void ");
	text.append(file_name);
	text.append("::evaluator_mag(struct Node *root)\n");
	text.append("{\n");

	text.append("  unsigned short order_init(");
	stringstream order_init_index;
	order_init_index << b_plans.get_init_order();
	text.append(order_init_index.str());
	text.append(");\n");

	text.append("  traverse(root, order_init);\n");
	text.append("  eval_visiter(root);\n");
	text.append("}\n");
	return text;
}

/**
  * Generates and inserts the class method that insert a new plan.
  */
string Builder_code::generate_add_plan() const
{
	string text("void ");
	text.append(file_name);
	text.append("::add_plan(const Key_plan &k_plan, unsigned short index_order)\n");
	text.append("{\n");
	text.append("   Plan plan(k_plan, index_order);\n");
	text.append("   eval_plans.push_back(plan);\n");
	text.append("}\n\n");
	return text;
}

/**
  * Generates and inserts the class method that insert a new projected plan.
  */
string Builder_code::generate_add_plan_project() const
{
	string text("void ");
	text.append(file_name);
	text.append("::add_plan_project(const Key_plan_project &k_plan_p, unsigned short index_order)\n");
	text.append("{\n");
	text.append("   Plan_project plan(k_plan_p, index_order);\n");
	text.append("   eval_plans_project.push_back(plan);\n");
	text.append("}\n\n");
	return text;
}

/**
  * Generates and inserts all class methods, includind traverse, visit evaluator and the main evaluator.
  * This methods are based on the article by Wuu Yang.
  */
void Builder_code::generate_methods() const
{
	string methods_t;

	methods_t.append(generate_print());

	methods_t.append(generate_add_plan());

	methods_t.append(generate_add_plan_project());

	methods_t.append(generate_translate());

	methods_t.append(generate_return_index_context());

	methods_t.append(generate_traverse());

	methods_t.append(generate_all_methods_eqs());

	methods_t.append(generate_all_compute_eq());

	methods_t.append(generate_eval_visiter());

	methods_t.append(generate_evaluator());

	string path(path_output);
	path.append(file_name);
	path.append(".cpp");
	std::ofstream file_output(path.c_str(), ofstream::app);
	file_output.write(methods_t.c_str(),methods_t.size());
	file_output.close();
}

/**
  * Generates and inserts all structs for represent each symbol of the grammar.
  * With constructor and to_string methods.
  *
  * For symbol S, with attrs s1 \<syn\> int, inserts:
  *
  * typedef struct Symbol_S: Node
  * {
  *   int s0;
  *
  *   Symbol_S(unsgned short r_id);
  *
  *   string to_string() const;
  * } S ;
  */
void Builder_code::generate_structs() const
{
	string structs("/**\n  * Structs of the symbols.\n  */\n");
	string text_constructor("/**\n  * Constructors of structs of the symbols.\n  */\n");
	string text_to_string("/**\n  * To_string of structs of the symbols.\n  */\n");

	const map<string, Symbol> &symbol_non_terminals(attr_grammar.get_non_terminal_symbols());

	for(map<string, Symbol>::const_iterator it_symb(symbol_non_terminals.begin()); it_symb != symbol_non_terminals.end(); it_symb++)
	{
		structs.append("typedef struct Symbol_");
		structs.append(it_symb->second.get_name());
		structs.append(": Node\n{\n");

		text_to_string.append("string ");
		text_to_string.append(it_symb->second.get_name());
		text_to_string.append("::to_string() const\n{\n");
		text_to_string.append("  string text(\"-- Values of symbol ");
		text_to_string.append(it_symb->second.get_name());
		text_to_string.append(":\\n\");\n");

		const vector<const Attribute*> &attrs(it_symb->second.get_attrs());
		for(size_t j(0); j < attrs.size(); j++)
		{
			structs.append("  ");
			structs.append(attrs[j]->get_sort_type()->get_name());
			structs.append(" ");
			structs.append(attrs[j]->get_name());
			structs.append(";");
			structs.append("\n");

			text_to_string.append("  text.append(\"   - Attribute ");
			if(attrs[j]->is_synthetize())
			{
				text_to_string.append("synthesized ");
			}
			else
			{
				text_to_string.append("inherited ");
			}
			text_to_string.append(attrs[j]->get_name());
			text_to_string.append(" = \");\n");

			if(attrs[j]->get_sort_type()->is_type_basic())
			{
				if((attrs[j]->get_sort_type()->get_name().compare("int") == 0) ||
				   (attrs[j]->get_sort_type()->get_name().compare("float") == 0))
				{
					string name_sstr("str_");
					name_sstr.append(attrs[j]->get_name());

					text_to_string.append("  stringstream ");
					text_to_string.append(name_sstr);
					text_to_string.append(";\n  ");
					text_to_string.append(name_sstr);
					text_to_string.append(" << ");
					text_to_string.append(attrs[j]->get_name());
					text_to_string.append(";\n");
					text_to_string.append("  text.append(");
					text_to_string.append(name_sstr);
					text_to_string.append(".str());\n");
				}
				else if (attrs[j]->get_sort_type()->get_name().compare("bool") == 0)
				{
					text_to_string.append("  text.append((");
					text_to_string.append(attrs[j]->get_name());
					text_to_string.append(")? \"true\": \"false\");\n");
				}
				else
				/* The attribute is a string or a char. */
				{
					text_to_string.append("  text.append(");
					text_to_string.append(attrs[j]->get_name());
					text_to_string.append(");\n");
				}
			}
			else
			{
				text_to_string.append("  text.append(");
				text_to_string.append(attrs[j]->get_name());
				text_to_string.append(".to_string());\n");
			}
			text_to_string.append("  text.append(\"\\n\");\n");
		}

		/* Generate constructor signature. */
		structs.append("\n  Symbol_");
		structs.append(it_symb->second.get_name());
		structs.append("(const unsigned short &r_id);\n");

		/* Generate constructor method. */
		text_constructor.append(it_symb->second.get_name());
		text_constructor.append("::Symbol_");
		text_constructor.append(it_symb->second.get_name());
		text_constructor.append("(const unsigned short &r_id): Node(r_id){}\n\n");

		/* Generate method to_string() */
		structs.append("\n  string to_string() const;\n");

		/* Generate recursive call to all childs. */
		text_to_string.append("  for(size_t i(0); i < childs.size(); i++)\n  {\n");
		text_to_string.append("    text.append(childs[i]->to_string());\n  }\n");
		text_to_string.append("  return text;\n");
		text_to_string.append("}\n\n");

		structs.append("} ");
		structs.append(it_symb->second.get_name());
		structs.append(" ;\n\n");
	}

	string path_header(path_output);
	path_header.append(file_name);
	path_header.append(".hpp");
	std::ofstream header_output(path_header.c_str(),ofstream::app);
	header_output.write(structs.c_str(), structs.size());
	header_output.close();

	string path_code(path_output);
	path_code.append(file_name);
	path_code.append(".cpp");
	std::ofstream code_output(path_code.c_str(),ofstream::app);
	code_output.write(text_constructor.c_str(), text_constructor.size());
	code_output.write(text_to_string.c_str(), text_to_string.size());
	code_output.close();
}

/**
  * Generates the header and source code of the static evaluator of the grammar passed as parameter,
  * alog with their evaluations plans, visit sequence and headers for uses user functions defined.
  */
bool Builder_code::generate_code(const vector<string> &headers_file, const string path) const
{
	generate_header_file();
	generate_code_file(headers_file);

	generate_structs();
	generate_constructor();
	generate_methods();

	generate_footer_header();
	generate_footer_code();

	if (!copy_static_code(path_output, path))
	{
		cout << "* Generation code ---------- [ FAIL ]" << endl;
		return false;
	}

	cout << "* Generation code ---------- [  OK  ]" << endl;
	return true;
}

} /* end namespace */
