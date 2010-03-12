/**
  *  \file		Builder_plan.h
  *  \brief		Header of generation plans module of Attribute Grammar.
  *  \date		18/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef BUILDER_PLAN_H_
#define BUILDER_PLAN_H_

#include <map>

#include "../Attr_grammar/Attr_grammar.h"
#include "../Attr_grammar/Rule.h"

#include "Builder_graphs.h"

using namespace std;

namespace genevalmag
{

// vector que almacena orden de equaciones
typedef vector< unsigned short > Order_eval_eq;

// vector que alamcena contexto inferior de la regla.
typedef vector< unsigned short > Order_rule;

// el padre de la regla con su contexto.
typedef struct c_rule
{
	unsigned short	father;
	Order_rule		context;

	bool operator< (const c_rule &other) const
	{
		return (context < other.context) ||
			   (father < other.father);
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

// el padre y la regla
typedef struct k_w
{
	unsigned short	father;
	unsigned short	id_rule;

	bool operator< (const k_w &other) const
	{
		return (id_rule < other.id_rule) ||
			   (father < other.father);
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

// key_work_list con el oden de esa regla aplicada al contexto que marca Key_work_list
typedef struct i_w
{
	Key_work_list	item;
	Order_eval_eq	order_attr;

	bool operator< (const i_w &other) const
	{
		return (order_attr < other.order_attr) ||
			   (item < other.item);
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

// clave que almacena el contexto para el guadado del plan
typedef struct k_plan
{
	Context_rule	id_plan;
	Order_eval_eq	plan;

	bool operator< (const k_plan &other) const
	{
		return (plan < other.plan) ||
			   (id_plan < other.id_plan);
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

// clave que almacena el contexto para el guadado del plan, proyectado al symbolo.
typedef struct k_p_project
{
	Key_plan		id_plan_project;
	const Symbol	*symbol_project;

	bool operator< (const k_p_project &other) const
	{
		return (symbol_project->get_name() < other.symbol_project->get_name()) ||
			   (id_plan_project < other.id_plan_project);
	}

	k_p_project &operator= (const k_p_project &other)
	{
		if(this != &other)
		{
			id_plan_project = other.id_plan_project;
			symbol_project = other.symbol_project;
		}
		return *this;
	}
} Key_plan_project;

class Builder_plan
{
	private:
		map< Key_plan, Order_eval_eq > eval_plans; // Function of Selection

		map < Key_plan_project, Order_eval_eq > plans_project; // Function TITA.

		void generates_topological_order(const Dp_graph &graph, Order_eval_eq &eq_order, const Attr_grammar &grammar, const Context_rule &context_rule) const;

		Order_eval_eq compute_order(const Dp_graph &graph_adp, const Order_eval_eq &eq_order, const Attr_grammar &grammar, const Context_rule &context_rule);

		void generate_plans(const Attr_grammar &grammar, const Builder_graphs &build_graphs);

	public:
		/**
		  * Constructor empty of Builder plan.
		  */
		Builder_plan();

		/**
		  * Destructor of Builder plan.
		  */
		~Builder_plan();

		/**
		  * Generates and saves all evaluation's plans for the Attribute Grammar.
		  */
		void build_plans(const Attr_grammar &attr_grammar);

		void print_all_plans(const Attr_grammar &grammar) const;

		void print_all_plans_project(const Attr_grammar &grammar) const;
};

} /* end genevalmag */

#endif /* BUILDER_PLAN_H_ */
