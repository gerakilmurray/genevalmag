/**
  *  \file    Plan.hpp
  *  \brief   Header with all struts, types and functions for plan's manager.
  *  \date    23/03/2010
  *  \author  Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author  Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef PLAN_HPP_
#define PLAN_HPP_

#include "Node.hpp"

namespace evalmag
{

/* Vector for order of equation. */
typedef vector <unsigned short> Order_eval_eq;

/* Vector that represents the inferior context of rule. */
typedef vector <unsigned short> Order_rule;

/* Key for map of plans. */
typedef struct k_plan
{
    unsigned short  id_plan;
    unsigned short  plan;

    bool operator== (const k_plan &other) const
    {
        return (id_plan == other.id_plan) &&
               (plan == other.plan);
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

    k_plan()
    {}

    k_plan(const unsigned short &context, const unsigned short &plan_)
    {
        id_plan = context;
        plan = plan_;
    }
} Key_plan;

/* Key for map of plans_project. Is a the same key plan that map of
 * plan with the projected symbol.
 */
typedef struct k_p_project
{
    Key_plan id_plan_project;
    unsigned short node_project;
    unsigned short index_ocurrence;

    bool operator== (const k_p_project &other) const
    {
        return (id_plan_project == other.id_plan_project) &&
               (node_project == other.node_project) &&
               (index_ocurrence == other.index_ocurrence);
    }

    k_p_project &operator= (const k_p_project &other)
    {
        if(this != &other)
        {
            id_plan_project = other.id_plan_project;
            node_project = other.node_project;
            index_ocurrence = other.index_ocurrence;
        }
        return *this;
    }

    k_p_project(const Key_plan &key, const unsigned short &node_p, const unsigned short &i_ocurrence)
    {
        id_plan_project = key;
        node_project = node_p;
        index_ocurrence = i_ocurrence;
    }

} Key_plan_project;

/**
 * Types for manage of plans.
 */
typedef vector <int> Visit_sequence;
typedef vector <unsigned short> Rule;
typedef pair <Key_plan, unsigned short> Plan;
typedef pair <Key_plan_project, unsigned short> Plan_project;

} /* end namespace */

#endif /* PLAN_HPP_ */

