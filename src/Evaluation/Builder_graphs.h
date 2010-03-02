/**
  *  \file		Builder_graphs.h
  *  \brief		Header with the functions for evaluation of AG.
  *  \date		17/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef DC_GRAPH_H_
#define DC_GRAPH_H_

#include <map>
#include "../Attr_grammar/Rule.h"
#include "../Attr_grammar/Symbol.h"
#include "../Attr_grammar/Attr_grammar.h"

using namespace genevalmag;

void compute_dependency_graphs(const map<string, Rule> &rules);

//void compute_attr_vertex(const map<string,Symbol> &symbols);

void compute_down_graph(const map<string, Symbol> &symbols, const map<string, Rule> &rules);

void compute_dcg(const map<string, Rule> &rules);

void compute_adp_graph(const Attr_grammar &grammar);

void print_all_graphs(const map<string, Rule> &rules);

#endif /* DC_GRAPH_H_ */
