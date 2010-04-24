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

/**
  * Vector for order of equation.
  * Each number represent an equation.
  */
typedef vector< unsigned short > Order_eval_eq;

/**
  * Vector that represents the inferior context of rule.
  * Each number represent a rule.
  */
typedef vector< unsigned short > Order_rule;

/** This struct represent a Context_rule, that is a father rule and the context of rule. */
typedef struct c_rule
{
	/**
	 * \var father
	 * \brief Index context father (rule).
	 */
	unsigned short	father;
	/**
	 * \var context
	 * \brief Indexs contexts inferior (rules).
	 */
	Order_rule		context;
	/**
	 * operator<
	 * @param other
	 * @return
	 */
	bool operator< (const c_rule &other) const
	{
		return (context < other.context) ||
		       (context == other.context && father < other.father);
	}
	/**
	 * operator=
	 * @param other
	 * @return
	 */
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

/** This struct represents a Key_work_list, that is a father rule and id-rule of the current rule. */
typedef struct k_w
{
	/**
	 *  \var father
	 *  \brief Index context father (rule)
	 */
	unsigned short	father;
	/**
	 * \var id_rule.
	 * \brief The index of rule.
	 */
	unsigned short	id_rule;
	/**
	 * operator==
	 * @param other
	 * @return
	 */
	bool operator== (const k_w &other) const
	{
		return (father == other.father) && (id_rule == other.id_rule);
	}
	/**
	 * operator=
	 * @param other
	 * @return
	 */
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

/** This struct represents an Item work, that is an Key_work_list and an equations order evaluation. */
typedef struct i_w
{
	/**
	 * \var item
	 * \brief A key_work_list.
	 */
	Key_work_list	item;
	/**
	 * \var order_attr
	 * \brief Order of ecuation.
	 */
	unsigned short	order_attr;
	/**
	 * operator==
	 * @param other
	 * @return
	 */
	bool operator== (const i_w &other) const
	{
		return (item == other.item) && (order_attr == other.order_attr);
	}
	/**
	 * operator=
	 * @param other
	 * @return
	 */
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

/** This structs represent a Key_plan, that is an id and an equations order evaluation. */
typedef struct k_plan
{
	/**
	 * \var id_plan
	 * \brief Index plan. - index to order superior.
	 */
	unsigned short  id_plan;
	/**
	 * \var plan
	 * \brief Index plan.
	 */
	unsigned short	plan;
	/**
	 * operator<
	 * @param other
	 * @return
	 */
	bool operator< (const k_plan &other) const
	{
		return (id_plan < other.id_plan) ||
		       (id_plan == other.id_plan && plan < other.plan);
	}
	/**
	 * operator==
	 * @param other
	 * @return
	 */
	bool operator== (const k_plan &other) const
	{
		return (id_plan == other.id_plan) && (plan == other.plan);
	}
	/**
	 * operator=
	 * @param other
	 * @return
	 */
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

/** This struct represent a Key_plan_project, that is a Key_plan, the symbol and ocurrence, by which project. */
typedef struct k_p_project
{
	/**
	 * \var id_plan_project
	 * \brief key_plan
	 */
	Key_plan		id_plan_project;
	/**
	 * \var symbol_project
	 * \brief Projected Symbol.
	 */
	const Symbol	*symbol_project;
	/**
	 * \var Index_ocurrence
	 * \brief Appearance index of projected symbol.
	 */
	unsigned short  index_ocurrence;
	/**
	 * operator<
	 * @param other
	 * @return
	 */
	bool operator< (const k_p_project &other) const
	{
		return (id_plan_project < other.id_plan_project) ||
		       (id_plan_project == other.id_plan_project && symbol_project->get_name() < other.symbol_project->get_name()) ||
		       (id_plan_project == other.id_plan_project && symbol_project->get_name() == other.symbol_project->get_name() && index_ocurrence < other.index_ocurrence);
	}
	/**
	 * operator==
	 * @param other
	 * @return
	 */
	bool operator== (const k_p_project &other) const
	{
		return (id_plan_project == other.id_plan_project) && (symbol_project->get_name() == other.symbol_project->get_name()) && (index_ocurrence == other.index_ocurrence);
	}
	/**
	 * operator=
	 * @param other
	 * @return
	 */
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
		/**
		  * \var contexts_uniques
		  * \brief Store all different context rule generates in the grammar.
		  */
		vector < Order_rule > contexts_uniques;

	    /**
	      * \var eval_plans
		  * \brief Store all evaluation plans of the grammar. Saves index of plans_uniques vector.
	      * "ro" function. Wuu yank's paper.
	      */
		map < Key_plan, unsigned short > eval_plans;
		vector < Order_eval_eq > plans_uniques;

		/**
		  * \var plans_project
		  * \brief Store all evaluation plans projects of the grammar.Saves index of plans_project_uniques vector.
		  * "tita" function. Wuu yank's paper.
		  */
		map < Key_plan_project, unsigned short > plans_project;
		vector < Order_eval_eq > plans_project_uniques;

		/**
		  * \var init_order_ag
		  * \brief Store the initial evaluation order of the attributes of the initial symbol.
		  */
		unsigned short init_order_ag;

		/**
		  * \var build_graphs
		  * \brief Stores all graphs DP, DOWN, DCG and ADP, generated for the grammar's analisys.
		  */
		Builder_graphs build_graphs;

		/**
		  * Applies a topological order at graph.
		  * The changes are applies about paramenter "result_order".
		  * @param graph
		  * @param result_order
		  * @param grammar
		  * @param context_rule
		  */
		void generates_topological_order(const Graph &graph, Order_eval_eq &result_order, const Attr_grammar &grammar, const Context_rule &context_rule) const;

		/**
		  * Compute the rule's order.
		  * The changes are applies about paramenter "result_order".
		  * @param graph_adp
		  * @param index_order
		  * @param grammar
		  * @param context_rule
		  * @return
		  */
		Order_eval_eq compute_order(const Graph &graph_adp, unsigned short index_order, const Attr_grammar &grammar, const Context_rule &context_rule);

		/**
		  * Generates and saves all evaluation's plans for the Attribute Grammar.
		  * @param grammar
		  * @return
		  */
		bool generate_plans(const Attr_grammar &grammar);

		/**
		  * Generates all graphs for attribute grammar: DP, DOWN, DCG and ADP.
		  * @param grammar
		  * @return
		  */
		bool generate_graphs(const Attr_grammar &grammar);

		/**
		  * Returns the index in the vector of context, or inserts in the last position.
		  * @param order
		  * @return
		  */
		unsigned short return_index_context(const Order_rule &order);

		/**
		  * Returns the index in the vector of plans, or inserts in the last position.
		  * @param order
		  * @return
		  */
		unsigned short return_index_plan(const Order_eval_eq &order);

		/**
		  * Returns the index in the vector of plans projects, or inserts in the last position.
		  * @param order
		  * @return
		  */
		unsigned short return_index_plan_p(const Order_eval_eq &order);

	public:
		/**
		  * Constructor empty of Builder plans.
		  * @return
		  */
		Builder_plans();

		/**
		  * Destructor of Builder plans.
		  * @return
		  */
		~Builder_plans();

		/**
		  * Generates and saves all evaluation's plans for the Attribute Grammar.
		  *
		  * Return: 0: when all success process.
		  * 		1: when detects cilcyc graph.
		  * 		2: when detects error in the graph generation.
		  * @param attr_grammar
		  * @return
		  */
		unsigned short build_plans(const Attr_grammar &attr_grammar);

		/**
		  * Saves all plans. Creates a graph that represents the plan and uses print_graph with dot.
		  * @param grammar
		  * @param path_output
		  * @return
		  */
		bool save_all_plans(const Attr_grammar &grammar, const string path_output) const;

		/**
		  * Saves all proyected's plans. Creates a graph that represents the plan and uses print_graph with dot.
		  * @param grammar
		  * @param path_output
		  * @return
		  */
		bool save_all_plans_project(const Attr_grammar &grammar, const string path_output) const;

		/**
		  * Returns the context rule unique in this index.
		  *
		  * @param i_context
		  * @return
		  */
		const Order_rule &get_context_unique(const unsigned short i_context) const;

		/**
		  * Returns all contexts rule uniques.
		  * @return
		  */
		const vector < Order_rule > &get_contexts_uniques() const;

		/**
		  * Returns all evaluations plans.
		  * @return
		  */
		const map < Key_plan, unsigned short > &get_plans() const;

		/**
		  * Returns all evaluations plans uniques.
		  * @return
		  */
		const vector < Order_eval_eq > &get_plans_uniques() const;

		/**
		  * Returns all evaluations plans project.
		  * @return
		  */
		const map < Key_plan_project, unsigned short > &get_plans_project() const;

		/**
		  * Returns all evaluations plans project uniques.
		  * @return
		  */
		const vector < Order_eval_eq > &get_plans_project_uniques() const;

		/**
		  * Returns the intial order of attributes of the initial symbol.
		  * @return
		  */
		const unsigned short &get_init_order() const;

		/**
		  * Returns the index inside the map of the plan that passed as parameter.
		  * @param it_plan
		  * @return
		  */
		const unsigned short get_index_plan(const map < Key_plan, unsigned short >::const_iterator it_plan) const;

		/**
		  * Returns an constant iterator of a project plan with key equals at the key that passed as parameter.
		  * Always finds the element.
		  * @param key
		  * @return
		  */
		const map < Key_plan_project, unsigned short >::const_iterator get_plan_project(const Key_plan_project &key) const;

		/**
		  * Saves all graphs generated as the analysis of the dependencies between attributes.
		  * @param rules
		  * @param path_output
		  */
		void save_all_graphs(const map<unsigned short, Rule> &rules, const string path_output) const;

		/**
		  * Saves the graphs generated as the analysis of the dependencies between attributes, which demonstrate cyclicity.
		  * @param rules
		  * @param path_output
		  */
		void save_cyclic_graphs(const map<unsigned short, Rule> &rules, const string path_output) const;
};

} /* end genevalmag */

#endif /* BUILDER_PLANS_H_ */
