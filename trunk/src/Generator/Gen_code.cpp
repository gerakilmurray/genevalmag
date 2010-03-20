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
	header.append("#include <vector>\n\n");

	header.append("using namespace std;\n\n");

	std::ofstream file_output(full_path.c_str());
	file_output.write(header.c_str(),header.size());
	file_output.close();
}

void Gen_code::generate_header_class()
{
	string header;
	header.append("namespace evalmag\n");
	header.append("{\n\n");

	header.append("typedef vector<int> Visit_sequence;\n\n");

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

void generate_initialize(string &text, const vector<Visit_seq> & v_seq)
{
	for(size_t i(0); i < v_seq.size(); i++)
	{
		text.append("            int ");
		string name ("order");

		stringstream index;
		index << i;
		name.append(index.str());

		text.append(name);
		text.append("[] = ");

		text.append("{");
		for(size_t j(0); j < v_seq[i].size(); j++)
		{
			stringstream i_seq_visit;
			i_seq_visit << v_seq[i][j];
			text.append(i_seq_visit.str());
			if(j < v_seq[i].size() - 1)
			{
				text.append(",");
			}
		}
		text.append("};\n");
		text.append("            Visit_sequence vec_");
		text.append(name);
		text.append("(");
		text.append(name);
		text.append(", ");
		text.append(name);
		text.append(" + sizeof(");
		text.append(name);
		text.append(") / sizeof(int));\n");

		text.append("            v_seq.push_back(vec_");
		text.append(name);
		text.append(");\n");
	}
}

void Gen_code::generate_private()
{
	string private_t;
	private_t.append("    private:\n");
	private_t.append("        vector<Visit_sequence> v_seq;\n");

	std::ofstream file_output(full_path.c_str(),ofstream::app);
	file_output.write(private_t.c_str(),private_t.size());
	file_output.close();
}


void Gen_code::generate_public(const vector<Visit_seq> & v_seq)
{
	string public_t;
	public_t.append("    public:\n");
	public_t.append("        Eval_mag()\n");
	public_t.append("        {\n");

	generate_initialize(public_t, v_seq);

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


void generate_evaluator(string &text)
{
	text.append("        void evaluator_mag(int v_s)\n        {\n");
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
	text.append("        }\n");
}


void Gen_code::generate_methods()
{
	std::ofstream file_output(full_path.c_str(),ofstream::app);

	string methods_t;

	generate_print(methods_t);

	generate_evaluator(methods_t);

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
	main_text.append("    eval_mag.evaluator_mag(0);\n");
	main_text.append("    eval_mag.evaluator_mag(1);\n");
	main_text.append("    eval_mag.evaluator_mag(2);\n");
	main_text.append("    eval_mag.evaluator_mag(3);\n");
	main_text.append("    eval_mag.evaluator_mag(4);\n");
	main_text.append("    eval_mag.evaluator_mag(5);\n");
	main_text.append("    eval_mag.evaluator_mag(6);\n");
	main_text.append("    eval_mag.evaluator_mag(7);\n");
	main_text.append("    eval_mag.evaluator_mag(8);\n");
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
		structs.append("\n{\n");
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


void Gen_code::generate_code(const Attr_grammar &attr_grammar, const vector<Visit_seq> & v_seq)
{
	generate_grammar_file(attr_grammar);
	generate_header_file();

	generate_externs(attr_grammar);
	generate_structs(attr_grammar);

	generate_header_class();
	generate_private();
	generate_public(v_seq);
	generate_methods();
	generate_footer();
	generate_main();
}

} /* end namespace */
