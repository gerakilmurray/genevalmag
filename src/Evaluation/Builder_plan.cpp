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

void build_plans(const Attr_grammar &attr_grammar)
{
	compute_dependency_graphs(attr_grammar.get_rules());
	cout << "DP" << endl;
//	compute_attr_vertex(attr_grammar.get_non_terminal_symbols());
//	cout << "ATTR_VERTEX" << endl;
	compute_down_graph(attr_grammar.get_non_terminal_symbols(), attr_grammar.get_rules());
	cout << "Down" << endl;
	compute_dcg(attr_grammar.get_rules());
	cout << "DCG" << endl;
	compute_adp_graph(attr_grammar);
	cout << "ADP" << endl;
	print_all_graphs(attr_grammar.get_rules());
	cout << "PRINT" << endl;
}
