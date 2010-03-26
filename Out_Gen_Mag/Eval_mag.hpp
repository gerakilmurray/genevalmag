/**
  *  \file      Eval_mag.hpp
  *  \brief     Class generator from static evaluator generator: GENEVALMAG 
  *  \date      Fri Mar 26 20:22:43 2010
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
*/

#ifndef EVAL_MAG_HPP_
#define EVAL_MAG_HPP_

#include <iostream>
#include <sstream>
#include <vector>
#include "Node.hpp"
#include "Plan.hpp"

using namespace std;
using namespace util_ag;

namespace evalmag
{

/**
 * Sorts of the Semantic Domains.
 */

/**
 * Functions and Operators of the Semantic Domains.
 */

//extern int operator+ (int p0, int p1);

/**
 * Structs of the symbols.
 */

typedef struct Symbol_S: Node
{
    int s0;

    string to_string() const
    {
        string text("Values of symbol S:\n");
        text.append(" Attr s0 = ");
        stringstream str_s0;
        str_s0 << s0;
        text.append(str_s0.str());
        text.append("\n");
        for(size_t i(0);i<childs.size();i++)
        {
            text.append(childs[i]->to_string());
        }
        return text;
    }
} S ;

typedef struct Symbol_X: Node
{
    int i1;
    int s1;

    string to_string() const
    {
        string text("Values of symbol X:\n");
        text.append(" Attr i1 = ");
        stringstream str_i1;
        str_i1 << i1;
        text.append(str_i1.str());
        text.append("\n");
        text.append(" Attr s1 = ");
        stringstream str_s1;
        str_s1 << s1;
        text.append(str_s1.str());
        text.append("\n");
        for(size_t i(0);i<childs.size();i++)
        {
            text.append(childs[i]->to_string());
        }
        return text;
    }
} X ;

typedef struct Symbol_Y: Node
{
    int i2;
    int i3;
    int s2;
    int s3;

    string to_string() const
    {
        string text("Values of symbol Y:\n");
        text.append(" Attr i2 = ");
        stringstream str_i2;
        str_i2 << i2;
        text.append(str_i2.str());
        text.append("\n");
        text.append(" Attr i3 = ");
        stringstream str_i3;
        str_i3 << i3;
        text.append(str_i3.str());
        text.append("\n");
        text.append(" Attr s2 = ");
        stringstream str_s2;
        str_s2 << s2;
        text.append(str_s2.str());
        text.append("\n");
        text.append(" Attr s3 = ");
        stringstream str_s3;
        str_s3 << s3;
        text.append(str_s3.str());
        text.append("\n");
        for(size_t i(0);i<childs.size();i++)
        {
            text.append(childs[i]->to_string());
        }
        return text;
    }
} Y ;

typedef struct Symbol_Z: Node
{
    int s4;

    string to_string() const
    {
        string text("Values of symbol Z:\n");
        text.append(" Attr s4 = ");
        stringstream str_s4;
        str_s4 << s4;
        text.append(str_s4.str());
        text.append("\n");
        for(size_t i(0);i<childs.size();i++)
        {
            text.append(childs[i]->to_string());
        }
        return text;
    }
} Z ;

/**
 * Types for manage of plans.
 */

typedef vector< int >                            Visit_sequence;
typedef vector< string >                         Rule;
typedef pair< Key_plan,Order_eval_eq >           Plan;
typedef pair< Key_plan_project, Order_eval_eq >  Plan_project;

class Eval_mag
{
    private:
        vector < Visit_sequence >    v_seq;
        /* "ro" function. Wuu yank's paper. */
        vector < Plan >              eval_plans;
        /* "tita" function. Wuu yank's paper. */
        vector < Plan_project >      eval_plans_project;
        vector < Rule >              rules;

