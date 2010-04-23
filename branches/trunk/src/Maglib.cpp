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

/**
  * Contructor empty of Mag_lib.
  */
Maglib::Maglib()
{
}

/**
  * Destructor empty of Mag_lib.
  */
Maglib::~Maglib()
{
}

/**
  * Generates the static evaluator's files for the Attribute grammar specificated in the
  * input_path_file passed as parameter.
  * All outputs of the library be saved in the path_folder_output.
  * The evaluator classname is defined by name_library.
  * The user could include somes headers for uses externs functions to evaluator.
  */
int Maglib::gen_evaluator
(
	const string path_input_file,
	const string path_folder_output,
	const string name_library,
	const vector<string> &headers
) const
{
	string path_output(path_folder_output);
	/* Ensure that the output path finish at '/'. */
	if (path_output[path_output.size()-1] != '/')
	{
		path_output.append("/");
	}

	/* Parses the input file to get the AG. */
	Parser_AG p_mag;
	if (p_mag.parse_grammar(path_input_file))
	{
		/* Parsing success and is a MAG. Proceed to save. */
		p_mag.save_grammar_file(path_output);

		/* Start the plan's generation. */
		Builder_plans b_plans;
		unsigned short res(b_plans.build_plans(p_mag.get_attr_grammar()));
		if (res == 0)
		{
			/* Success, proceed to save all graphs generated. */
			b_plans.save_all_graphs(p_mag.get_attr_grammar().get_rules(), path_output);

			/* And saves all plans generated too. */
			b_plans.save_all_plans(p_mag.get_attr_grammar(), path_output);
			b_plans.save_all_plans_project(p_mag.get_attr_grammar(), path_output);

			/* Begins the visit sequence computation. */
			Builder_visit_sequences b_visit_seq;
			if (b_visit_seq.generate_visit_sequences(p_mag.get_attr_grammar(), b_plans))
			{
				/* Success, the last step is code generation. */
				Builder_code b_gen(path_output, name_library);
				if(b_gen.generate_code(p_mag.get_attr_grammar(), b_plans, b_visit_seq.get_visit_seq(),headers))
				{
					/* Success, the evaluator is completed. */
					return 0;
				}
			}
		}
		else if (res == 1)
		{
			/* The graphs generation exits because detects a cyclic graphs of attribute dependencies. */
			b_plans.save_cyclic_graphs(p_mag.get_attr_grammar().get_rules(), path_output);
		}
	}
	/* In this point some step fails. */
	return -1;
}

} /* end genevalmag */
