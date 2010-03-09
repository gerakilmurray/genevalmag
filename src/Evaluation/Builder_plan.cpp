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

#include "../Util/Utilities.h"

using namespace std;
using namespace boost;
using namespace utilities;

namespace genevalmag
{

typedef pair < unsigned short, Order_eval> Order_rule;

typedef pair < bool, Order_rule > Item_work;

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

void Builder_plan::generates_topological_order(const Dp_graph &graph, Order_eval &t_order, const Rule &rule) const
{
	typedef Dp_graph::vertex_descriptor Vertex;

	typedef std::list<Vertex> MakeOrder;
	MakeOrder make_order;

	topological_sort(graph, std::front_inserter(make_order));

	property_map<Dp_graph, vertex_data_t>::const_type prop(get(vertex_data_t(), graph));

	for (MakeOrder::iterator i = make_order.begin(); i != make_order.end(); ++i)
	{
		// Al usar DCG sabemos que no hay nodos literales.
		t_order.push_back(rule.get_index_eq((Ast_instance*)prop[*i]));
	}
}

Order_eval Builder_plan::compute_order(const Dp_graph &graph_adp, const Order_eval &order, const Rule &rule)
{
	Dp_graph graph = graph_adp;

	Order_eval result;

	for (size_t i(1); i< order.size(); i++)
	{
		property_map<Dp_graph, vertex_data_t>::type prop(get(vertex_data_t(), graph));

		Dp_graph::vertex_descriptor v1(return_vertex(graph, rule.get_eq(order[i-1])->get_l_value()));
		assert(v1 != USHRT_MAX);
		Dp_graph::vertex_descriptor v2(return_vertex(graph, rule.get_eq(order[i])->get_l_value()));
		assert(v2 != USHRT_MAX);

		add_edge(v1, v2, graph);
	}

	generates_topological_order(graph, result, rule);

	return result;
}

/**
  * Generates and saves all evaluation's plans for the Attribute Grammar.
  */
void Builder_plan::generate_plans(const Attr_grammar &grammar, const Builder_graphs &build_graphs)
{
	vector<Item_work > work_list;

	vector<unsigned short> initial_rules(grammar.get_rules_with_left_symbol(grammar.get_initial_symb()));

	for(size_t i(0); i < initial_rules.size(); i++)
	{
		Order_eval random_order;
		const Rule &rule = grammar.get_rule(initial_rules[i]);
		generates_topological_order(build_graphs.get_dcg_graph(initial_rules[i]),random_order,rule);
		Order_rule o_eval(initial_rules[i], random_order);
		Item_work new_p(false,o_eval);
		work_list.push_back(new_p);
	}

	Item_work i_work;
	while(work_list.size() > 0)
	{
		i_work = work_list.back();
		const Rule &rule = grammar.get_rule(i_work.second.first);
		work_list.pop_back();
		if (!i_work.first)
		// A(q,w) is not marked;
		{
			i_work.first = true;

			const map<vector<unsigned short>,Dp_graph> &adp_graph(build_graphs.get_adp_graphs());

			for(map<vector<unsigned short>,Dp_graph >::const_iterator adp(adp_graph.begin()); adp != adp_graph.end(); adp++)
			{
				if (adp->first[0] == i_work.second.first)
				{
					Order_eval total_order(compute_order(adp->second,i_work.second.second,rule));
				}
			}
		}
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