    public:
        Eval_mag()
        {
            /**
             * Initialize of Evaluation Plans.
             */

            Key_plan key0;
            key0.id_plan.father = 0;
            unsigned short __context_key0[] = {1,4,2,5};
            Order_rule context_key0(__context_key0, __context_key0 + sizeof(__context_key0) / sizeof(unsigned short));
            key0.id_plan.context = context_key0;
            unsigned short __key_order_eq_key0[] = {1};
            Order_eval_eq key_order_eq_key0(__key_order_eq_key0, __key_order_eq_key0 + sizeof(__key_order_eq_key0) / sizeof(unsigned short));
            key0.plan = key_order_eq_key0;

            unsigned short __order_eq0[] = {2,3,4,1};
            Order_eval_eq order_eq0(__order_eq0, __order_eq0 + sizeof(__order_eq0) / sizeof(unsigned short));
            Plan new_p0(key0 , order_eq0);
            eval_plans.push_back(new_p0);

            Key_plan key1;
            key1.id_plan.father = 0;
            unsigned short __context_key1[] = {1,4,3,5};
            Order_rule context_key1(__context_key1, __context_key1 + sizeof(__context_key1) / sizeof(unsigned short));
            key1.id_plan.context = context_key1;
            unsigned short __key_order_eq_key1[] = {1};
            Order_eval_eq key_order_eq_key1(__key_order_eq_key1, __key_order_eq_key1 + sizeof(__key_order_eq_key1) / sizeof(unsigned short));
            key1.plan = key_order_eq_key1;

            unsigned short __order_eq1[] = {4,2,3,1};
            Order_eval_eq order_eq1(__order_eq1, __order_eq1 + sizeof(__order_eq1) / sizeof(unsigned short));
            Plan new_p1(key1 , order_eq1);
            eval_plans.push_back(new_p1);

            Key_plan key2;
            key2.id_plan.father = 1;
            unsigned short __context_key2[] = {2};
            Order_rule context_key2(__context_key2, __context_key2 + sizeof(__context_key2) / sizeof(unsigned short));
            key2.id_plan.context = context_key2;
            unsigned short __key_order_eq_key2[] = {6,5};
            Order_eval_eq key_order_eq_key2(__key_order_eq_key2, __key_order_eq_key2 + sizeof(__key_order_eq_key2) / sizeof(unsigned short));
            key2.plan = key_order_eq_key2;

            unsigned short __order_eq2[] = {6,5};
            Order_eval_eq order_eq2(__order_eq2, __order_eq2 + sizeof(__order_eq2) / sizeof(unsigned short));
            Plan new_p2(key2 , order_eq2);
            eval_plans.push_back(new_p2);

            Key_plan key3;
            key3.id_plan.father = 1;
            unsigned short __context_key3[] = {3};
            Order_rule context_key3(__context_key3, __context_key3 + sizeof(__context_key3) / sizeof(unsigned short));
            key3.id_plan.context = context_key3;
            unsigned short __key_order_eq_key3[] = {7,8};
            Order_eval_eq key_order_eq_key3(__key_order_eq_key3, __key_order_eq_key3 + sizeof(__key_order_eq_key3) / sizeof(unsigned short));
            key3.plan = key_order_eq_key3;

            unsigned short __order_eq3[] = {7,8};
            Order_eval_eq order_eq3(__order_eq3, __order_eq3 + sizeof(__order_eq3) / sizeof(unsigned short));
            Plan new_p3(key3 , order_eq3);
            eval_plans.push_back(new_p3);

            Key_plan key4;
            key4.id_plan.father = 1;
            unsigned short __context_key4[] = {4};
            Order_rule context_key4(__context_key4, __context_key4 + sizeof(__context_key4) / sizeof(unsigned short));
            key4.id_plan.context = context_key4;
            unsigned short __key_order_eq_key4[] = {9};
            Order_eval_eq key_order_eq_key4(__key_order_eq_key4, __key_order_eq_key4 + sizeof(__key_order_eq_key4) / sizeof(unsigned short));
            key4.plan = key_order_eq_key4;

            unsigned short __order_eq4[] = {9};
            Order_eval_eq order_eq4(__order_eq4, __order_eq4 + sizeof(__order_eq4) / sizeof(unsigned short));
            Plan new_p4(key4 , order_eq4);
            eval_plans.push_back(new_p4);

            Key_plan key5;
            key5.id_plan.father = 5;
            unsigned short __context_key5[] = {2};
            Order_rule context_key5(__context_key5, __context_key5 + sizeof(__context_key5) / sizeof(unsigned short));
            key5.id_plan.context = context_key5;
            unsigned short __key_order_eq_key5[] = {5,6};
            Order_eval_eq key_order_eq_key5(__key_order_eq_key5, __key_order_eq_key5 + sizeof(__key_order_eq_key5) / sizeof(unsigned short));
            key5.plan = key_order_eq_key5;

            unsigned short __order_eq5[] = {5,6};
            Order_eval_eq order_eq5(__order_eq5, __order_eq5 + sizeof(__order_eq5) / sizeof(unsigned short));
            Plan new_p5(key5 , order_eq5);
            eval_plans.push_back(new_p5);

            Key_plan key6;
            key6.id_plan.father = 5;
            unsigned short __context_key6[] = {3};
            Order_rule context_key6(__context_key6, __context_key6 + sizeof(__context_key6) / sizeof(unsigned short));
            key6.id_plan.context = context_key6;
            unsigned short __key_order_eq_key6[] = {7,8};
            Order_eval_eq key_order_eq_key6(__key_order_eq_key6, __key_order_eq_key6 + sizeof(__key_order_eq_key6) / sizeof(unsigned short));
            key6.plan = key_order_eq_key6;

            unsigned short __order_eq6[] = {7,8};
            Order_eval_eq order_eq6(__order_eq6, __order_eq6 + sizeof(__order_eq6) / sizeof(unsigned short));
            Plan new_p6(key6 , order_eq6);
            eval_plans.push_back(new_p6);

            Key_plan key7;
            key7.id_plan.father = 1;
            unsigned short __context_key7[] = {5,2};
            Order_rule context_key7(__context_key7, __context_key7 + sizeof(__context_key7) / sizeof(unsigned short));
            key7.id_plan.context = context_key7;
            unsigned short __key_order_eq_key7[] = {10};
            Order_eval_eq key_order_eq_key7(__key_order_eq_key7, __key_order_eq_key7 + sizeof(__key_order_eq_key7) / sizeof(unsigned short));
            key7.plan = key_order_eq_key7;

            unsigned short __order_eq7[] = {11,12,10};
            Order_eval_eq order_eq7(__order_eq7, __order_eq7 + sizeof(__order_eq7) / sizeof(unsigned short));
            Plan new_p7(key7 , order_eq7);
            eval_plans.push_back(new_p7);

            Key_plan key8;
            key8.id_plan.father = 1;
            unsigned short __context_key8[] = {5,3};
            Order_rule context_key8(__context_key8, __context_key8 + sizeof(__context_key8) / sizeof(unsigned short));
            key8.id_plan.context = context_key8;
            unsigned short __key_order_eq_key8[] = {10};
            Order_eval_eq key_order_eq_key8(__key_order_eq_key8, __key_order_eq_key8 + sizeof(__key_order_eq_key8) / sizeof(unsigned short));
            key8.plan = key_order_eq_key8;

            unsigned short __order_eq8[] = {12,11,10};
            Order_eval_eq order_eq8(__order_eq8, __order_eq8 + sizeof(__order_eq8) / sizeof(unsigned short));
            Plan new_p8(key8 , order_eq8);
            eval_plans.push_back(new_p8);

            /**
             * Initialize of Evaluation Plans Project.
             */

            Key_plan key_plan_proj0;
            key_plan_proj0.id_plan.father = 0;
            unsigned short __context_key_plan_proj0[] = {1,4,2,5};
            Order_rule context_key_plan_proj0(__context_key_plan_proj0, __context_key_plan_proj0 + sizeof(__context_key_plan_proj0) / sizeof(unsigned short));
            key_plan_proj0.id_plan.context = context_key_plan_proj0;
            unsigned short __key_order_eq_key_plan_proj0[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj0(__key_order_eq_key_plan_proj0, __key_order_eq_key_plan_proj0 + sizeof(__key_order_eq_key_plan_proj0) / sizeof(unsigned short));
            key_plan_proj0.plan = key_order_eq_key_plan_proj0;

            Key_plan_project key_proj0;
            key_proj0.id_plan_project = key_plan_proj0;
            key_proj0.node_project = "X";
            unsigned short __order_eq_proj0[] = {9};
            Order_eval_eq order_eq_proj0(__order_eq_proj0, __order_eq_proj0 + sizeof(__order_eq_proj0) / sizeof(unsigned short));
            Plan_project new_p_proj0(key_proj0 , order_eq_proj0);
            eval_plans_project.push_back(new_p_proj0);

            Key_plan key_plan_proj1;
            key_plan_proj1.id_plan.father = 0;
            unsigned short __context_key_plan_proj1[] = {1,4,3,5};
            Order_rule context_key_plan_proj1(__context_key_plan_proj1, __context_key_plan_proj1 + sizeof(__context_key_plan_proj1) / sizeof(unsigned short));
            key_plan_proj1.id_plan.context = context_key_plan_proj1;
            unsigned short __key_order_eq_key_plan_proj1[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj1(__key_order_eq_key_plan_proj1, __key_order_eq_key_plan_proj1 + sizeof(__key_order_eq_key_plan_proj1) / sizeof(unsigned short));
            key_plan_proj1.plan = key_order_eq_key_plan_proj1;

            Key_plan_project key_proj1;
            key_proj1.id_plan_project = key_plan_proj1;
            key_proj1.node_project = "X";
            unsigned short __order_eq_proj1[] = {9};
            Order_eval_eq order_eq_proj1(__order_eq_proj1, __order_eq_proj1 + sizeof(__order_eq_proj1) / sizeof(unsigned short));
            Plan_project new_p_proj1(key_proj1 , order_eq_proj1);
            eval_plans_project.push_back(new_p_proj1);

            Key_plan key_plan_proj2;
            key_plan_proj2.id_plan.father = 0;
            unsigned short __context_key_plan_proj2[] = {1,4,2,5};
            Order_rule context_key_plan_proj2(__context_key_plan_proj2, __context_key_plan_proj2 + sizeof(__context_key_plan_proj2) / sizeof(unsigned short));
            key_plan_proj2.id_plan.context = context_key_plan_proj2;
            unsigned short __key_order_eq_key_plan_proj2[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj2(__key_order_eq_key_plan_proj2, __key_order_eq_key_plan_proj2 + sizeof(__key_order_eq_key_plan_proj2) / sizeof(unsigned short));
            key_plan_proj2.plan = key_order_eq_key_plan_proj2;

            Key_plan_project key_proj2;
            key_proj2.id_plan_project = key_plan_proj2;
            key_proj2.node_project = "Y";
            unsigned short __order_eq_proj2[] = {6,5};
            Order_eval_eq order_eq_proj2(__order_eq_proj2, __order_eq_proj2 + sizeof(__order_eq_proj2) / sizeof(unsigned short));
            Plan_project new_p_proj2(key_proj2 , order_eq_proj2);
            eval_plans_project.push_back(new_p_proj2);

            Key_plan key_plan_proj3;
            key_plan_proj3.id_plan.father = 0;
            unsigned short __context_key_plan_proj3[] = {1,4,3,5};
            Order_rule context_key_plan_proj3(__context_key_plan_proj3, __context_key_plan_proj3 + sizeof(__context_key_plan_proj3) / sizeof(unsigned short));
            key_plan_proj3.id_plan.context = context_key_plan_proj3;
            unsigned short __key_order_eq_key_plan_proj3[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj3(__key_order_eq_key_plan_proj3, __key_order_eq_key_plan_proj3 + sizeof(__key_order_eq_key_plan_proj3) / sizeof(unsigned short));
            key_plan_proj3.plan = key_order_eq_key_plan_proj3;

            Key_plan_project key_proj3;
            key_proj3.id_plan_project = key_plan_proj3;
            key_proj3.node_project = "Y";
            unsigned short __order_eq_proj3[] = {7,8};
            Order_eval_eq order_eq_proj3(__order_eq_proj3, __order_eq_proj3 + sizeof(__order_eq_proj3) / sizeof(unsigned short));
            Plan_project new_p_proj3(key_proj3 , order_eq_proj3);
            eval_plans_project.push_back(new_p_proj3);

            Key_plan key_plan_proj4;
            key_plan_proj4.id_plan.father = 1;
            unsigned short __context_key_plan_proj4[] = {5,2};
            Order_rule context_key_plan_proj4(__context_key_plan_proj4, __context_key_plan_proj4 + sizeof(__context_key_plan_proj4) / sizeof(unsigned short));
            key_plan_proj4.id_plan.context = context_key_plan_proj4;
            unsigned short __key_order_eq_key_plan_proj4[] = {10};
            Order_eval_eq key_order_eq_key_plan_proj4(__key_order_eq_key_plan_proj4, __key_order_eq_key_plan_proj4 + sizeof(__key_order_eq_key_plan_proj4) / sizeof(unsigned short));
            key_plan_proj4.plan = key_order_eq_key_plan_proj4;

            Key_plan_project key_proj4;
            key_proj4.id_plan_project = key_plan_proj4;
            key_proj4.node_project = "Y";
            unsigned short __order_eq_proj4[] = {5,6};
            Order_eval_eq order_eq_proj4(__order_eq_proj4, __order_eq_proj4 + sizeof(__order_eq_proj4) / sizeof(unsigned short));
            Plan_project new_p_proj4(key_proj4 , order_eq_proj4);
            eval_plans_project.push_back(new_p_proj4);

            Key_plan key_plan_proj5;
            key_plan_proj5.id_plan.father = 1;
            unsigned short __context_key_plan_proj5[] = {5,3};
            Order_rule context_key_plan_proj5(__context_key_plan_proj5, __context_key_plan_proj5 + sizeof(__context_key_plan_proj5) / sizeof(unsigned short));
            key_plan_proj5.id_plan.context = context_key_plan_proj5;
            unsigned short __key_order_eq_key_plan_proj5[] = {10};
            Order_eval_eq key_order_eq_key_plan_proj5(__key_order_eq_key_plan_proj5, __key_order_eq_key_plan_proj5 + sizeof(__key_order_eq_key_plan_proj5) / sizeof(unsigned short));
            key_plan_proj5.plan = key_order_eq_key_plan_proj5;

            Key_plan_project key_proj5;
            key_proj5.id_plan_project = key_plan_proj5;
            key_proj5.node_project = "Y";
            unsigned short __order_eq_proj5[] = {7,8};
            Order_eval_eq order_eq_proj5(__order_eq_proj5, __order_eq_proj5 + sizeof(__order_eq_proj5) / sizeof(unsigned short));
            Plan_project new_p_proj5(key_proj5 , order_eq_proj5);
            eval_plans_project.push_back(new_p_proj5);

            Key_plan key_plan_proj6;
            key_plan_proj6.id_plan.father = 0;
            unsigned short __context_key_plan_proj6[] = {1,4,2,5};
            Order_rule context_key_plan_proj6(__context_key_plan_proj6, __context_key_plan_proj6 + sizeof(__context_key_plan_proj6) / sizeof(unsigned short));
            key_plan_proj6.id_plan.context = context_key_plan_proj6;
            unsigned short __key_order_eq_key_plan_proj6[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj6(__key_order_eq_key_plan_proj6, __key_order_eq_key_plan_proj6 + sizeof(__key_order_eq_key_plan_proj6) / sizeof(unsigned short));
            key_plan_proj6.plan = key_order_eq_key_plan_proj6;

            Key_plan_project key_proj6;
            key_proj6.id_plan_project = key_plan_proj6;
            key_proj6.node_project = "Z";
            unsigned short __order_eq_proj6[] = {10};
            Order_eval_eq order_eq_proj6(__order_eq_proj6, __order_eq_proj6 + sizeof(__order_eq_proj6) / sizeof(unsigned short));
            Plan_project new_p_proj6(key_proj6 , order_eq_proj6);
            eval_plans_project.push_back(new_p_proj6);

            Key_plan key_plan_proj7;
            key_plan_proj7.id_plan.father = 0;
            unsigned short __context_key_plan_proj7[] = {1,4,3,5};
            Order_rule context_key_plan_proj7(__context_key_plan_proj7, __context_key_plan_proj7 + sizeof(__context_key_plan_proj7) / sizeof(unsigned short));
            key_plan_proj7.id_plan.context = context_key_plan_proj7;
            unsigned short __key_order_eq_key_plan_proj7[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj7(__key_order_eq_key_plan_proj7, __key_order_eq_key_plan_proj7 + sizeof(__key_order_eq_key_plan_proj7) / sizeof(unsigned short));
            key_plan_proj7.plan = key_order_eq_key_plan_proj7;

            Key_plan_project key_proj7;
            key_proj7.id_plan_project = key_plan_proj7;
            key_proj7.node_project = "Z";
            unsigned short __order_eq_proj7[] = {10};
            Order_eval_eq order_eq_proj7(__order_eq_proj7, __order_eq_proj7 + sizeof(__order_eq_proj7) / sizeof(unsigned short));
            Plan_project new_p_proj7(key_proj7 , order_eq_proj7);
            eval_plans_project.push_back(new_p_proj7);

            /**
             * Initialize of Visit Sequences.
             */

            int __order0[] = {2,-2,4,-3,2,-4,5,-1};
            Visit_sequence order0(__order0, __order0 + sizeof(__order0) / sizeof(int));
            v_seq.push_back(order0);

            int __order1[] = {3,-4,3,-2,4,-3,5,-1};
            Visit_sequence order1(__order1, __order1 + sizeof(__order1) / sizeof(int));
            v_seq.push_back(order1);

            int __order2[] = {-6,0,-5};
            Visit_sequence order2(__order2, __order2 + sizeof(__order2) / sizeof(int));
            v_seq.push_back(order2);

            int __order3[] = {-7,0,-8};
            Visit_sequence order3(__order3, __order3 + sizeof(__order3) / sizeof(int));
            v_seq.push_back(order3);

            int __order4[] = {-9};
            Visit_sequence order4(__order4, __order4 + sizeof(__order4) / sizeof(int));
            v_seq.push_back(order4);

            int __order5[] = {-5,-6};
            Visit_sequence order5(__order5, __order5 + sizeof(__order5) / sizeof(int));
            v_seq.push_back(order5);

            int __order6[] = {-7,0,-8};
            Visit_sequence order6(__order6, __order6 + sizeof(__order6) / sizeof(int));
            v_seq.push_back(order6);

            int __order7[] = {-11,2,-12,-10};
            Visit_sequence order7(__order7, __order7 + sizeof(__order7) / sizeof(int));
            v_seq.push_back(order7);

            int __order8[] = {3,-12,-11,3,-10};
            Visit_sequence order8(__order8, __order8 + sizeof(__order8) / sizeof(int));
            v_seq.push_back(order8);

            /**
             * Initialize of Rules of grammar.
             */

            string __rule_non_terminal_0[] = {"S","X","Y","Z"};
            Rule rule_non_terminal_0(__rule_non_terminal_0, __rule_non_terminal_0 + sizeof(__rule_non_terminal_0) / sizeof(string));
            rules.push_back(rule_non_terminal_0);

            string __rule_non_terminal_1[] = {"Y"};
            Rule rule_non_terminal_1(__rule_non_terminal_1, __rule_non_terminal_1 + sizeof(__rule_non_terminal_1) / sizeof(string));
            rules.push_back(rule_non_terminal_1);

            string __rule_non_terminal_2[] = {"Y"};
            Rule rule_non_terminal_2(__rule_non_terminal_2, __rule_non_terminal_2 + sizeof(__rule_non_terminal_2) / sizeof(string));
            rules.push_back(rule_non_terminal_2);

            string __rule_non_terminal_3[] = {"X"};
            Rule rule_non_terminal_3(__rule_non_terminal_3, __rule_non_terminal_3 + sizeof(__rule_non_terminal_3) / sizeof(string));
            rules.push_back(rule_non_terminal_3);

            string __rule_non_terminal_4[] = {"Z","Y"};
            Rule rule_non_terminal_4(__rule_non_terminal_4, __rule_non_terminal_4 + sizeof(__rule_non_terminal_4) / sizeof(string));
            rules.push_back(rule_non_terminal_4);

        }

        void print_v_seq()
        {
            for(size_t i(0); i < v_seq.size(); i++)
            {
            	cout << "Visit Sequence Nro " << i+1 << ": ";
            	for(size_t j(0); j < v_seq[i].size(); j++)
            	{
            		cout << v_seq[i][j];
            		if(j < v_seq[i].size() - 1)
            		{
            			cout << ", ";
            		}
            	}
            	cout << "." << endl;
            }
        }

        void traverse(struct Node * node, Order_eval_eq order, unsigned short father)
        {
            Key_plan k_plan;
            k_plan.id_plan.context.push_back(node->rule_id);
            for(size_t i(0); i< node->childs.size();i++ )
            {
                k_plan.id_plan.context.push_back(node->childs[i]->rule_id);
            }
            k_plan.id_plan.father = father;
            k_plan.plan = order;
            for(size_t i(0); i < eval_plans.size(); i++)
            {
                if (eval_plans[i].first == k_plan)
                {
                    node->index_plan_v_seq = i;
                    node->num_v_seq = 0;
                    break;
                }
            }
            Rule &rule = rules[node->rule_id - 1];
            for(size_t i(0); i < node->childs.size(); i++)
            {
                Key_plan_project k_plan_proj;
                k_plan_proj.id_plan_project = k_plan;
                k_plan_proj.node_project = rule[i+1];
                for(size_t j(0); j < eval_plans_project.size(); j++)
                {
                    if (eval_plans_project[j].first == k_plan_proj)
                    {
                        traverse(node->childs[i], eval_plans_project[j].second, node->rule_id);
                        break;
                    }
                }
            }
        }

        void translate_mag(int v_s)
        {
            for(size_t i(0); i < v_seq[v_s].size(); i++)
            {
            	if(v_seq[v_s][i] > 0)
            	{
            	    cout << "Visit " << v_seq[v_s][i];
            	}
            	if(v_seq[v_s][i] == 0)
            	{
            	    cout << "Leave";
            	}
            	if(v_seq[v_s][i] < 0)
            	{
            	    cout << "Compute " << v_seq[v_s][i]*(-1);
            	}
            	if(i < v_seq[v_s].size() - 1)
            	{
            	    cout << ", ";
            	}
            }
            cout << "." << endl;
        }

        // Eq (1) S[0].s0 = (((X[0].s1 + Y[0].s2) + Y[0].s3) + Z[0].s4);
        void compute_eq_1(struct Node *root)
        {
            S *node = (S *) root;
            node->s0 = (((((X*)node->childs[0])->s1 + ((Y*)node->childs[1])->s2) + ((Y*)node->childs[1])->s3) + ((Z*)node->childs[2])->s4);
        }

        // Eq (2) X[0].i1 = Y[0].s3;
        void compute_eq_2(struct Node *root)
        {
            S *node = (S *) root;
            ((X*)node->childs[0])->i1 = ((Y*)node->childs[1])->s3;
        }

        // Eq (3) Y[0].i2 = X[0].s1;
        void compute_eq_3(struct Node *root)
        {
            S *node = (S *) root;
            ((Y*)node->childs[1])->i2 = ((X*)node->childs[0])->s1;
        }

        // Eq (4) Y[0].i3 = Y[0].s2;
        void compute_eq_4(struct Node *root)
        {
            S *node = (S *) root;
            ((Y*)node->childs[1])->i3 = ((Y*)node->childs[1])->s2;
        }

        // Eq (5) Y[0].s2 = Y[0].i2;
        void compute_eq_5(struct Node *root)
        {
            Y *node = (Y *) root;
            node->s2 = node->i2;
        }

        // Eq (6) Y[0].s3 = 1;
        void compute_eq_6(struct Node *root)
        {
            Y *node = (Y *) root;
            node->s3 = 1;
        }

        // Eq (7) Y[0].s2 = 2;
        void compute_eq_7(struct Node *root)
        {
            Y *node = (Y *) root;
            node->s2 = 2;
        }

        // Eq (8) Y[0].s3 = Y[0].i3;
        void compute_eq_8(struct Node *root)
        {
            Y *node = (Y *) root;
            node->s3 = node->i3;
        }

        // Eq (9) X[0].s1 = X[0].i1;
        void compute_eq_9(struct Node *root)
        {
            X *node = (X *) root;
            node->s1 = node->i1;
        }

        // Eq (10) Z[0].s4 = Y[0].s3;
        void compute_eq_10(struct Node *root)
        {
            Z *node = (Z *) root;
            node->s4 = ((Y*)node->childs[0])->s3;
        }

        // Eq (11) Y[0].i2 = 3;
        void compute_eq_11(struct Node *root)
        {
            Z *node = (Z *) root;
            ((Y*)node->childs[0])->i2 = 3;
        }

        // Eq (12) Y[0].i3 = Y[0].s2;
        void compute_eq_12(struct Node *root)
        {
            Z *node = (Z *) root;
            ((Y*)node->childs[0])->i3 = ((Y*)node->childs[0])->s2;
        }

    	void compute_eq(int num_eq, struct Node *root)
     	{
    		switch ( num_eq ) {
    		  case 1 :
    			compute_eq_1(root);
    			break;

    		  case 2 :
    			compute_eq_2(root);
    			break;

    		  case 3 :
    			compute_eq_3(root);
    			break;

    		  case 4 :
    			compute_eq_4(root);
    			break;

    		  case 5 :
    			compute_eq_5(root);
    			break;

    		  case 6 :
    			compute_eq_6(root);
    			break;

    		  case 7 :
    			compute_eq_7(root);
    			break;

    		  case 8 :
    			compute_eq_8(root);
    			break;

    		  case 9 :
    			compute_eq_9(root);
    			break;

    		  case 10 :
    			compute_eq_10(root);
    			break;

    		  case 11 :
    			compute_eq_11(root);
    			break;

    		  case 12 :
    			compute_eq_12(root);
    			break;

     		  default :
     			cout << "TODO MAL" << endl;
    		}
     	}

        void eval_visiter(struct Node *root)
        {
        	for (size_t i(root->num_v_seq);i < v_seq[root->index_plan_v_seq].size();i++)
        	{
        		int item_visit = v_seq[root->index_plan_v_seq][i];
        		if (item_visit > 0)
        		{
        			for(size_t j(0); j<root->childs.size();j++)
        			{
        				if (root->childs[j]->rule_id == item_visit)
        				{
        					eval_visiter(root->childs[j]);
        					break;
        				}
        			}
        		}
        		else if (item_visit < 0)
        		{
    				compute_eq((item_visit * -1),root);
        		}
        		else
        		{
        			root->num_v_seq = i+1; // donde quede
        			return;
        		}
        	}
        }

        void evaluator_mag(struct Node *root)
        {
            unsigned short __order_root0[] = {1};
            Order_eval_eq order_root0(__order_root0, __order_root0 + sizeof(__order_root0) / sizeof(unsigned short));
        	traverse(root, order_root0, 0);
        	eval_visiter(root);
        }
};

} /* end namespace */

#endif /* EVAL_MAG_HPP_ */

