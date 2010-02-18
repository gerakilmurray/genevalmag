/**
  *  \file		Builder_plan.cpp
  *  \brief		Implementation of the methods the Builder_plan.h
  *  \date		18/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include "Builder_plan.h"
#include "DC_graph.h"

void build_plans(const Attr_grammar &attr_grammar)
{
	compute_dependency_graphs(attr_grammar.get_rules());
}
