/**
  *  \file		Gen_code.cpp
  *  \brief		Implementation of the methods the Gen_code.h.
  *  \date		18/03/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <fstream>
#include <iostream>
#include <time.h>

#include "../Evaluation/Builder_plan.h"
#include "../Ast/Ast_function.h"
#include "../Ast/Ast_literal.h"
#include "../Ast/Ast_instance.h"
#include "../Util/Utilities.h"

#include "Gen_code.h"

using namespace std;
using namespace utilities;

namespace genevalmag
{

const string FILE_GRAMMAR("Grammar_mag.log");
const string FILE_NAME("Eval_mag.hpp");
const string DEFAULT_PATH("../GenEvalAG/");
const string DEFAULT_FOLDER("Out_Gen_Mag/");

Gen_code::Gen_code()
{
	string path(DEFAULT_PATH);
	path.append(DEFAULT_FOLDER);
	create_folder(path);
	path_output_code = path;
	full_path = path_output_code;
	full_path.append(FILE_NAME);
}

Gen_code::Gen_code(string path)
{
	string _path(path);
	_path.append(DEFAULT_FOLDER);
	create_folder(_path);
	path_output_code = _path;
	full_path = path_output_code;
	full_path.append(FILE_NAME);
}

Gen_code::~Gen_code()
{

}

void Gen_code::generate_grammar_file(const Attr_grammar &attr_grammar) const
{
	string p_grammar(path_output_code);
	p_grammar.append(FILE_GRAMMAR);

	string grammar_t;

	grammar_t.append("/**\n");
	grammar_t.append("  *  \\file      ");
	grammar_t.append(FILE_GRAMMAR);
	grammar_t.append("\n");
	grammar_t.append("  *  \\brief     Specification of the parsed grammar mag.\n");
	grammar_t.append("  *  \\date      ");
	time_t rawtime;
	struct tm *timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	grammar_t.append(asctime (timeinfo));
	grammar_t.append("  *  \\author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>\n");
	grammar_t.append("  *  \\author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>\n");
	grammar_t.append("*/\n\n");

	grammar_t.append(attr_grammar.to_string());

	std::ofstream file_output(p_grammar.c_str());
	file_output.write(grammar_t.c_str(), grammar_t.size());
	file_output.close();
}

void Gen_code::generate_header_file()
{
	string header;
	header.append("/**\n");
	header.append("  *  \\file      ");
	header.append(FILE_NAME);
	header.append("\n");
	header.append("  *  \\brief     Class generator from static evaluator generator: GENEVALMAG \n");

	header.append("  *  \\date      ");
	time_t rawtime;
	struct tm *timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	header.append(asctime (timeinfo));

	header.append("  *  \\author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>\n");
	header.append("  *  \\author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>\n");
	header.append("*/\n\n");

	header.append("#ifndef EVAL_MAG_HPP_\n");
	header.append("#define EVAL_MAG_HPP_\n\n");

	header.append("#include <stdlib.h>\n");
	header.append("#include <iostream>\n");
	header.append("#include <sstream>\n");
	header.append("#include <vector>\n");
	header.append("#include \"Node.hpp\"\n");
	header.append("#include \"Plan.hpp\"\n\n");

	header.append("using namespace std;\n");
	header.append("using namespace util_ag;\n\n");

	std::ofstream file_output(full_path.c_str());
	file_output.write(header.c_str(),header.size());
	file_output.close();
}

void Gen_code::generate_header_class()
{
	string header;
	header.append("class Eval_mag\n");
	header.append("{\n");

	std::ofstream file_output(full_path.c_str(),ofstream::app);
	file_output.write(header.c_str(),header.size());
	file_output.close();
}

void Gen_code::generate_footer()
{
	string footer;
	footer.append("};\n\n");
	footer.append("} /* end namespace */\n\n");
	footer.append("#endif /* EVAL_MAG_HPP_ */\n\n");

	std::ofstream file_output(full_path.c_str(),ofstream::app);
	file_output.write(footer.c_str(),footer.size());
	file_output.close();
}

