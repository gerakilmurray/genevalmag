/**
  *  \file		Gen_eval_AG.cpp
  *  \brief		Main module.
  *  \date		09/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <stdio.h>
#include <iostream>
#include <string>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>

#include "Attr_grammar/Attr_grammar.h"
#include "Util/Utilities.h"
#include "Parser/Parser_AG.h"
#include "Evaluation/Builder_plans.h"
#include "Evaluation/Builder_visit_sequences.h"
#include "Generator/Gen_code.h"

const string DEFAULT_PATH("./GenEvalAG/");
const string DEFAULT_FILE_NAME("Eval_mag");

namespace genevalmag
{

/**
  *	Path of the input file with the specification of AG.
  */
//const string PATH_INPUT_FILE ("./src/Test/mag.txt");

}

using namespace std;
using namespace genevalmag;
using namespace utilities;

/* retorna "a - b" en segundos */
double timeval_diff(struct timeval *a, struct timeval *b)
{
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}

bool check_option(const char *strFilename)
{
	struct stat stFileInfo;
	int intStat(stat(strFilename,&stFileInfo));
	return (intStat == 0);
}

bool check_name(const char *strFilename)
{
	if (strFilename[0] != '-' && strFilename[0] != '/')
	{
		return true;
	}
	return false;
}


void out_error_information()
{
	string err_use("ERROR: Genevalag wrong uses.\n Uses:\n");
	err_use.append("		GenevalMag  [OPTION] -f <input_file>\n");
	err_use.append("		 	where [OPTION]:\n");
	err_use.append("				-i 	Including header 'h' or 'hpp' file for resolve externs variables in generated code.\n");
	err_use.append("			 	-fo Define the folder output for output generated information.\n");
	err_use.append("				-o	Define the names files generated library.\n");
	cerr << err_use << endl;
	exit(-1);
}

/**
  *	GenevalMag  [OPTION] -f <input_file>
  *	where [OPTION]:
  *		-i 	Including header "h" or "hpp" file for resolve externs variables in generated code.
  *		-fo Define the folder output for output generated information.
  *		-o	Define the names files generated library.
  */


/**
  * Main method of the parsing.
  */
int main
(
	int argc,      // Number of strings in array argv
	char *argv[],  // Array of command-line argument strings
	char *envp[]   // Array of environment variable string
)
{
	struct timeval t_ini, t_fin;
	double secs;

	gettimeofday(&t_ini, NULL);

	if(argc == 1)
	{
		out_error_information();
	}

	string path_input_file;
	string path_folder_output(DEFAULT_PATH);
	vector<string> headers;
	string name_library(DEFAULT_FILE_NAME);

	bool file_input(false);
	int i(1);
	while (i < argc)
	{
		if (argc > i + 1)
		{
			string arg_i (argv[i]);
			i++;
			if (arg_i.compare("-f") == 0)
			{
				file_input = true;
				if(check_option(argv[i]))
					path_input_file = argv[i++];
				else
					out_error_information();
				continue;
			}
			if (arg_i.compare("-fo") == 0)
			{
				path_folder_output = argv[i++];
			}
			if (arg_i.compare("-o") == 0)
			{
				if (check_name(argv[i]))
					name_library = argv[i++];
				else
					out_error_information();
				continue;
			}
			if (arg_i.compare("-i") == 0)
			{
				if (check_option(argv[i]))
					headers.push_back(argv[i++]);
				else
					out_error_information();
				continue;
			}
		}

	}

	if (!(clean_output_folder(path_folder_output)))
	{
		out_error_information();
	}

	if (!file_input)
	{
		out_error_information();
	}

	Parser_AG p_mag;

	if (p_mag.parse_grammar(path_input_file))
	{
		Builder_plans b_plans(path_folder_output);
		if (b_plans.build_plans(p_mag.get_attr_grammar()))
		{
			Builder_visit_sequences b_visit_seq;
			if (b_visit_seq.generate_visit_sequences(p_mag.get_attr_grammar(),b_plans))
			{
				Gen_code gen(path_folder_output,name_library );
				gen.generate_code(p_mag.get_attr_grammar(), b_plans, b_visit_seq.get_visit_seq());
			}

		}
	}
	cout << "Bye... :-D" << endl;

	gettimeofday(&t_fin, NULL);

	secs = timeval_diff(&t_fin, &t_ini);
	printf("Generation complete in: %.6g seconds.\n", secs);
	return 0;
}
