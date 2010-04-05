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

using namespace std;

namespace evalmag
{


/* Vector for order of equation. */
typedef vector< unsigned short > Order_eval_eq;

/* Vector that represents the inferior context of rule. */
typedef vector< unsigned short > Order_rule;

/* Father and conext of rule. */
//typedef struct c_rule
//{
//        unsigned short  father;
//        Order_rule              context;
//
//        bool operator== (const c_rule &other) const
//        {
//                return (father == other.father) && (context == other.context);
//        }
//
//        c_rule &operator= (const c_rule &other)
//        {
//                if(this != &other)
//                {
//                        father = other.father;
//                        context = other.context;
//                }
//                return *this;
//        }
//} Context_rule;

/* Father and id-rule of rule. */
//typedef struct k_w
//{
//        unsigned short  father;
//        unsigned short  id_rule;
//
//        bool operator== (const k_w &other) const
//        {
//                return (father == other.father) && (id_rule == other.id_rule);
//        }
//
//        k_w &operator= (const k_w &other)
//        {
//                if(this != &other)
//                {
//                        father = other.father;
//                        id_rule = other.id_rule;
//                }
//                return *this;
//        }
//} Key_work_list;

/* Struct that represents an item in the list of work. */
//typedef struct i_w
//{
//        Key_work_list   item;
//        Order_eval_eq   order_attr;
//
//        bool operator== (const i_w &other) const
//        {
//                return (item == other.item) && (order_attr == other.order_attr);
//        }
//
//        i_w &operator= (const i_w &other)
//        {
//                if(this != &other)
//                {
//                        item = other.item;
//                        order_attr = other.order_attr;
//                }
//                return *this;
//        }
//} Item_work;

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

        bool operator== (const k_p_project &other) const
        {
                return (id_plan_project == other.id_plan_project) && (node_project == other.node_project);
        }

        k_p_project &operator= (const k_p_project &other)
        {
                if(this != &other)
                {
                        id_plan_project = other.id_plan_project;
                        node_project = other.node_project;
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