template <class T>
string write_vector_with_inic(string &text_buffer, string name_vec, size_t index, const vector<T> &vec, string type_vec, const string type_array)
{
	text_buffer.append("            ");
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
	text_buffer.append("};\n");

	text_buffer.append("            ");
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

void generate_initialize_v_seq(string &text, const vector<Visit_seq> & v_seq)
{
	text.append("            /**\n              * Initialize of Visit Sequences.\n              */\n\n");

	for(size_t i(0); i < v_seq.size(); i++)
	{
		string name_vec(
			write_vector_with_inic<int>(
				text,
				"order_",
				i,
				v_seq[i],
				"Visit_sequence",
				"int"
			)
		);

		text.append("            v_seq.push_back(");
		text.append(name_vec);
		text.append(");\n\n");
	}
}

string generate_key_plan(string &text,const string n_key,int num_key, Key_plan k_p )
{
	/* generate key_plan */

	/* it->first.id_plan */
	text.append("            Key_plan ");
	string name_key(n_key);
	stringstream str_index;
	str_index << num_key;
	name_key.append(str_index.str());
	text.append(name_key);
	text.append(";\n");

//	text.append(name_key);
//	text.append(".id_plan.father = ");
//	stringstream father;
//	father << k_p.id_plan.father;
//	text.append(father.str());
//	text.append(";\n");

	string context_key ("context_");
	context_key.append(n_key);
	string name_o_rule(
		write_vector_with_inic<unsigned short>(
			text,
			context_key,
			num_key,
			k_p.id_plan,
			"Order_rule",
			"unsigned short"
		)
	);

	text.append("            ");
	text.append(name_key);
	text.append(".id_plan = ");
	text.append(name_o_rule);
	text.append(";\n");

	/* it->first.plan */
	string key_order ("key_order_eq_");
	key_order.append(n_key);
	string name_order_eval(
		write_vector_with_inic<unsigned short>(
			text,
			key_order,
			num_key,
			k_p.plan,
			"Order_eval_eq",
			"unsigned short"
		)
	);

	text.append("            ");
	text.append(name_key);
	text.append(".plan = ");
	text.append(name_order_eval);
	text.append(";\n\n");
	return name_key;
}

void generate_initialize_plans(string &text, const map < Key_plan, Order_eval_eq > &plans_p)
{
	text.append("            /**\n              * Initialize of Evaluation Plans.\n              */\n\n");

	int num_key = 0;
	for(map < Key_plan, Order_eval_eq >::const_iterator it(plans_p.begin()); it != plans_p.end(); it++)
	{
		/* generate key_plan */
		string name_key(generate_key_plan(text, "key_", num_key, it->first));

		stringstream str_index;
		str_index << num_key;

		/* generate key_order_eval_eq */
		string name_order(
			write_vector_with_inic<unsigned short>(
				text,
				"order_eq_",
				num_key,
				it->second,
				"Order_eval_eq",
				"unsigned short"
			)
		);

		/* generate insert in map */
		text.append("            Plan ");
		string name_new_p("__plan_");
		name_new_p.append(str_index.str());
		text.append(name_new_p);
		text.append("(");
		text.append(name_key);
		text.append(" , ");
		text.append(name_order);
		text.append(");\n");
		text.append("            eval_plans.push_back(");
		text.append(name_new_p);
		text.append(");\n\n");

		num_key++;
	}
}

void generate_initialize_plan_proj(string &text, const map < Key_plan_project, Order_eval_eq > &plans_p)
{
	text.append("            /**\n              * Initialize of Evaluation Plans Project.\n              */\n\n");

	int num_key = 0;
	for(map < Key_plan_project, Order_eval_eq >::const_iterator it(plans_p.begin()); it != plans_p.end(); it++)
	{
		/* generate key_plan */
		string name_key_plan(generate_key_plan(text, "key_plan_proj_", num_key, it->first.id_plan_project));

		stringstream str_index;
		str_index << num_key;

		text.append("            Key_plan_project ");
		string name_key("key_proj_");
		name_key.append(str_index.str());
		text.append(name_key);

		text.append(";\n            ");

		text.append(name_key);
		text.append(".id_plan_project = ");
		text.append(name_key_plan);
		text.append(";\n");

		/* it->second */
		text.append("            ");
		text.append(name_key);
		text.append(".node_project = \"");
		text.append(it->first.symbol_project->get_name());
		text.append("\";\n");

		/* generate key_order_eval_eq */
		string name_order(
			write_vector_with_inic<unsigned short>(
				text,
				"order_eq_proj_",
				num_key,
				it->second,
				"Order_eval_eq",
				"unsigned short"
			)
		);

		/* generate insert in map */
		text.append("            Plan_project ");
		string name_new_p("__plan_proj_");
		name_new_p.append(str_index.str());
		text.append(name_new_p);
		text.append("(");
		text.append(name_key);
		text.append(" , ");
		text.append(name_order);
		text.append(");\n");
		text.append("            eval_plans_project.push_back(");
		text.append(name_new_p);
		text.append(");\n\n");

		num_key++;
	}
}

void Gen_code::generate_private()
{
	string private_t;
	private_t.append("    private:\n");
	private_t.append("        vector < Visit_sequence >    v_seq;\n");
	private_t.append("        /* \"ro\" function. Wuu yank's paper. */\n");
	private_t.append("        vector < Plan >              eval_plans;\n");
	private_t.append("        /* \"tita\" function. Wuu yank's paper. */\n");
	private_t.append("        vector < Plan_project >      eval_plans_project;\n");
	private_t.append("        vector < Rule >              rules;\n");

	std::ofstream file_output(full_path.c_str(),ofstream::app);
	file_output.write(private_t.c_str(),private_t.size());
	file_output.close();
}

void generate_initialize_rules(string &text, const Attr_grammar &attr_grammar)
{
	text.append("            /**\n              * Initialize of Rules of grammar.\n              */\n\n");

	const map<unsigned short, Rule> &rules = attr_grammar.get_rules();
	int index = 0;
	for (map < unsigned short, Rule >::const_iterator r_it (rules.begin()); r_it != rules.end(); r_it++)
	{
		stringstream str_index;
		str_index << index;

		vector<const Symbol*> right_side_non_terminals(r_it->second.get_non_terminals_right_side());
		vector<string> name_symbol_rule;

		string name_aux("\"");
		name_aux.append(r_it->second.get_left_symbol()->get_name());
		name_aux.append("\"");
		name_symbol_rule.push_back(name_aux);
		for (size_t i(0); i < right_side_non_terminals.size(); i++)
		{
			name_aux = "\"";
			name_aux.append(right_side_non_terminals[i]->get_name());
			name_aux.append("\"");
			name_symbol_rule.push_back(name_aux);
		}

		string name_vec(
			write_vector_with_inic<string>(
				text,
				"rule_non_terminal_",
				index,
				name_symbol_rule,
				"Rule",
				"string"
			)
		);

		text.append("            rules.push_back(");
		text.append(name_vec);
		text.append(");\n\n");

		index++;
	}
}

void Gen_code::generate_public(const vector<Visit_seq> & v_seq, const Builder_plan &b_plan, const Attr_grammar &attr_grammar)
{
	string public_t;
	public_t.append("\n    public:\n");
	public_t.append("        Eval_mag()\n");
	public_t.append("        {\n");

	generate_initialize_plans(public_t, b_plan.get_plans());

	generate_initialize_plan_proj(public_t, b_plan.get_plans_project());

	generate_initialize_v_seq(public_t, v_seq);

	generate_initialize_rules(public_t, attr_grammar);

	public_t.append("        }\n\n");

	std::ofstream file_output(full_path.c_str(),ofstream::app);
	file_output.write(public_t.c_str(),public_t.size());
	file_output.close();
}

void generate_print(string &text)
{
	text.append("        void print_v_seq()\n        {\n");
	text.append("            for(size_t i(0); i < v_seq.size(); i++)\n");
	text.append("            {\n");
	text.append("            	cout << \"Visit Sequence Nro \" << i+1 << \": \";\n");
	text.append("            	for(size_t j(0); j < v_seq[i].size(); j++)\n");
	text.append("            	{\n");
	text.append("            		cout << v_seq[i][j];\n");
	text.append("            		if(j < v_seq[i].size() - 1)\n");
	text.append("            		{\n");
	text.append("            			cout << \", \";\n");
	text.append("            		}\n");
	text.append("            	}\n");
	text.append("            	cout << \".\" << endl;\n");
	text.append("            }\n");
	text.append("        }\n\n");
}

void generate_translate(string &text)
{
	text.append("        void translate_mag(int v_s)\n        {\n");
	text.append("            for(size_t i(0); i < v_seq[v_s].size(); i++)\n");
	text.append("            {\n");
	text.append("            	if(v_seq[v_s][i] > 0)\n            	{\n");
	text.append("            	    cout << \"Visit child \" << v_seq[v_s][i];\n");
	text.append("            	}\n");
	text.append("            	if(v_seq[v_s][i] == 0)\n            	{\n");
	text.append("            	    cout << \"Leave\";\n");
	text.append("            	}\n");
	text.append("            	if(v_seq[v_s][i] < 0)\n            	{\n");
	text.append("            	    cout << \"Compute \" << v_seq[v_s][i]*(-1);\n");
	text.append("            	}\n");
	text.append("            	if(i < v_seq[v_s].size() - 1)\n            	{\n");
	text.append("            	    cout << \", \";\n");
	text.append("            	}\n");
	text.append("            }\n");
	text.append("            cout << \".\" << endl;\n");
	text.append("        }\n\n");
}

void generate_traverse(string &text)
{
	text.append("        void traverse(struct Node * node, Order_eval_eq order)\n");
	text.append("        {\n");
	text.append("            Key_plan k_plan;\n");
	text.append("            k_plan.id_plan.push_back(node->rule_id);\n");
	text.append("            for(size_t i(0); i < node->childs.size(); i++)\n");
	text.append("            {\n");
	text.append("                k_plan.id_plan.push_back(node->childs[i]->rule_id);\n");
	text.append("            }\n");
	text.append("            k_plan.plan = order;\n");
	text.append("            bool find_plan(false);\n");
	text.append("            for(size_t i(0); i < eval_plans.size(); i++)\n");
	text.append("            {\n");
	text.append("                if (eval_plans[i].first == k_plan)\n");
	text.append("                {\n");
	text.append("                    node->index_plan_v_seq = i;\n");
	text.append("                    node->num_v_seq = 0;\n");
	text.append("                    find_plan = true;\n");
	text.append("                    break;\n");
	text.append("                }\n");
	text.append("            }\n");

	text.append("            if(!find_plan)\n");
	text.append("            {\n");
	text.append("                cerr << \"ERROR: the AST input is wrong create.\" << endl;\n");
	text.append("                exit(-1);\n");
	text.append("            }\n");

	text.append("            Rule &rule(rules[node->rule_id - 1]);\n");
	text.append("            for(size_t i(0); i < node->childs.size(); i++)\n");
	text.append("            {\n");
	text.append("                Key_plan_project k_plan_proj;\n");
	text.append("                k_plan_proj.id_plan_project = k_plan;\n");
	text.append("                k_plan_proj.node_project = rule[i+1];\n");
	text.append("                for(size_t j(0); j < eval_plans_project.size(); j++)\n");
	text.append("                {\n");
	text.append("                    if (eval_plans_project[j].first == k_plan_proj)\n");
	text.append("                    {\n");
	text.append("                        traverse(node->childs[i], eval_plans_project[j].second);\n");
	text.append("                        break;\n");
	text.append("                    }\n");
	text.append("                }\n");
	text.append("            }\n");
	text.append("        }\n\n");
}

string generate_expr_text(const Ast_node *node, const Rule &rule)
{
	string expr;
	const Ast_function* func(dynamic_cast<const Ast_function*>(node));
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
		const Ast_literal *lit(dynamic_cast<const Ast_literal *>(node));
		if(lit)
		{
			expr.append(lit->to_string());
		}
		else
		{
			const Ast_instance *ins((const Ast_instance *) node);

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

void generate_all_methods_eqs(string &text, const Attr_grammar &attr_grammar)
{
	const map <unsigned short, Rule> &rules(attr_grammar.get_rules());
	for(map <unsigned short, Rule>::const_iterator r_it(rules.begin()); r_it != rules.end(); r_it++)
	{
		const map <unsigned short, Equation> &eqs(r_it->second.get_eqs());

		const Symbol *symb_rule(r_it->second.get_left_symbol());

		for(map <unsigned short, Equation>::const_iterator eq_it(eqs.begin()); eq_it != eqs.end(); eq_it++)
		{
			stringstream str_i_eq;
			str_i_eq << eq_it->second.get_id();
			text.append("        // Eq ");
			text.append(cleaning_tabs(eq_it->second.to_string()));
			text.append("\n        void compute_eq_");
			text.append(str_i_eq.str());
			text.append("(struct Node *root)\n");
			text.append("        {\n            ");
			text.append(symb_rule->get_name());
			text.append(" *node((");
			text.append(symb_rule->get_name());
			text.append("*) root);\n");

			const Ast_instance *ins_left(eq_it->second.get_l_value());

			if (ins_left->get_symb()->equals(*symb_rule))
			{
				text.append("            node->");
			}
			else
			{
				text.append("            ((");
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
			text.append("        }\n\n");
		}
	}
}

void generate_all_compute_eq(string &text, const Attr_grammar &attr_grammar)
{

	text.append("    	void compute_eq(int num_eq, struct Node *root)\n");
	text.append("     	{\n");
	text.append("    		switch ( num_eq ) {\n");

	for(size_t i(0); i < attr_grammar.get_count_eqs(); i++)
	{
		stringstream str_i;
		str_i << i+1;
		text.append("    		  case ");
		text.append(str_i.str());
		text.append(" :\n");
		text.append("    			compute_eq_");
		text.append(str_i.str());
		text.append("(root); break;\n\n");
	}
	text.append("     		  default :\n");
	text.append("     			cout << \"ERROR: Fatal action.\" << endl;\n");
	text.append("    		}\n");
	text.append("     	}\n\n");
}

void generate_eval_visiter(string &text)
{
	text.append("        void eval_visiter(struct Node *root)\n");
	text.append("        {\n");
	text.append("        	for(size_t i(root->num_v_seq); i < v_seq[root->index_plan_v_seq].size(); i++)\n");
	text.append("        	{\n");
	text.append("        		int item_visit(v_seq[root->index_plan_v_seq][i]);\n");
	text.append("        		if (item_visit > 0)\n");
	text.append("        		{\n");
	text.append("        		    eval_visiter(root->childs[item_visit - 1]);\n");

//	text.append("        			for(size_t j(0); j < root->childs.size(); j++)\n");
//	text.append("        			{\n");
//	text.append("        				if (root->childs[j]->rule_id == item_visit)\n");
//	text.append("        				{\n");
//	text.append("        					eval_visiter(root->childs[j]);\n");
//	text.append("        					break;\n");
//	text.append("        				}\n");
//	text.append("        			}\n");
	text.append("        		}\n");
	text.append("        		else if (item_visit < 0)\n");
	text.append("        		{\n");
	text.append("    				compute_eq((item_visit * -1), root);\n");
	text.append("        		}\n");
	text.append("        		else\n");
	text.append("        		{\n");
	text.append("        			root->num_v_seq = i+1; // donde quede\n");
	text.append("        			return;\n");
	text.append("        		}\n");
	text.append("        	}\n");
	text.append("        }\n\n");
}

void generate_evaluator(string &text, const Builder_plan &b_plan)
{
	text.append("        void evaluator_mag(struct Node *root)\n");
	text.append("        {\n");

	text.append("            vector < Order_eval_eq > orders_init;\n");

	const vector < Order_eval_eq > &init_orders = b_plan.get_init_orders();
	for(size_t i(0); i < init_orders.size(); i++)
	{
		string init_order_name(
			write_vector_with_inic<unsigned short>(
				text,
				"order_root_",
				i,
				init_orders[i],
				"Order_eval_eq",
				"unsigned short"
			)
		);

		text.append("            orders_init.push_back(");
		text.append(init_order_name);
		text.append(");\n");
	}

	text.append("        	traverse(root, orders_init[root->rule_id - 1]);\n");
	text.append("        	eval_visiter(root);\n");
	text.append("        }\n");
}

void Gen_code::generate_methods(const Builder_plan &b_plan, const Attr_grammar &attr_grammar)
{
	string methods_t;

	generate_print(methods_t);

	generate_traverse(methods_t);

	generate_translate(methods_t);

	generate_all_methods_eqs(methods_t, attr_grammar);

	generate_all_compute_eq(methods_t, attr_grammar);

	generate_eval_visiter(methods_t);

	generate_evaluator(methods_t, b_plan);

	std::ofstream file_output(full_path.c_str(), ofstream::app);
	file_output.write(methods_t.c_str(),methods_t.size());
	file_output.close();
}

void Gen_code::generate_externs(const Attr_grammar &attr_grammar)
{
	string externs;

	externs.append("/**\n  * Sorts of the Semantic Domains.\n  */\n\n");

	const map<string, Sort> &sorts(attr_grammar.get_sorts());

	for(map<string, Sort>::const_iterator it_s(sorts.begin()); it_s != sorts.end(); it_s++)
	{
		if(!it_s->second.is_type_basic())
		{
			externs.append("//extern ");
			externs.append(it_s->second.get_name());
			externs.append(";\n\n");
		}
	}

	externs.append("/**\n  * Functions and Operators of the Semantic Domains.\n  */\n\n");

	const map<string, Function> &funcs(attr_grammar.get_functions());

	for(map<string, Function>::const_iterator it_f(funcs.begin()); it_f != funcs.end(); it_f++)
	{
		externs.append("//extern ");
		externs.append(it_f->second.signature());
		externs.append("\n\n");
	}

	std::ofstream file_output(full_path.c_str(),ofstream::app);
	file_output.write(externs.c_str(),externs.size());
	file_output.close();
}

void Gen_code::generate_structs(const Attr_grammar &attr_grammar)
{
	string structs;
	structs.append("namespace evalmag\n");
	structs.append("{\n\n");

	structs.append("/**\n  * Structs of the symbols.\n  */\n\n");

	const map<string, Symbol> &symbol_non_terminals(attr_grammar.get_non_terminal_symbols());

	for(map<string, Symbol>::const_iterator it_symb(symbol_non_terminals.begin()); it_symb != symbol_non_terminals.end(); it_symb++)
	{
		structs.append("typedef struct Symbol_");
		structs.append(it_symb->second.get_name());
		structs.append(": Node\n{\n");

		string text_to_string("\n    string to_string() const\n    {\n");
		text_to_string.append("        string text(\"Values of symbol ");
		text_to_string.append(it_symb->second.get_name());
		text_to_string.append(":\\n\");\n");

		const vector<const Attribute*> &attrs(it_symb->second.get_attrs());
		for(size_t j(0); j < attrs.size(); j++)
		{
			structs.append("    ");
			structs.append(attrs[j]->get_sort_type()->get_name());
			structs.append(" ");
			structs.append(attrs[j]->get_name());
			structs.append(";");
			structs.append("\n");

			text_to_string.append("        text.append(\" Attr ");
			text_to_string.append(attrs[j]->get_name());
			text_to_string.append(" = \");\n");

			if(attrs[j]->get_sort_type()->is_type_basic())
			{
				if((attrs[j]->get_sort_type()->get_name().compare("int") == 0) ||
				   (attrs[j]->get_sort_type()->get_name().compare("float") == 0))
				{
					string name_sstr("str_");
					name_sstr.append(attrs[j]->get_name());

					text_to_string.append("        stringstream ");
					text_to_string.append(name_sstr);
					text_to_string.append(";\n        ");
					text_to_string.append(name_sstr);
					text_to_string.append(" << ");
					text_to_string.append(attrs[j]->get_name());
					text_to_string.append(";\n");
					text_to_string.append("        text.append(");
					text_to_string.append(name_sstr);
					text_to_string.append(".str());\n");
				}
				else
				{
					text_to_string.append("        text.append(");
					text_to_string.append(attrs[j]->get_name());
					text_to_string.append(");\n");
				}
			}
			else
			{
				text_to_string.append("        text.append(");
				text_to_string.append(attrs[j]->get_name());
				text_to_string.append(".to_string());\n");
			}
			text_to_string.append("        text.append(\"\\n\");\n");
		}

		/* Generate method to_string() */
		text_to_string.append("        for(size_t i(0); i < childs.size(); i++)\n        {\n");
		text_to_string.append("            text.append(childs[i]->to_string());\n        }\n");
		text_to_string.append("        return text;\n");
		text_to_string.append("    }\n");
		structs.append(text_to_string);
		structs.append("} ");
		structs.append(it_symb->second.get_name());
		structs.append(" ;\n\n");
	}

	std::ofstream file_output(full_path.c_str(), ofstream::app);
	file_output.write(structs.c_str(),structs.size());
	file_output.close();
}

void Gen_code::generate_code(const Attr_grammar &attr_grammar, const Builder_plan &b_plan, const vector<Visit_seq> & v_seq)
{
	generate_grammar_file(attr_grammar);
	generate_header_file();

	generate_externs(attr_grammar);
	generate_structs(attr_grammar);

	generate_header_class();
	generate_private();
	generate_public(v_seq,b_plan, attr_grammar);
	generate_methods(b_plan, attr_grammar);
	generate_footer();
}

} /* end namespace */
