/**
  *  \file		Builder_plan.cpp
  *  \brief		Implementation of the methods the Builder_plan.h
  *  \date		18/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include "Builder_plan.h"
#include "Builder_graphs.h"
#include <iostream>

namespace genevalmag
{

Builder_plan::Builder_plan(){}
Builder_plan::~Builder_plan(){}


void Builder_plan::build_plans(const Attr_grammar &attr_grammar)
{
	Builder_graphs b_graphs;

	b_graphs.compute_dependency_graphs(attr_grammar.get_rules());
	cout << "DP" << endl;
	b_graphs.compute_down_graph(attr_grammar.get_non_terminal_symbols(), attr_grammar.get_rules());
	cout << "Down" << endl;
	b_graphs.compute_dcg(attr_grammar.get_rules());
	cout << "DCG" << endl;
	b_graphs.compute_adp_graph(attr_grammar);
	cout << "ADP" << endl;
	b_graphs.print_all_graphs(attr_grammar.get_rules());
	cout << "PRINT" << endl;
}
} // end genevalmag
