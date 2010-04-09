/**
  *  \file		Builder_plans.h
  *  \brief		Header of generation plans module of Attribute Grammar.
  *  \date		18/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef BUILDER_PLANS_H_
#define BUILDER_PLANS_H_

#include <map>

#include "../Attr_grammar/Attr_grammar.h"
#include "../Attr_grammar/Rule.h"

#include "Builder_graphs.h"

using namespace std;

namespace genevalmag
{
/* Vector for order of equation. */
typedef vector< unsigned short > Order_eval_eq;

/* Vector that represents the inferior context of rule. */
typedef vector< unsigned short > Order_rule;

/* Father and conext of rule. */
typedef struct c_rule
{
	unsigned short	father;
	Order_rule		context;

	bool operator< (const c_rule &other) const
	{
		return (father < other.father) || (context < other.context);
	}

	c_rule &operator= (const c_rule &other)
	{
		if(this != &other)
		{
			father = other.father;
			context = other.context;
		}
		return *this;
	}
} Context_rule;

/* Father and id-rule of rule. */
typedef struct k_w
{
	unsigned short	father;
	unsigned short	id_rule;

	bool operator== (const k_w &other) const
	{
		return (father == other.father) && (id_rule == other.id_rule);
	}

	k_w &operator= (const k_w &other)
	{
		if(this != &other)
		{
			father = other.father;
			id_rule = other.id_rule;
		}
		return *this;
	}
} Key_work_list;

/* Struct that represents an item in the list of work. */
typedef struct i_w
{
	Key_work_list	item;
	Order_eval_eq	order_attr;

	bool operator== (const i_w &other) const
	{
		return (item == other.item) && (order_attr == other.order_attr);
	}

	i_w &operator= (const i_w &other)
	{
		if(this != &other)
		{
			item = other.item;
			order_attr = other.order_attr;
		}
		return *this;
	}
} Item_work;

/* Key for map of plans. */
typedef struct k_plan
{
	Order_rule      id_plan;
	Order_eval_eq	plan;

	bool operator< (const k_plan &other) const
	{
		return (id_plan < other.id_plan) || (plan < other.plan);
	}

	bool operator== (const k_plan &other) const
	{
		return (id_plan == other.id_plan) && (plan == other.plan);
	}

	k_plan &operator= (const k_plan &other)
	{
		if(this != &other)
		{
			id_plan = other.id_plan;
			plan = other.plan;
		}
		return *this;
	}
} Key_plan;

/* Key for map of plans_project. Is a the same key plan that map of plan with the projected symbol. */
typedef struct k_p_project
{
	Key_plan		id_plan_project;
	const Symbol	*symbol_project;
	unsigned short  index_ocurrence;

	bool operator< (const k_p_project &other) const
	{
		return (id_plan_project < other.id_plan_project) || (symbol_project->get_name() < other.symbol_project->get_name()) || (index_ocurrence < other.index_ocurrence);
	}

	bool operator== (const k_p_project &other) const
	{
		return (id_plan_project == other.id_plan_project) && (symbol_project->get_name() == other.symbol_project->get_name()) && (index_ocurrence == other.index_ocurrence);
	}

	k_p_project &operator= (const k_p_project &other)
	{
		if(this != &other)
		{
			id_plan_project = other.id_plan_project;
			symbol_project = other.symbol_project;
			index_ocurrence = other.index_ocurrence;
		}
		return *this;
	}
} Key_plan_project;

class Builder_plans
{
	private:
		map < Key_plan, Order_eval_eq > eval_plans; /* "ro" function. Wuu yank's paper. */

		map < Key_plan_project, Order_eval_eq > plans_project; /* "tita" function. Wuu yank's paper. */

		vector < Order_eval_eq > init_order_ag;

		/**
		  * Applies a topological order at graph.
		  * The changes are applies about paramenter "result_order".
		  */
		void generates_topological_order(const Graph &graph, Order_eval_eq &eq_order, const Attr_grammar &grammar, const Context_rule &context_rule) const;

		/**
		  * Compute the rule's order.
		  * The changes are applies about paramenter "result_order".
		  */
		Order_eval_eq compute_order(const Graph &graph_adp, const Order_eval_eq &eq_order, const Attr_grammar &grammar, const Context_rule &context_rule);

		/**
		  * Generates and saves all evaluation's plans for the Attribute Grammar.
		  */
		void generate_plans(const Attr_grammar &grammar, const Builder_graphs &build_graphs);

	public:
		/**
		  * Constructor empty of Builder plans.
		  */
		Builder_plans();

		/**
		  * Destructor of Builder plans.
		  */
		~Builder_plans();

		/**
		  * Generates and saves all evaluation's plans for the Attribute Grammar.
		  */
		bool build_plans(const Attr_grammar &attr_grammar);

		/**
		  * Prints all plans. Creates a graph that represents the plan and uses print_graph with dot.
		  */
		void print_all_plans(const Attr_grammar &grammar) const;
		/**
		  * Prints all proyected's plans. Creates a graph that represents the plan and uses print_graph with dot.
		  */
		void print_all_plans_project(const Attr_grammar &grammar) const;

		const map < Key_plan, Order_eval_eq > &get_plans() const;

		const map < Key_plan_project, Order_eval_eq > &get_plans_project() const;

		const vector < Order_eval_eq > &get_init_orders() const;

		const unsigned short get_index_plan(const map < Key_plan, Order_eval_eq >::const_iterator it_plan) const;

		const map < Key_plan_project, Order_eval_eq >::const_iterator get_plan_project(const Key_plan_project &key) const;

//		const vector< unsigned short > get_plans(Symbol * symb)
};

} /* end genevalmag */

#endif /* BUILDER_PLANS_H_ */
