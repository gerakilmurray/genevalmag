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
#include "Evaluation/Builder_plans.h"
#include "Evaluation/Builder_visit_sequences.h"
#include "Generator/Gen_code.h"

namespace genevalmag
{

/**
  *	Path of the input file with the specification of AG.
  */
const string PATH_INPUT_FILE ("./src/Test/count.txt");

}

using namespace std;
using namespace genevalmag;

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
	Parser_AG p_mag;

	if (p_mag.parse_grammar(PATH_INPUT_FILE))
	{
		Builder_plans b_plans;
		if (b_plans.build_plans(p_mag.get_attr_grammar()))
		{
			Builder_visit_sequences b_visit_seq;
			if (b_visit_seq.generate_visit_sequences(p_mag.get_attr_grammar(),b_plans))
			{
				Gen_code gen;
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
