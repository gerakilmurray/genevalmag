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
typedef pair < unsigned short, Order_rule > Context_rule;

// el padre y la regla
typedef pair < unsigned short, unsigned short > Key_work_list;

// key_work_list con el oden de esa regla aplicada al contexto que marca Key_work_list
typedef pair < Key_work_list, Order_eval_eq > Item_work;

// clave que almacena el contexto para el guadado del plan
typedef pair < Context_rule, Order_eval_eq > Key_plan;

// clave que almacena el contexto para el guadado del plan, proyectado al symbolo.
typedef pair < Key_plan, const Symbol* > Key_plan_project;


class Builder_plan
{
	private:
		map<Key_plan, Order_eval_eq> eval_plans; // Function of Selection

		map <Key_plan_project, Order_eval_eq> plans_project; // Function TITA.
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
};

} /* end genevalmag */

#endif /* BUILDER_PLAN_H_ */
