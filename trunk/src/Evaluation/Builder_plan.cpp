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

/**
  * Applies a topological order at graph.
  * The changes are applies about paramenter "result_order".
  */
void Builder_plan::generates_topological_order(const Dp_graph &graph, Order_eval_eq &result_order, const Attr_grammar &grammar, const Context_rule &context_rule) const
{
	typedef std::list<Vertex> MakeOrder;
	MakeOrder make_order;

	/* Function of library boost. Topological order.  */
	topological_sort(graph, std::front_inserter(make_order));

	/* Creates result_order with "make_order" */

	property_map<Dp_graph, vertex_data_t>::const_type prop(get(vertex_data_t(), graph));

	/* Cycle over make_oder for save the id_equation in result_order. */
	for (MakeOrder::iterator i(make_order.begin()); i != make_order.end(); ++i)
	{
		const Ast_instance* ins(dynamic_cast<const Ast_instance*>(prop[*i]));
		if (ins)
		/* For the equation's order only interests the instances. */
		{
			unsigned short index;
			if (ins->get_attr()->is_inherit() && ins->get_symb()->equals(*grammar.get_rule(context_rule.context[0]).get_left_symbol()))
			/* The instance is a inherit of left-symbol rule.
			 * The instance searchs in the superior context of rule. */
			{
				vector<unsigned short> context_father;
				context_father.push_back(context_rule.father);
				index = (grammar.get_index_eq_with_context(ins, context_father));
			}
			else
			/* The instance is a inherit of right-symbol rule or syntetize of left-symbol.
			 *  The instance searchs in the context of rule. */
			{
				index = (grammar.get_index_eq_with_context(ins, context_rule.context));
			}
			assert (index > 0);
			result_order.push_back(index);
		}
	}
}

/**
  * Compute the rule's order.
  * The changes are applies about paramenter "result_order".
  */
Order_eval_eq Builder_plan::compute_order(const Dp_graph &graph_adp, const Order_eval_eq &order_eq, const Attr_grammar &grammar, const Context_rule &context_rule)
{
	Dp_graph graph(graph_adp);
	/* Creates edges with the elem of order_eq
	 * Ex: Order_eq = 2, 5, 6.
	 *  Edges : (2,5), (5,6) */
	for (size_t i(1); i < order_eq.size(); i++)
	{
		property_map<Dp_graph, vertex_data_t>::type prop(get(vertex_data_t(), graph));
		/* Obtain v1 */
		const Ast_instance *ins1(grammar.get_eq_l_value(order_eq[i-1]));
		assert(ins1 != NULL);
		Vertex v1(return_vertex(graph, ins1));
		assert(v1 != USHRT_MAX);

		/* Obtain v2 */
		const Ast_instance *ins2(grammar.get_eq_l_value(order_eq[i]));
		assert(ins2 != NULL);
		Vertex v2(return_vertex(graph, ins2));
		assert(v2 != USHRT_MAX);

		add_edge(v1, v2, graph);
	}
	/* Applies transitive function over graph. */
	warshall_transitive_closure(graph);

	Order_eval_eq result;
	/* Applies topological order over graph. */
	generates_topological_order(graph, result, grammar, context_rule);

	return result;
}

/**
  * Prints all plans. Creates a graph that represents the plan and uses print_graph with dot.
  */
