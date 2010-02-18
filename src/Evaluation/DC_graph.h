/**
  *  \file		DC_graph.h
  *  \brief		Header with the functions for evaluation of AG.
  *  \date		17/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef DC_GRAPH_H_
#define DC_GRAPH_H_

#include <map>
#include "../Attr_grammar/Rule.h"

using namespace genevalmag;

void compute_dependency_graphs(const map<string, Rule> rules);

#endif /* DC_GRAPH_H_ */
