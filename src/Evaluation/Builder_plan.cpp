/**
  *  \file		Builder_plan.cpp
  *  \brief		Implementation of the methods the Builder_plan.h
  *  \date		18/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>

#include <boost/graph/topological_sort.hpp>
#include <boost/graph/transitive_closure.hpp>

#include "Builder_plan.h"

#include "../Util/Utilities.h"

using namespace std;
using namespace boost;
using namespace utilities;

namespace genevalmag
{

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

void Builder_plan::generates_topological_order(const Dp_graph &graph, Order_eval_eq &result_order, const Attr_grammar &grammar, const Context_rule &context_rule) const
{
	typedef Dp_graph::vertex_descriptor Vertex;

	typedef std::list<Vertex> MakeOrder;
	MakeOrder make_order;

	topological_sort(graph, std::front_inserter(make_order));

	property_map<Dp_graph, vertex_data_t>::const_type prop(get(vertex_data_t(), graph));

	for (MakeOrder::iterator i(make_order.begin()); i != make_order.end(); ++i)
	{
		const Ast_instance* ins(dynamic_cast<const Ast_instance*>(prop[*i]));
		if (ins)
		{
			unsigned short index;
			if (ins->get_attr()->is_inherit() && ins->get_symb()->equals(*grammar.get_rule(context_rule.context[0]).get_left_symbol()))
			{
				vector<unsigned short> context_father;
				context_father.push_back(context_rule.father);
				index = (grammar.get_index_eq_with_context(ins, context_father));
			}
			else
			{
				index = (grammar.get_index_eq_with_context(ins, context_rule.context));
			}
			assert (index > 0);
			result_order.push_back(index);
		}
	}
}

Order_eval_eq Builder_plan::compute_order(const Dp_graph &graph_adp, const Order_eval_eq &order_eq, const Attr_grammar &grammar, const Context_rule &context_rule)
{
	Dp_graph graph(graph_adp);
	for (size_t i(1); i < order_eq.size(); i++)
	{
		property_map<Dp_graph, vertex_data_t>::type prop(get(vertex_data_t(), graph));

		const Ast_instance *ins1(grammar.get_eq_l_value(order_eq[i-1]));
		assert(ins1 != NULL);
		Dp_graph::vertex_descriptor v1(return_vertex(graph, ins1));
		assert(v1 != USHRT_MAX);
		const Ast_instance *ins2 = grammar.get_eq_l_value(order_eq[i]);
		assert(ins2 != NULL);
		Dp_graph::vertex_descriptor v2(return_vertex(graph, ins2));
		assert(v2 != USHRT_MAX);

		add_edge(v1, v2, graph);
	}

	warshall_transitive_closure(graph);

	Order_eval_eq result;
	generates_topological_order(graph, result, grammar, context_rule);

	return result;
}

void Builder_plan::print_all_plans(const Attr_grammar &grammar) const
{
	for(map < Key_plan, Order_eval_eq >::const_iterator it(eval_plans.begin()); it != eval_plans.end(); it++)
	{
		Dp_graph graph_plan;
		string names[it->second.size()];
		Dp_graph::vertex_descriptor ant = 0;

		for(size_t i(0); i<it->second.size(); i++)
		{
			Dp_graph::vertex_descriptor current = add_vertex(graph_plan);
			if (i>0)
			{
				add_edge(ant,current,graph_plan);
			}
			ant = current;
			const Equation *eq = grammar.get_eq(it->second[i]);
			names[i] = cleaning_tabs(eq->to_string());
		}

		string name_graph("Evaluation Plan of rule ");
		const Rule *rule(&(grammar.get_rules().find(it->first.id_plan.context[0])->second));
		name_graph.append(cleaning_tabs(rule->to_string_not_eqs()));

		name_graph.append(write_inf_context(it->first.id_plan.context));

		name_graph.append(", order: ");
		for(size_t i(0); i < it->first.plan.size(); i++)
		{
			name_graph.append(" Eq");
			stringstream key_eq;
			key_eq << it->first.plan[i];
			name_graph.append(key_eq.str());
			if(i < it->first.plan.size() - 1)
			{
				name_graph.append(" ,");
			}
		}
		if (it->first.id_plan.father == 0)
		{
			name_graph.append(" without a father");
		}
		else
		{
			name_graph.append(" and father: R");
			stringstream father;
			father << it->first.id_plan.father;
			name_graph.append(father.str());
		}
		name_graph.append(".");

		print_graph(graph_plan,"_plan_graph", name_graph, names,"box");
	}
}

void Builder_plan::print_all_plans_project(const Attr_grammar &grammar) const
{
	for(map < Key_plan_project, Order_eval_eq >::const_iterator it(plans_project.begin()); it != plans_project.end(); it++)
	{
		Dp_graph graph_plan;
		string names[it->second.size()];
		Dp_graph::vertex_descriptor ant = 0;

		for(size_t i(0); i<it->second.size(); i++)
		{
			Dp_graph::vertex_descriptor current = add_vertex(graph_plan);
			if (i>0)
			{
				add_edge(ant,current,graph_plan);
			}
			ant = current;
			const Equation *eq = grammar.get_eq(it->second[i]);
			names[i] = cleaning_tabs(eq->to_string());
		}

		string name_graph("Evaluation Plan Project of rule ");
		const Rule *rule(&(grammar.get_rules().find(it->first.id_plan_project.id_plan.context[0])->second));
		name_graph.append(cleaning_tabs(rule->to_string_not_eqs()));

		name_graph.append(write_inf_context(it->first.id_plan_project.id_plan.context));

		name_graph.append(", order: ");
		for(size_t i(0); i < it->first.id_plan_project.plan.size(); i++)
		{
			name_graph.append(" Eq");
			stringstream key_eq;
			key_eq << it->first.id_plan_project.plan[i];
			name_graph.append(key_eq.str());
			if(i < it->first.id_plan_project.plan.size() - 1)
			{
				name_graph.append(" ,");
			}
		}
		if (it->first.id_plan_project.id_plan.father == 0)
		{
			name_graph.append(", without a father");
		}
		else
		{
			name_graph.append(", father: R");
			stringstream father;
			father << it->first.id_plan_project.id_plan.father;
			name_graph.append(father.str());
		}
		name_graph.append(" and Symbol: ");
		name_graph.append(it->first.symbol_project->get_name());
		name_graph.append(".");

		print_graph(graph_plan,"_plan_project_graph", name_graph, names,"box");
	}
}

void project_order(const Symbol *symb, const Attr_grammar &grammar, const Order_eval_eq &total_order, Order_eval_eq &p_order)
{
	for(size_t i(0); i < total_order.size(); i++)
	{
		const Ast_instance *ins(grammar.get_eq_l_value(total_order[i]));
		if (symb->equals(*ins->get_symb()))
		{
			p_order.push_back(total_order[i]);
		}
	}
}

/**
  * Generates and saves all evaluation's plans for the Attribute Grammar.
  */