void Builder_plan::print_all_plans(const Attr_grammar &grammar) const
{
	for(map < Key_plan, Order_eval_eq >::const_iterator it(eval_plans.begin()); it != eval_plans.end(); it++)
	{
		Dp_graph graph_plan;
		string names[it->second.size()];
		Vertex ant(0);
		/* creates graph. */
		for(size_t i(0); i<it->second.size(); i++)
		{
			Vertex current(add_vertex(graph_plan));
			if (i>0)
			{
				add_edge(ant,current,graph_plan);
			}
			ant = current;
			const Equation *eq(grammar.get_eq(it->second[i]));
			names[i] = cleaning_tabs(eq->to_string());
		}
		/* Obtains the rule. */
		string name_graph("Evaluation Plan of rule ");
		const Rule *rule(&(grammar.get_rules().find(it->first.id_plan.context[0])->second));
		name_graph.append(cleaning_tabs(rule->to_string_not_eqs()));

		name_graph.append(write_inf_context(it->first.id_plan.context));

		/* Obtains the rule's context. */
		if (it->first.plan.size() == 0)
		{
			name_graph.append(", without Order.Sup");
		}
		else
		{
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
		}

		/* Obtains the rule's superior context. */
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

/**
  * Prints all proyected's plans. Creates a graph that represents the plan and uses print_graph with dot.
  */
void Builder_plan::print_all_plans_project(const Attr_grammar &grammar) const
{
	for(map < Key_plan_project, Order_eval_eq >::const_iterator it(plans_project.begin()); it != plans_project.end(); it++)
	{
		Dp_graph graph_plan;
		string names[it->second.size()];
		Vertex ant(0);
		/* creates graph. */
		for(size_t i(0); i<it->second.size(); i++)
		{
			Vertex current(add_vertex(graph_plan));
			if (i>0)
			{
				add_edge(ant,current,graph_plan);
			}
			ant = current;
			const Equation *eq(grammar.get_eq(it->second[i]));
			names[i] = cleaning_tabs(eq->to_string());
		}

		/* Obtains the rule. */
		string name_graph("Evaluation Plan Project of rule ");
		const Rule *rule(&(grammar.get_rules().find(it->first.id_plan_project.id_plan.context[0])->second));
		name_graph.append(cleaning_tabs(rule->to_string_not_eqs()));

		name_graph.append(write_inf_context(it->first.id_plan_project.id_plan.context));

		/* Obtains the rule's context. */
		if (it->first.id_plan_project.plan.size() == 0)
		{
			name_graph.append(", without Order.Sup");
		}
		else
		{
			name_graph.append(", Order.Sup: ");
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
		}

		/* Obtains the rule's superior context. */
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

		/* Obtains the symbol projected. */
		name_graph.append(" and Symbol: ");
		name_graph.append(it->first.symbol_project->get_name());
		name_graph.append(".");

		print_graph(graph_plan,"_plan_project_graph", name_graph, names,"box");
	}
}

/**
  * Projects a order over a symbol.
  */
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

void purge_plan_with(const Rule &rule, const Order_eval_eq &order_eq, Order_eval_eq &purged_order)
{
	for(size_t i(0); i < order_eq.size(); i++)
	{
		if(rule.get_eq(order_eq[i]) != NULL)
		{
			purged_order.push_back(order_eq[i]);
		}
	}
}

bool defined_work (const vector < Item_work > &list, const Item_work &item_work)
{
	for(size_t i(0); i < list.size(); i++)
	{
		if(item_work == list[i])
		{
			return true;
		}
	}
	return false;
}

/**
  * Generates and saves all evaluation's plans for the Attribute Grammar.
  */
void Builder_plan::generate_plans(const Attr_grammar &grammar, const Builder_graphs &build_graphs)
{
	vector < Item_work > work_list;

	vector < Item_work > defined_item_work;

	vector< unsigned short > initial_rules(grammar.get_rules_with_left_symbol(grammar.get_initial_symb()));

	/* Initializes the work list with the rules with the initial symbol grammar. */
	for(size_t i(0); i < initial_rules.size(); i++)
	{
		Order_eval_eq init_order;
		Context_rule context;
		context.father = 0; /* Initial rule hasn't father. */
		vector < unsigned short > invoque_context;
		invoque_context.push_back(initial_rules[i]);
		context.context = invoque_context;
		generates_topological_order(build_graphs.get_dcg_graph(initial_rules[i]), init_order, grammar, context);

		Key_work_list key;
		key.father = 0;/* Initial rule hasn't father. */
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

		if (!defined_work(defined_item_work, i_work))
		/* A(q,w) is not marked */
		{
			defined_item_work.push_back(i_work);

			for(map<vector<unsigned short>,Dp_graph >::const_iterator adp(adp_graph.begin()); adp != adp_graph.end(); adp++)
			{
				/* Current rule that defines the ADP. */
				const Rule& rule(grammar.get_rule(adp->first[0]));

				if (rule.key() == i_work.item.id_rule)
				/* The adp graph belong at rule of the item_work current. */
				{
					/* Creates the context rule with superior context and context of rule. */
					Context_rule context;
					context.father = i_work.item.father;
					context.context = adp->first;

					Order_eval_eq total_order(compute_order(adp->second, i_work.order_attr, grammar, context));

					Order_eval_eq order_purged;
					purge_plan_with(rule, total_order,order_purged);

					/* Saves the new_plan in the map. */
					Key_plan key_plan;
					key_plan.id_plan = context;
					key_plan.plan = i_work.order_attr;
					pair < Key_plan, Order_eval_eq > new_p(key_plan, order_purged);
					eval_plans.insert(new_p);

					vector<const Symbol*> right_side(rule.get_non_terminals_right_side());

					for(size_t i(0); i < right_side.size(); i++)
					{
						Order_eval_eq proj_order;

						const Rule& rule_proj(grammar.get_rule(adp->first[i+1]));
						purge_plan_with(rule_proj, total_order, proj_order);
						//project_order(right_side[i], grammar, order_purged, proj_order);

						/* Saves the new_plan_projected in the projected map. */
						Key_plan_project key_project;
						key_project.id_plan_project = key_plan;
						key_project.symbol_project = right_side[i];
						pair < Key_plan_project, Order_eval_eq > new_p(key_project, proj_order);
						plans_project.insert(new_p);

						/* Creates new plans for the work-list with the rule's right symbol.  */
						Key_work_list key;
						/* adp->firts[0] is the id-rule. */
						key.father = rule.key();
						/* adp->firts[i+1] is the id_rule of rule for the i-esimo non-termials.*/
						key.id_rule = adp->first[i+1];
						Item_work i_work_new;
						i_work_new.item = key;
						i_work_new.order_attr = proj_order;

						if (!defined_work(defined_item_work, i_work_new))
						{
							work_list.push_back(i_work_new);
						}
					}
				}
			}
		}
	}

	clean_output_folder();
//	build_graphs.print_all_graphs(grammar.get_rules());
//	build_graphs.print_adp_graphs(grammar.get_rules());
	print_all_plans(grammar);
//	print_all_plans_project(grammar);
}

bool Builder_plan::build_plans(const Attr_grammar &attr_grammar)
{
	Builder_graphs build_graphs;
	generate_graphs(attr_grammar, build_graphs);

	if (build_graphs.check_cyclic_adp_dependencies())
	{
		cerr << "ERROR: One o more graph ADP has an cycle in its dependencies. Look the folder /out_graph for more details." << endl;
		build_graphs.print_graphs_cyclic(attr_grammar.get_rules());
		return false;
	}
	else
	{
		generate_plans(attr_grammar, build_graphs);
		return true;
	}
}

const map < Key_plan, Order_eval_eq > &Builder_plan::get_plans() const
{
	return eval_plans;
}

} /* end genevalmag */
