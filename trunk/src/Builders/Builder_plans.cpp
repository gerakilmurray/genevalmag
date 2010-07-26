/**
  *  \file		Builder_plans.cpp
  *  \brief		Implementation of the methods the Builder_plans.h
  *  \date		18/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>
#include <limits.h>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/transitive_closure.hpp>

#include "../../include/Builders/Builder_plans.h"

#include "../../include/Util/Utilities.h"

using namespace std;
using namespace boost;
using namespace utilities;

namespace genevalmag
{

/**
  * Defaults path to saves evaluation plans y their projections.
  */
const string PATH_OUT_PLAN("plans/");
const string PATH_OUT_PLAN_PROJECT("plans_project/");

/**
  * Constructor empty of Builder plan.
  */
Builder_plans::Builder_plans(const Attr_grammar &attribute_grammar):
	attr_grammar(attribute_grammar),
	build_graphs(attribute_grammar)
{
}

/**
  * Destructor of Builder plan.
  */
Builder_plans::~Builder_plans()
{
}

/**
  * Saves all graphs generated as the analysis of the dependencies between attributes.
  */
void Builder_plans::save_all_graphs(const string path_output) const
{
	build_graphs.save_all_graphs(path_output);
}

/**
  * Saves the graphs generated as the analysis of the dependencies between attributes, which demonstrate cyclicity.
  */
void Builder_plans::save_cyclic_graphs(const string path_output) const
{
	build_graphs.save_cyclic_graphs(path_output);
}

/**
  * Generates all graphs for attribute grammar: DP, DOWN, DCG and ADP.
  */
bool Builder_plans::generate_graphs()
{
	if(build_graphs.compute_dependency_graphs())
	{
		if(build_graphs.compute_down_graph())
		{
			if(build_graphs.compute_dcg())
			{
				if(build_graphs.compute_adp_graph())
				{
					cout << "* Generation graphs -------- [  OK  ]" << endl;
					return true;
				}
			}
		}
	}
	cout << "* Generation graphs -------- [ FAIL ]\n" << endl;
	return false;
}

/**
  * Applies a topological order at graph.
  * The changes are applies about paramenter "result_order".
  */
