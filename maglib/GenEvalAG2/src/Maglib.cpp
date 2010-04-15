/**
  *  \file		Maglib.cpp
  *  \brief		Implementation of the library of evaluator's generator.
  *  \date		14/04/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <vector>
#include <string>

#include "../include/Parser/Parser_AG.h"
#include "../include/Builders/Builder_plans.h"
#include "../include/Builders/Builder_visit_sequences.h"
#include "../include/Builders/Builder_code.h"
#include "../include/Maglib.h"

namespace genevalmag
{

Maglib::Maglib()
{
}

Maglib::~Maglib()
{
}

int Maglib::gen_evaluator(const string path_input_file, const string path_folder_output,
							const string name_library, const vector<string> &headers) const
{
	string path_output(path_folder_output);
	if (path_output[path_output.size()-1] != '/')
	{
		path_output.append("/");
	}
	Parser_AG p_mag;
	if (p_mag.parse_grammar(path_input_file))
	{
		p_mag.save_grammar_file(path_output);

		Builder_plans b_plans;
		unsigned short res(b_plans.build_plans(p_mag.get_attr_grammar()));
		if (res == 0)
		{
			b_plans.save_all_graphs(p_mag.get_attr_grammar().get_rules(), path_output);

			b_plans.save_all_plans(p_mag.get_attr_grammar(), path_output);
			b_plans.save_all_plans_project(p_mag.get_attr_grammar(), path_output);

			Builder_visit_sequences b_visit_seq;
			if (b_visit_seq.generate_visit_sequences(p_mag.get_attr_grammar(), b_plans))
			{
				Gen_code gen(path_output, name_library);
				if(gen.generate_code(p_mag.get_attr_grammar(), b_plans, b_visit_seq.get_visit_seq(),headers))
				{
					return 0;
				}
			}
		}
		else if (res == 1)
		{
			b_plans.save_cyclic_graphs(p_mag.get_attr_grammar().get_rules(), path_output);
		}
	}
	return -1;
}

} /* end genevalmag */
