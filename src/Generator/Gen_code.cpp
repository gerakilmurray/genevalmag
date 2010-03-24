/**
 * \file Gen_code.cpp
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 18/03/2010
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#include <fstream>
#include <iostream>
#include <time.h>

#include "Gen_code.h"
#include "../Evaluation/Builder_plan.h"

namespace genevalmag
{

const string FILE_GRAMMAR("Grammar_mag.log");
const string FILE_NAME("Eval_mag.cpp");
const string DEFAULT_PATH("../");

Gen_code::Gen_code()
{
	path_output_code = DEFAULT_PATH;
	full_path = path_output_code;
	full_path.append(FILE_NAME);
}

Gen_code::Gen_code(string path)
{
	path_output_code = path;
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

	header.append("#ifndef EVAL_MAG_CPP_\n");
	header.append("#define EVAL_MAG_CPP_\n\n");

	header.append("#include <iostream>\n");
	header.append("#include <vector>\n");
	header.append("#include \"GenEvalAG/src/Generator/Node.hpp\"\n");
	header.append("#include \"GenEvalAG/src/Generator/Plan.hpp\"\n\n");

	header.append("using namespace std;\n");
	header.append("using namespace util_ag;\n");
	std::ofstream file_output(full_path.c_str());
	file_output.write(header.c_str(),header.size());
	file_output.close();
}

void Gen_code::generate_header_class()
{
	string header;
	header.append("namespace evalmag\n");
	header.append("{\n\n");

	header.append("typedef vector<int> Visit_sequence;\n");

	header.append("typedef vector<string> Rule;\n");

	header.append("typedef pair< Key_plan,Order_eval_eq> Plan;\n");

	header.append("typedef pair< Key_plan_project,Order_eval_eq> Plan_project;\n\n");

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
	footer.append("#endif /* EVAL_MAG_CPP_ */\n\n");

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
	for(size_t i(0); i < v_seq.size(); i++)
	{
		string name_vec(write_vector_with_inic<int>(text, "order",i,v_seq[i],"Visit_sequence","int"));

		text.append("            v_seq.push_back(");
		text.append(name_vec);
		text.append(");\n");
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
	text.append(";\n            ");

	text.append(name_key);
	text.append(".id_plan.father = ");
	stringstream father;
	father << k_p.id_plan.father;
	text.append(father.str());
	text.append(";\n");

	string context_key ("context_");
	context_key.append(n_key);
	string name_o_rule(write_vector_with_inic<unsigned short>(text, context_key,num_key,k_p.id_plan.context,"Order_rule","unsigned short"));

	text.append("            ");
	text.append(name_key);
	text.append(".id_plan.context = ");
	text.append(name_o_rule);
	text.append(";\n");

		/* it->first.plan */
	string key_order ("key_order_eq_");
	key_order.append(n_key);
	string name_order_eval(write_vector_with_inic<unsigned short>(text, key_order,num_key,k_p.plan,"Order_eval_eq","unsigned short"));

	text.append("            ");
	text.append(name_key);
	text.append(".plan = ");
	text.append(name_order_eval);
	text.append(";\n\n");
	return name_key;
}

