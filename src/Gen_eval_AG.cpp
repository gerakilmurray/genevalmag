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

#include "Attr_grammar/Attr_grammar.h"
#include "Parser/Parser_AG.h"
#include "Evaluation/Builder_plan.h"

namespace genevalmag
{

/**
  *	Path of the input file with the specification of AG.
  */
const string PATH_INPUT_FILE ("./src/Test/mag.txt");

/**
  * Constant that represent the maximum size of the file buffer.
  */
//const unsigned short  MAX_INPUT_FILE (32000);

/**
  * Constant that represent the maximum size of the line read.
  */
//const unsigned short MAX_INPUT_LINE (256);

}

using namespace std;
using namespace genevalmag;

/**
  * Reads the contents of the file and save it in the
  * string passed as parameter.
  */
//bool read_file_in(string &txt_output)
//{
//	FILE*	p_file;
//	char	buffer[MAX_INPUT_FILE];
//
//	p_file = fopen(PATH_INPUT_FILE.c_str(), "r");
//	if(p_file == NULL)
//	{
//		cerr << "ERROR: the file input non-exist." << endl;
//		return false;
//	}
//	else
//	{
//		while(!feof(p_file))
//		{
//			char * result = fgets(buffer, MAX_INPUT_LINE, p_file);
//			if (result)
//			{
//				txt_output += buffer;
//			}
//		}
//		fclose(p_file);
//	}
//	return true;
//}

/* retorna "a - b" en segundos */
double timeval_diff(struct timeval *a, struct timeval *b)
{
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}

/**
  * Main method of the parsing.
  */
int main()
{
	struct timeval t_ini, t_fin;
	double secs;

	gettimeofday(&t_ini, NULL);

//	string input_grammar;
//	if(read_file_in(input_grammar))
//	{
		Parser_AG p_mag;

//		if (p_mag.parse_grammar(input_grammar.c_str()))
		if (p_mag.parse_grammar(PATH_INPUT_FILE))
		{
			Builder_plan b_plans;
			b_plans.build_plans(p_mag.get_attr_grammar());
		}
//	}
	cout << "Bye... :-D" << endl;

	gettimeofday(&t_fin, NULL);

	secs = timeval_diff(&t_fin, &t_ini);
	printf("Generation complete in: %.6g seconds.\n", secs);
	return 0;
}
