/**
  *  \file              Plan.hpp
  *  \brief
  *  \date              23/03/2010
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef PLAN_HPP_
#define PLAN_HPP_

#include "Node.hpp"

namespace evalmag
{

/* Vector for order of equation. */
typedef vector< unsigned short > Order_eval_eq;

/* Vector that represents the inferior context of rule. */
typedef vector< unsigned short > Order_rule;

/* Key for map of plans. */
typedef struct k_plan
{
    Order_rule    id_plan;
    Order_eval_eq   plan;

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
    Key_plan                id_plan_project;
    string                  node_project;
    unsigned short          index_ocurrence;

    bool operator== (const k_p_project &other) const
    {
        return (id_plan_project == other.id_plan_project) && (node_project == other.node_project) && (index_ocurrence == other.index_ocurrence);
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
} Key_plan_project;

/**
 * Types for manage of plans.
 */
typedef vector< int >                            Visit_sequence;
typedef vector< string >                         Rule;
typedef pair< Key_plan,Order_eval_eq >           Plan;
typedef pair< Key_plan_project, Order_eval_eq >  Plan_project;

} /* end namespace */

#endif /* PLAN_HPP_ */