void Builder_plan::generate_plans(const Attr_grammar &grammar, const Builder_graphs &build_graphs)
{
	vector < Item_work > work_list;

	map < Item_work, bool > defined_item_work;

	vector< unsigned short > initial_rules(grammar.get_rules_with_left_symbol(grammar.get_initial_symb()));

	for(size_t i(0); i < initial_rules.size(); i++)
	{
		Order_eval_eq init_order;
		Context_rule context;
		context.father = 0; // rule ficticia; regla inicial no tiene padre.
		vector < unsigned short > invoque_context;
		invoque_context.push_back(initial_rules[i]);
		context.context = invoque_context;
		generates_topological_order(build_graphs.get_dcg_graph(initial_rules[i]), init_order, grammar, context);

		Key_work_list key;
		key.father = 0;//rule ficticia; regla inicial no tiene padre
		key.id_rule = initial_rules[i];
		Item_work i_eval;
		i_eval.item = key;
		i_eval.order_attr = init_order;
		work_list.push_back(i_eval);
	}

	const map<vector<unsigned short>,Dp_graph> &adp_graph(build_graphs.get_adp_graphs());

	while(work_list.size() > 0)
	{
		Item_work i_work(work_list.back());
		work_list.pop_back();

		if (defined_item_work.find(i_work) == defined_item_work.end())
		// A(q,w) is not marked;
		{
			pair< Item_work, bool > new_item(i_work, true);
			defined_item_work.insert(new_item);

			for(map<vector<unsigned short>,Dp_graph >::const_iterator adp(adp_graph.begin()); adp != adp_graph.end(); adp++)
			{
				if (adp->first[0] == i_work.item.id_rule)
				{
					Context_rule context;
					context.father = i_work.item.father;
					context.context = adp->first;

					Order_eval_eq total_order(compute_order(adp->second, i_work.order_attr, grammar, context));

					Key_plan key_plan;
					key_plan.id_plan = context;
					key_plan.plan = i_work.order_attr;
					pair < Key_plan, Order_eval_eq > new_p(key_plan, total_order);
					eval_plans.insert(new_p);

					const Rule& rule(grammar.get_rule(adp->first[0]));
					vector<const Symbol*> right_side(rule.get_non_terminals_right_side());

					for(size_t i(0); i < right_side.size(); i++)
					{
						Order_eval_eq proj_order;

						project_order(right_side[i], grammar, total_order, proj_order);

						Key_plan_project key_project;
						key_project.id_plan_project = key_plan;
						key_project.symbol_project = right_side[i];
						pair < Key_plan_project, Order_eval_eq > new_p(key_project, proj_order);
						plans_project.insert(new_p);

						Key_work_list key;
						key.father = adp->first[0];
						// adp->firts[i+1] es el key de la regla para el i-esimo non-termials.
						key.id_rule = adp->first[i+1];
						Item_work o_rule;
						o_rule.item = key;
						o_rule.order_attr = proj_order;
						if (defined_item_work.find(o_rule)->second)
						{
							work_list.push_back(o_rule);
						}
					}
				}
			}
		}
	}

	clean_output_folder();
	build_graphs.print_adp_graphs(grammar.get_rules());
	print_all_plans(grammar);
//	print_all_plans_project(grammar);
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
