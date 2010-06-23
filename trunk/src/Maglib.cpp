/**
  *  \file		Maglib.cpp
  *  \brief		Implementation of the library of evaluator's generator.
  *  \date		14/04/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <vector>
#include <iostream>
#include <string>

#include "../include/Parser/Parser_AG.h"
#include "../include/Builders/Builder_plans.h"
#include "../include/Builders/Builder_visit_sequences.h"
#include "../include/Builders/Builder_code.h"
#include "../include/Util/Utilities.h"
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
	const vector<string> &headers,
	const string path
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
		/* Erase and create the output folder */
		if(!utilities::clean_output_folder(path_output))
		{
			cerr << "ERROR: the path " << path_output << " is invalid or inaccessible." << endl;
			return -1;
		}

		/* Parsing success and is a MAG. Proceed to save. */
		p_mag.save_grammar_file(path_output);

		/* Start the plan's generation. */
		Builder_plans b_plans(p_mag.get_attr_grammar());
		unsigned short res(b_plans.build_plans());
		if (res == 0)
		{
			/* Success, proceed to save all graphs generated. */
			b_plans.save_all_graphs(path_output);
			/* And saves all plans generated too. */
			b_plans.save_all_plans(path_output);
			b_plans.save_all_plans_project(path_output);

			/* Begins the visit sequence computation. */
			Builder_visit_sequences b_visit_seq(b_plans, p_mag.get_attr_grammar());
			if (b_visit_seq.generate_visit_sequences())
			{
				/* Success, the last step is code generation. */
				Builder_code b_gen(path_output, name_library, p_mag.get_attr_grammar(), b_plans, b_visit_seq);
				if(b_gen.generate_code(headers, path))
				{
					/* Success, the evaluator is completed. */
					return 0;
				}
			}
		}
		else if (res == 1)
		{
			/* The graphs generation exits because detects a cyclic graphs of attribute dependencies. */
			b_plans.save_cyclic_graphs(path_output);
			cerr << "ERROR: One o more graph ADP has an cycle in its dependencies. Look the folder " << path_output
			<< "graphs/CYCLIC_graphs/ for more details." << endl;
		}
	}
	/* In this point some step fails. */
	return -1;
}

} /* end genevalmag */