void generate_initialize_plans(string &text, const map < Key_plan, Order_eval_eq > &plans_p)
{
	int num_key = 0;
	for(map < Key_plan, Order_eval_eq >::const_iterator it(plans_p.begin()); it != plans_p.end(); it++)
	{
		/* generate key_plan */

			/* it->first.id_plan */

		string name_key(generate_key_plan(text,"key",num_key, it->first));

		stringstream str_index;
		str_index << num_key;

		/* generate key_Oder_eval_eq */

		string name_order(write_vector_with_inic<unsigned short>(text, "order_eq",num_key,it->second,"Order_eval_eq","unsigned short"));

		/* generate insert in map */
		text.append("            Plan ");
		string name_new_p("new_p");
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
	int num_key = 0;
	for(map < Key_plan_project, Order_eval_eq >::const_iterator it(plans_p.begin()); it != plans_p.end(); it++)
	{
		/* generate key_plan */

			/* it->first.id_plan */
		string name_key_plan(generate_key_plan(text,"key_plan_proj",num_key, it->first.id_plan_project));

		stringstream str_index;
		str_index << num_key;

		text.append("            Key_plan_project ");
		string name_key("key_proj");
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

		/* generate key_Oder_eval_eq */

		string name_order(write_vector_with_inic<unsigned short>(text, "order_eq_proj",num_key,it->second,"Order_eval_eq","unsigned short"));

		/* generate insert in map */
		text.append("            Plan_project ");
		string name_new_p("new_p_proj");
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

void generate_initialize_rules(string &text, const Attr_grammar &grammar)
{
	const map<unsigned short, Rule> &rules = grammar.get_rules();
	int index = 0;
	for (map < unsigned short, Rule >::const_iterator r_it (rules.begin()); r_it != rules.end();r_it++)
	{
		stringstream str_index;
		str_index << index;

		vector<const Symbol*> right_side_non_terminals(r_it->second.get_non_terminals_right_side());
		vector<string> name_symbol_rule;

		string name_aux("\"");
		name_aux.append(r_it->second.get_left_symbol()->get_name());
		name_aux.append("\"");
		name_symbol_rule.push_back(name_aux);
		for (size_t i(0); i< right_side_non_terminals.size();i++)
		{
			name_aux =  "\"";
			name_aux.append(right_side_non_terminals[i]->get_name());
			name_aux.append("\"");
			name_symbol_rule.push_back(name_aux);
		}

		string name_vec(write_vector_with_inic<string>(text, "rule_non_terminal_",index,name_symbol_rule,"Rule","string"));

		text.append("            rules.push_back(");
		text.append(name_vec);
		text.append(");\n\n");

		index++;
	}
}


void Gen_code::generate_public(const vector<Visit_seq> & v_seq, const Builder_plan &b_plan, const Attr_grammar &grammar)
{
	string public_t;
	public_t.append("    public:\n");
	public_t.append("        Eval_mag()\n");
	public_t.append("        {\n");

	generate_initialize_plans(public_t, b_plan.get_plans());

	generate_initialize_plan_proj(public_t, b_plan.get_plans_project());

	generate_initialize_v_seq(public_t, v_seq);

	generate_initialize_rules(public_t, grammar);

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
	text.append("            	    cout << \"Visit \" << v_seq[v_s][i];\n");
	text.append("            	}\n");
	text.append("            	if(v_seq[v_s][i] == 0)\n            	{\n");
	text.append("            	    cout << \"Leave\";\n");
	text.append("            	}\n");
	text.append("            	if(v_seq[v_s][i] < 0)\n            	{\n");
	text.append("            	    cout << \"Compute \" << v_seq[v_s][i]*(-1);\n");
	text.append("            	}\n");
	text.append("            	if(i < v_seq[v_s].size() -1)\n            	{\n");
	text.append("            	    cout << \", \";\n");
	text.append("            	}\n");
	text.append("            }\n");
	text.append("            cout << \".\" << endl;\n");
	text.append("        }\n\n");
}


void generate_traverse(string &text)
{
	text.append("        void traverse(struct Node * node, Order_eval_eq order, unsigned short father)\n");
	text.append("        {\n");
	text.append("            Key_plan k_plan;\n");
	text.append("            k_plan.id_plan.context.push_back(node->rule_id);\n");
	text.append("            for(size_t i(0); i< node->childs.size();i++ )\n");
	text.append("            {\n");
	text.append("                k_plan.id_plan.context.push_back(node->childs[i]->rule_id);\n");
	text.append("            }\n");
	text.append("            k_plan.id_plan.father = father;\n");
	text.append("            k_plan.plan = order;\n");
	text.append("            for(size_t i(0); i < eval_plans.size(); i++)\n");
	text.append("            {\n");
	text.append("                if (eval_plans[i].first == k_plan)\n");
	text.append("                {\n");
	text.append("                    node->index_plan_v_seq = i;\n");
	text.append("                }\n");
	text.append("            }\n");
	text.append("            Rule &rule = rules[node->rule_id];\n");
	text.append("            for(size_t i(0); i < node->childs.size(); i++)\n");
	text.append("            {\n");
	text.append("                Key_plan_project k_plan_proj;\n");
	text.append("                k_plan_proj.id_plan_project = k_plan;\n");
	text.append("                k_plan_proj.node_project = rule[i+1];\n");
	text.append("                for(size_t j(0); j < eval_plans_project.size(); j++)\n");
	text.append("                {\n");
	text.append("                    if (eval_plans_project[j].first == k_plan_proj)\n");
	text.append("                    {\n");
	text.append("                        traverse(node->childs[i], eval_plans_project[j].second, node->rule_id);\n");
	text.append("                        break;\n");
	text.append("                    }\n");
	text.append("                }\n");
	text.append("            }\n");
	text.append("        }\n\n");
}

void generate_evaluator(string &text, const Builder_plan &b_plan)
{
	const Order_eval_eq &init_order = b_plan.get_init_order();

	text.append("        void evaluator_mag(struct Node *root)\n");
	text.append("        {\n");

	string init_order_name (write_vector_with_inic<unsigned short>(text, "order_root", 0, init_order, "Order_eval_eq", "unsigned short"));

	text.append("        	traverse(root, order_root0, 0);\n");
	text.append("        	//eval_visiter(root);\n");
	text.append("        }\n");
}

void Gen_code::generate_methods(const Builder_plan &b_plan)
{
	string methods_t;

	generate_print(methods_t);

	generate_traverse(methods_t);

	generate_translate(methods_t);

	generate_evaluator(methods_t, b_plan);

	std::ofstream file_output(full_path.c_str(),ofstream::app);
	file_output.write(methods_t.c_str(),methods_t.size());
	file_output.close();
}

void Gen_code::generate_main()
{
	string main_text;
	main_text.append("using namespace evalmag;\n\n");
	main_text.append("/**\n");
	main_text.append("  * Main method of the Eval_mag.\n");
	main_text.append("  */\n");
	main_text.append("int main()\n");
	main_text.append("{\n");
	main_text.append("    Eval_mag eval_mag;\n");
	main_text.append("    eval_mag.print_v_seq();\n");
	main_text.append("    eval_mag.translate_mag(0);\n");
	main_text.append("    eval_mag.translate_mag(1);\n");
	main_text.append("    eval_mag.translate_mag(2);\n");
	main_text.append("    eval_mag.translate_mag(3);\n");
	main_text.append("    eval_mag.translate_mag(4);\n");
	main_text.append("    eval_mag.translate_mag(5);\n");
	main_text.append("    eval_mag.translate_mag(6);\n");
	main_text.append("    eval_mag.translate_mag(7);\n");
	main_text.append("    eval_mag.translate_mag(8);\n\n");
	main_text.append("    eval_mag.evaluator_mag();\n");
	main_text.append("    return 0;\n");
	main_text.append("}\n");

	std::ofstream file_output(full_path.c_str(),ofstream::app);
	file_output.write(main_text.c_str(),main_text.size());
	file_output.close();
}

void Gen_code::generate_externs(const Attr_grammar &attr_grammar)
{
	string externs;

	externs.append("/**\n * Sorts of the Semantic Domains.\n */\n\n");

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

	externs.append("/**\n * Functions and Operators of the Semantic Domains.\n */\n\n");

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

	structs.append("/**\n * Structs of the symbols.\n */\n\n");

	const map<string, Symbol> &symbol_non_terminals(attr_grammar.get_non_terminal_symbols());

	for(map<string, Symbol>::const_iterator it_symb(symbol_non_terminals.begin()); it_symb != symbol_non_terminals.end(); it_symb++)
	{
		structs.append("typedef struct Symbol_");
		structs.append(it_symb->second.get_name());
		structs.append(": Node\n{\n");
		const vector<const Attribute*> &attrs(it_symb->second.get_attrs());
		for(size_t j(0);j< attrs.size();j++)
		{
			structs.append("    ");
			structs.append(attrs[j]->get_sort_type()->get_name());
			structs.append(" ");
			structs.append(attrs[j]->get_name());
			structs.append(";");
			structs.append("\n");
		}
		structs.append("} ");
		structs.append(it_symb->second.get_name());
		structs.append(" ;\n\n");
	}

	std::ofstream file_output(full_path.c_str(),ofstream::app);
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
	generate_methods(b_plan);
	generate_footer();
	generate_main();
}

} /* end namespace */
