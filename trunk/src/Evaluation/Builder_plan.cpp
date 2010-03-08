/**
  *  \file		Builder_plan.cpp
  *  \brief		Implementation of the methods the Builder_plan.h
  *  \date		18/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>

#include <boost/graph/topological_sort.hpp>

#include "Builder_plan.h"
#include "../Parser/Semantics_actions.h"

using namespace std;
using namespace boost;

namespace genevalmag
{

typedef vector<const Ast_instance*> Order_eval;

/**
  * Constructor empty of Builder plan.
  */
Builder_plan::Builder_plan()
{
}

/**
  * Destructor of Builder plan.
  */
Builder_plan::~Builder_plan()
{
}

/**
  * Generates all graphs for attribute grammar: DP, DOWN, DCG and ADP.
  */
void generate_graphs(const Attr_grammar &grammar, Builder_graphs &b_graphs)
{
	b_graphs.compute_dependency_graphs(grammar.get_rules());

	b_graphs.compute_down_graph(grammar.get_non_terminal_symbols(), grammar.get_rules());

	b_graphs.compute_dcg(grammar.get_rules());

	b_graphs.compute_adp_graph(grammar);
}

void generates_topological_order(const Dp_graph &graph, Order_eval &t_order)
{
	typedef Dp_graph::vertex_descriptor Vertex;

	typedef std::list<Vertex> MakeOrder;
	MakeOrder make_order;

	topological_sort(graph, std::front_inserter(make_order));

	std::cout << "make ordering: ";
	property_map<Dp_graph, vertex_data_t>::const_type prop(get(vertex_data_t(), graph));
	for (MakeOrder::iterator i = make_order.begin(); i != make_order.end(); ++i)
	{
		std::cout << prop[*i]->to_string() << " ";
	}
	std::cout << std::endl;
}

/**
  * Generates and saves all evaluation's plans for the Attribute Grammar.
  */
void generate_plans(const Attr_grammar &grammar, const Builder_graphs &build_graphs)
{
	vector<pair < unsigned short, Order_eval> > work_list;

	vector<unsigned short> initial_rules(grammar.get_rules_with_left_symbol(grammar.get_initial_symb()));

	Order_eval random_order;

	generates_topological_order(build_graphs.get_down_graph(grammar.get_initial_symb()),random_order);

	for(size_t i(0); i < initial_rules.size(); i++)
	{
		pair<unsigned short, Order_eval> new_p(initial_rules[i], random_order);
		work_list.push_back(new_p);
	}

	build_graphs.print_all_graphs(grammar.get_rules());
	cout << "PLANES GERERADOR EXITOSAMENTE" << endl;
}

void Builder_plan::build_plans(const Attr_grammar &attr_grammar)
{
	Builder_graphs build_graphs;
	generate_graphs(attr_grammar, build_graphs);

	if (build_graphs.check_cyclic_adp_dependencies())
	{
		cerr << "ERROR: One o more graph ADP has an cycle in its dependencies. Look the folder /out_graph for more details." << endl;
		build_graphs.print_graphs_cyclic(attr_grammar.get_rules());
	}
	else
	{
		generate_plans(attr_grammar, build_graphs);
	}
}

} /* end genevalmag */