void Builder_plans::generates_topological_order(const Graph &graph, Order_eval_eq &result_order, const Context_rule &context_rule) const
{
	typedef std::list<Vertex> MakeOrder;
	MakeOrder make_order;

	/* Function of library boost. Topological order.  */
	topological_sort(graph, std::front_inserter(make_order));

	/* Creates result_order with "make_order" */
	property_map<Graph, vertex_data_t>::const_type prop(get(vertex_data_t(), graph));

	/* Cycles over make_oder for save the id_equation in result_order. */
	for (MakeOrder::iterator i(make_order.begin()); i != make_order.end(); ++i)
	{
		const Expr_instance* ins(dynamic_cast<const Expr_instance*>(prop[*i]));
		if (ins)
		/* For the equation's order only interests the instances. */
		{
			unsigned short index;
			if (ins->get_attr()->is_inherit() && ins->get_symb()->equals(*attr_grammar.get_rule(context_rule.context[0]).get_left_symbol()))
			/* The instance is a inherit of left-symbol rule.
			 * The instance searchs in the superior context of rule. */
			{
				vector<unsigned short> context_father;
				context_father.push_back(context_rule.father);
				index = (attr_grammar.get_index_eq_with_context(ins, context_father));
			}
			else
			/* The instance is a inherit of right-symbol rule or syntetize of left-symbol.
			 * The instance searchs in the context of rule. */
			{
				index = (attr_grammar.get_index_eq_with_context(ins, context_rule.context));
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
Order_eval_eq Builder_plans::compute_order(const Graph &graph_adp, unsigned short index_order, const Context_rule &context_rule)
{
	Graph graph(graph_adp);
	const Order_eval_eq &order_eq(plans_project_uniques[index_order]);
	/* Creates edges with the elem of order_eq
	 * Ex: Order_eq = 2, 5, 6.
	 *  Edges : (2,5), (5,6) */
	for (size_t i(1); i < order_eq.size(); i++)
	{
		property_map<Graph, vertex_data_t>::type prop(get(vertex_data_t(), graph));
		/* Obtain v1 */
		const Expr_instance *ins1(attr_grammar.get_eq_l_value(order_eq[i-1]));
		assert(ins1 != NULL);
		Vertex v1(return_vertex(graph, ins1));
		assert(v1 != USHRT_MAX);

		/* Obtain v2 */
		const Expr_instance *ins2(attr_grammar.get_eq_l_value(order_eq[i]));
		assert(ins2 != NULL);
		Vertex v2(return_vertex(graph, ins2));
		assert(v2 != USHRT_MAX);

		add_edge(v1, v2, graph);
	}
	/* Applies transitive function over graph. */
//	warshall_transitive_closure(graph);

	Order_eval_eq result;
	/* Applies topological order over graph. */
	generates_topological_order(graph, result, context_rule);

	return result;
}

/**
  * Saves all plans. Creates a graph that represents the plan and uses print_graph with dot.
  */
bool Builder_plans::save_all_plans(const string path_output) const
{
	string path_out(path_output);
	path_out.append(PATH_OUT_PLAN);
	if(!clean_output_folder(path_out))
	{
		return false;
	}
	for(map < Key_plan, unsigned short >::const_iterator it(eval_plans.begin()); it != eval_plans.end(); it++)
	{
		Graph graph_plan;

		const Order_eval_eq &plan_o(plans_uniques[it->second]);

		string names[plan_o.size()];
		Vertex ant(0);
		/* Creates graph. */
		for(size_t i(0); i < plan_o.size(); i++)
		{
			Vertex current(add_vertex(graph_plan));
			if (i > 0)
			{
				add_edge(ant,current,graph_plan);
			}
			ant = current;
			const Equation *eq(attr_grammar.get_eq(plan_o[i]));
			names[i] = cleaning_tabs(eq->to_string());
		}
		/* Obtains the rule. */
		string name_graph("Evaluation Plan of rule ");

		const Order_rule &context_o(contexts_uniques[it->first.id_plan]);

		const Rule *rule(&(attr_grammar.get_rules().find(context_o[0])->second));

		name_graph.append(cleaning_tabs(rule->to_string_not_eqs()));

		name_graph.append(write_inf_context(context_o));

		const Order_eval_eq &plan_ctx(plans_project_uniques[it->first.plan]);

		/* Obtains the rule's context. */
		if (plan_ctx.size() == 0)
		{
			name_graph.append(", without Order.Sup");
		}
		else
		{
			name_graph.append(", order: ");
			for(size_t i(0); i < plan_ctx.size(); i++)
			{
				name_graph.append(" Eq");
				stringstream key_eq;
				key_eq << plan_ctx[i];
				name_graph.append(key_eq.str());
				if(i < plan_ctx.size() - 1)
				{
					name_graph.append(" ,");
				}
			}
		}
		name_graph.append(".");

		print_graph(graph_plan, path_out.c_str(), "_plan_graph", name_graph, names, "box");
	}
	return true;
}

/**
  * Saves all proyected's plans. Creates a graph that represents the plan and uses print_graph with dot.
  */
bool Builder_plans::save_all_plans_project(const string path_output) const
{
	string path_out(path_output);
	path_out.append(PATH_OUT_PLAN_PROJECT);
	if(!clean_output_folder(path_out))
	{
		return false;
	}

	for(map < Key_plan_project, unsigned short >::const_iterator it(plans_project.begin()); it != plans_project.end(); it++)
	{
		Graph graph_plan;

		const Order_eval_eq &plan_p_o(plans_project_uniques[it->second]);

		string names[plan_p_o.size()];
		Vertex ant(0);
		/* Creates graph. */
		for(size_t i(0); i < plan_p_o.size(); i++)
		{
			Vertex current(add_vertex(graph_plan));
			if (i > 0)
			{
				add_edge(ant,current,graph_plan);
			}
			ant = current;
			const Equation *eq(attr_grammar.get_eq(plan_p_o[i]));
			names[i] = cleaning_tabs(eq->to_string());
		}

		/* Obtains the rule. */
		string name_graph("Evaluation Plan Project of rule ");

		const Order_rule &context_o(contexts_uniques[it->first.id_plan_project.id_plan]);

		const Rule *rule(&(attr_grammar.get_rules().find(context_o[0])->second));
		name_graph.append(cleaning_tabs(rule->to_string_not_eqs()));

		name_graph.append(write_inf_context(context_o));

		const Order_eval_eq &plan_p_ctx(plans_project_uniques[it->first.id_plan_project.plan]);

		/* Obtains the rule's context. */
		if (plan_p_ctx.size() == 0)
		{
			name_graph.append(", without Order.Sup");
		}
		else
		{
			name_graph.append(", Order.Sup: ");
			for(size_t i(0); i < plan_p_ctx.size(); i++)
			{
				name_graph.append(" Eq");
				stringstream key_eq;
				key_eq << plan_p_ctx[i];
				name_graph.append(key_eq.str());
				if(i < plan_p_ctx.size() - 1)
				{
					name_graph.append(" ,");
				}
			}
		}
		/* Obtains the symbol projected. */
		name_graph.append(" and Symbol: ");
		name_graph.append(it->first.symbol_project->get_name());
		name_graph.append(" ");
		stringstream symb_ocurence;
		symb_ocurence << it->first.index_ocurrence;
		name_graph.append(symb_ocurence.str());
		name_graph.append(".");

		print_graph(graph_plan, path_out.c_str(), "_plan_project_graph", name_graph, names, "box");
	}
	return true;
}

/**
  * Copy in the result vector all equations belonging to the rule passed as parameter.
  */
void purge_plan_with(const Rule &rule, const Order_eval_eq &order_eq, Order_eval_eq &purged_order)
{
	for(size_t i(0); i < order_eq.size(); i++)
	{
		if(rule.get_eq(order_eq[i]) != NULL)
		{
			if (!belong_index(order_eq[i],purged_order))
			{
				purged_order.push_back(order_eq[i]);
			}
		}
	}
}

/**
  * Searchs in the list the item work that passed as parameter, if it find return true, otherwise false.
  */
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
  * Returns the index in the vector of context, or inserts in the last position.
  */
unsigned short Builder_plans::return_index_context(const Order_rule &order)
{
	unsigned short index(0);
	for(; index < contexts_uniques.size(); index++)
	{
		if(order == contexts_uniques[index])
		{
			return index;
		}
	}
	contexts_uniques.push_back(order);
	return index;
}

/**
  * Returns the index in the vector, or inserts in the last position.
  */
unsigned short return_index_vec(const Order_eval_eq &order, vector<Order_eval_eq> &vec)
{
	unsigned short index(0);
	for(; index < vec.size(); index++)
	{
		if(order == vec[index])
		{
			return index;
		}
	}
	vec.push_back(order);
	return index;
}

/**
  * Returns the index in the vector of plans, or inserts in the last position.
  */
unsigned short Builder_plans::return_index_plan(const Order_eval_eq &order)
{
	return return_index_vec(order, plans_uniques);
}

/**
  * Returns the index in the vector of plans projects, or inserts in the last position.
  */
unsigned short Builder_plans::return_index_plan_p(const Order_eval_eq &order)
{
	return return_index_vec(order, plans_project_uniques);
}

/**
  * Generates and saves all evaluation's plans for the Attribute Grammar.
  */
bool Builder_plans::generate_plans()
{
	vector < Item_work > work_list;
	vector < Item_work > defined_item_work;
	/* Initial Rule: Is the position "1" because for obtain the initial symbol uses the rule "1"*/
	const Rule &initial_rule(attr_grammar.get_rules().begin()->second);

	/* Initializes the work list with the rule with the initial symbol grammar. */
	Order_eval_eq init_order;
	Context_rule context;
	context.father = 0; /* Initial rule hasn't father. */
	vector < unsigned short > invoque_context;
	invoque_context.push_back(initial_rule.key());
	context.context = invoque_context;
	generates_topological_order(build_graphs.get_dcg_graph(initial_rule.key()), init_order, context);

	init_order_ag = return_index_plan_p(init_order);

	Key_work_list key;
	/* Initial rule hasn't father. */
	key.father = 0;
	key.id_rule = initial_rule.key();
	Item_work i_eval;
	i_eval.item = key;
	i_eval.order_attr = init_order_ag;
	work_list.push_back(i_eval);

	const map<vector<unsigned short>,Graph> &adp_graphs(build_graphs.get_adp_graphs());

	while(work_list.size() > 0)
	{
		Item_work i_work(work_list.back());
		work_list.pop_back();

		if (!defined_work(defined_item_work, i_work))
		/* A(q,w) is not marked */
		{
			defined_item_work.push_back(i_work);

			for(map<vector<unsigned short>,Graph>::const_iterator adp(adp_graphs.begin()); adp != adp_graphs.end(); adp++)
			{
				/* Current rule that defines the ADP. */
				const Rule& rule(attr_grammar.get_rule(adp->first[0]));

				if (rule.key() == i_work.item.id_rule)
				/* The adp graph belong at rule of the item_work current. */
				{
					/* Creates the context rule with superior context and context of rule. */
					Context_rule context;
					context.father = i_work.item.father;
					context.context = adp->first;

					Order_eval_eq total_order(compute_order(adp->second, i_work.order_attr, context));

					Order_eval_eq order_purged;
					purge_plan_with(rule, total_order, order_purged);

					/* Saves the new_plan in the map. */
					Key_plan key_plan;
					key_plan.id_plan = return_index_context(adp->first);

					key_plan.plan = i_work.order_attr;
					unsigned short index_plan = return_index_plan(order_purged);
					pair < Key_plan, unsigned short > new_p(key_plan, index_plan);
					eval_plans.insert(new_p);

					vector<const Symbol*> right_side(rule.get_non_terminals_right_side());

					for(size_t i(0); i < right_side.size(); i++)
					{
						Order_eval_eq proj_order;

						const Rule& rule_proj(attr_grammar.get_rule(adp->first[i+1]));

						purge_plan_with(rule_proj, total_order, proj_order);

						if (proj_order.size() > 0)
						/* if size == 0 this plan not interesting on this project. */
						{
							/* Saves the new_plan_projected in the projected map. */
							Key_plan_project key_project;
							key_project.id_plan_project = key_plan;
							key_project.symbol_project = right_side[i];
							key_project.index_ocurrence = i;
							unsigned short index_plan_p = return_index_plan_p(proj_order);
							pair < Key_plan_project, unsigned short > new_p(key_project, index_plan_p);
							plans_project.insert(new_p);

							/* Creates new plans for the work-list with the rule's right symbol.  */
							Key_work_list key;
							/* adp->firts[0] is the id-rule. */
							key.father = rule.key();
							/* adp->firts[i+1] is the id_rule of rule for the i-esimo non-termials.*/
							key.id_rule = adp->first[i+1];
							Item_work i_work_new;
							i_work_new.item = key;
							i_work_new.order_attr = index_plan_p;
							if (!defined_work(defined_item_work, i_work_new))
							{
								if(!defined_work(work_list, i_work_new))
								{
									work_list.push_back(i_work_new);
								}
							}
						}
					}
				}
			}
		}
	}
	return true;
}

/**
  * Return: 0: when all success process.
  * 		1: when detects cilcyc graph.
  * 		2: when detects error in the graph generation.
  */
unsigned short Builder_plans::build_plans()
{
	if(generate_graphs())
	{
		if (build_graphs.check_cyclic_adp_dependencies())
		{
			cout << "* Build plans -------------- [ ABORT ]\n" << endl;
			return 1;
		}
		else if(generate_plans())
		{
			cout << "* Build plans -------------- [  OK  ]" << endl;
			return 0;
		}
		cout << "* Build plans -------------- [ FAIL ]\n" << endl;
	}
	return 2;
}

/**
  * Returns the context rule unique in this index.
  */
const Order_rule &Builder_plans::get_context_unique(const unsigned short i_context) const
{
	return contexts_uniques[i_context];
}

/**
  * Returns all contexts rule uniques.
  */
const vector < Order_rule > &Builder_plans::get_contexts_uniques() const
{
	return contexts_uniques;
}

/**
  * Returns all evaluations plans.
  */
const map < Key_plan, unsigned short > &Builder_plans::get_plans() const
{
	return eval_plans;
}

/**
  * Returns all evaluations plans uniques.
  */
const vector < Order_eval_eq > &Builder_plans::get_plans_uniques() const
{
	return plans_uniques;
}

/**
  * Returns all evaluations plans project.
  */
const map < Key_plan_project, unsigned short > &Builder_plans::get_plans_project() const
{
	return plans_project;
}

/**
  * Returns all evaluations plans project uniques.
  */
const vector < Order_eval_eq > &Builder_plans::get_plans_project_uniques() const
{
	return plans_project_uniques;
}

/**
  * Returns the intial order of attributes of the initial symbol.
  */
const unsigned short &Builder_plans::get_init_order() const
{
	return init_order_ag;
}

/**
  * Returns the index inside the map of the plan that passed as parameter.
  */
const unsigned short Builder_plans::get_index_plan(const map < Key_plan, unsigned short >::const_iterator it_plan) const
{
	unsigned short res(0);

	map < Key_plan, unsigned short >::const_iterator first(eval_plans.begin());
	map < Key_plan, unsigned short >::const_iterator last(eval_plans.end());

	while(it_plan != first && first != last)
	{
		res++;
		first++;
	}
	return res;
}

/**
  * Returns an constant iterator of a project plan with key equals at the key that passed as parameter.
  * Always finds the element.
  */
const map < Key_plan_project, unsigned short >::const_iterator Builder_plans::get_plan_project(const Key_plan_project &key) const
{
	const map < Key_plan_project, unsigned short >::const_iterator it(plans_project.find(key));
	assert(it != plans_project.end());
	return it;
}

} /* end genevalmag */
