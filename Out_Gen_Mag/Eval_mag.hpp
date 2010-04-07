/**
  *  \file      Eval_mag.hpp
  *  \brief     Class generator from static evaluator generator: GENEVALMAG 
  *  \date      Tue Apr  6 21:44:48 2010
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
*/

#ifndef EVAL_MAG_HPP_
#define EVAL_MAG_HPP_

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "Node.hpp"
#include "Plan.hpp"

using namespace std;
using namespace util_ag;

/**
  * Sorts of the Semantic Domains.
  */

/**
  * Functions and Operators of the Semantic Domains.
  */

//extern int operator+ (int p0, int p1);

namespace evalmag
{

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
        for(size_t i(0); i < childs.size(); i++)
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
        for(size_t i(0); i < childs.size(); i++)
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
        for(size_t i(0); i < childs.size(); i++)
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
        for(size_t i(0); i < childs.size(); i++)
        {
            text.append(childs[i]->to_string());
        }
        return text;
    }
} Z ;

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

            Key_plan key_0;
            unsigned short __context_key_0[] = {1,4,2,5};
            Order_rule context_key_0(__context_key_0, __context_key_0 + sizeof(__context_key_0) / sizeof(unsigned short));
            key_0.id_plan = context_key_0;
            unsigned short __key_order_eq_key_0[] = {1};
            Order_eval_eq key_order_eq_key_0(__key_order_eq_key_0, __key_order_eq_key_0 + sizeof(__key_order_eq_key_0) / sizeof(unsigned short));
            key_0.plan = key_order_eq_key_0;

            unsigned short __order_eq_0[] = {2,3,4,1};
            Order_eval_eq order_eq_0(__order_eq_0, __order_eq_0 + sizeof(__order_eq_0) / sizeof(unsigned short));
            Plan __plan_0(key_0 , order_eq_0);
            eval_plans.push_back(__plan_0);

            Key_plan key_1;
            unsigned short __context_key_1[] = {1,4,3,5};
            Order_rule context_key_1(__context_key_1, __context_key_1 + sizeof(__context_key_1) / sizeof(unsigned short));
            key_1.id_plan = context_key_1;
            unsigned short __key_order_eq_key_1[] = {1};
            Order_eval_eq key_order_eq_key_1(__key_order_eq_key_1, __key_order_eq_key_1 + sizeof(__key_order_eq_key_1) / sizeof(unsigned short));
            key_1.plan = key_order_eq_key_1;

            unsigned short __order_eq_1[] = {4,2,3,1};
            Order_eval_eq order_eq_1(__order_eq_1, __order_eq_1 + sizeof(__order_eq_1) / sizeof(unsigned short));
            Plan __plan_1(key_1 , order_eq_1);
            eval_plans.push_back(__plan_1);

            Key_plan key_2;
            unsigned short __context_key_2[] = {2};
            Order_rule context_key_2(__context_key_2, __context_key_2 + sizeof(__context_key_2) / sizeof(unsigned short));
            key_2.id_plan = context_key_2;
            unsigned short __key_order_eq_key_2[] = {5,6};
            Order_eval_eq key_order_eq_key_2(__key_order_eq_key_2, __key_order_eq_key_2 + sizeof(__key_order_eq_key_2) / sizeof(unsigned short));
            key_2.plan = key_order_eq_key_2;

            unsigned short __order_eq_2[] = {5,6};
            Order_eval_eq order_eq_2(__order_eq_2, __order_eq_2 + sizeof(__order_eq_2) / sizeof(unsigned short));
            Plan __plan_2(key_2 , order_eq_2);
            eval_plans.push_back(__plan_2);

            Key_plan key_3;
            unsigned short __context_key_3[] = {2};
            Order_rule context_key_3(__context_key_3, __context_key_3 + sizeof(__context_key_3) / sizeof(unsigned short));
            key_3.id_plan = context_key_3;
            unsigned short __key_order_eq_key_3[] = {6,5};
            Order_eval_eq key_order_eq_key_3(__key_order_eq_key_3, __key_order_eq_key_3 + sizeof(__key_order_eq_key_3) / sizeof(unsigned short));
            key_3.plan = key_order_eq_key_3;

            unsigned short __order_eq_3[] = {6,5};
            Order_eval_eq order_eq_3(__order_eq_3, __order_eq_3 + sizeof(__order_eq_3) / sizeof(unsigned short));
            Plan __plan_3(key_3 , order_eq_3);
            eval_plans.push_back(__plan_3);

            Key_plan key_4;
            unsigned short __context_key_4[] = {3};
            Order_rule context_key_4(__context_key_4, __context_key_4 + sizeof(__context_key_4) / sizeof(unsigned short));
            key_4.id_plan = context_key_4;
            unsigned short __key_order_eq_key_4[] = {7,8};
            Order_eval_eq key_order_eq_key_4(__key_order_eq_key_4, __key_order_eq_key_4 + sizeof(__key_order_eq_key_4) / sizeof(unsigned short));
            key_4.plan = key_order_eq_key_4;

            unsigned short __order_eq_4[] = {7,8};
            Order_eval_eq order_eq_4(__order_eq_4, __order_eq_4 + sizeof(__order_eq_4) / sizeof(unsigned short));
            Plan __plan_4(key_4 , order_eq_4);
            eval_plans.push_back(__plan_4);

            Key_plan key_5;
            unsigned short __context_key_5[] = {4};
            Order_rule context_key_5(__context_key_5, __context_key_5 + sizeof(__context_key_5) / sizeof(unsigned short));
            key_5.id_plan = context_key_5;
            unsigned short __key_order_eq_key_5[] = {9};
            Order_eval_eq key_order_eq_key_5(__key_order_eq_key_5, __key_order_eq_key_5 + sizeof(__key_order_eq_key_5) / sizeof(unsigned short));
            key_5.plan = key_order_eq_key_5;

            unsigned short __order_eq_5[] = {9};
            Order_eval_eq order_eq_5(__order_eq_5, __order_eq_5 + sizeof(__order_eq_5) / sizeof(unsigned short));
            Plan __plan_5(key_5 , order_eq_5);
            eval_plans.push_back(__plan_5);

            Key_plan key_6;
            unsigned short __context_key_6[] = {5,2};
            Order_rule context_key_6(__context_key_6, __context_key_6 + sizeof(__context_key_6) / sizeof(unsigned short));
            key_6.id_plan = context_key_6;
            unsigned short __key_order_eq_key_6[] = {10};
            Order_eval_eq key_order_eq_key_6(__key_order_eq_key_6, __key_order_eq_key_6 + sizeof(__key_order_eq_key_6) / sizeof(unsigned short));
            key_6.plan = key_order_eq_key_6;

            unsigned short __order_eq_6[] = {11,12,10};
            Order_eval_eq order_eq_6(__order_eq_6, __order_eq_6 + sizeof(__order_eq_6) / sizeof(unsigned short));
            Plan __plan_6(key_6 , order_eq_6);
            eval_plans.push_back(__plan_6);

            Key_plan key_7;
            unsigned short __context_key_7[] = {5,3};
            Order_rule context_key_7(__context_key_7, __context_key_7 + sizeof(__context_key_7) / sizeof(unsigned short));
            key_7.id_plan = context_key_7;
            unsigned short __key_order_eq_key_7[] = {10};
            Order_eval_eq key_order_eq_key_7(__key_order_eq_key_7, __key_order_eq_key_7 + sizeof(__key_order_eq_key_7) / sizeof(unsigned short));
            key_7.plan = key_order_eq_key_7;

            unsigned short __order_eq_7[] = {12,11,10};
            Order_eval_eq order_eq_7(__order_eq_7, __order_eq_7 + sizeof(__order_eq_7) / sizeof(unsigned short));
            Plan __plan_7(key_7 , order_eq_7);
            eval_plans.push_back(__plan_7);

            /**
              * Initialize of Evaluation Plans Project.
              */

            Key_plan key_plan_proj_0;
            unsigned short __context_key_plan_proj_0[] = {1,4,2,5};
            Order_rule context_key_plan_proj_0(__context_key_plan_proj_0, __context_key_plan_proj_0 + sizeof(__context_key_plan_proj_0) / sizeof(unsigned short));
            key_plan_proj_0.id_plan = context_key_plan_proj_0;
            unsigned short __key_order_eq_key_plan_proj_0[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj_0(__key_order_eq_key_plan_proj_0, __key_order_eq_key_plan_proj_0 + sizeof(__key_order_eq_key_plan_proj_0) / sizeof(unsigned short));
            key_plan_proj_0.plan = key_order_eq_key_plan_proj_0;

            Key_plan_project key_proj_0;
            key_proj_0.id_plan_project = key_plan_proj_0;
            key_proj_0.node_project = "X";
            unsigned short __order_eq_proj_0[] = {9};
            Order_eval_eq order_eq_proj_0(__order_eq_proj_0, __order_eq_proj_0 + sizeof(__order_eq_proj_0) / sizeof(unsigned short));
            Plan_project __plan_proj_0(key_proj_0 , order_eq_proj_0);
            eval_plans_project.push_back(__plan_proj_0);

            Key_plan key_plan_proj_1;
            unsigned short __context_key_plan_proj_1[] = {1,4,3,5};
            Order_rule context_key_plan_proj_1(__context_key_plan_proj_1, __context_key_plan_proj_1 + sizeof(__context_key_plan_proj_1) / sizeof(unsigned short));
            key_plan_proj_1.id_plan = context_key_plan_proj_1;
            unsigned short __key_order_eq_key_plan_proj_1[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj_1(__key_order_eq_key_plan_proj_1, __key_order_eq_key_plan_proj_1 + sizeof(__key_order_eq_key_plan_proj_1) / sizeof(unsigned short));
            key_plan_proj_1.plan = key_order_eq_key_plan_proj_1;

            Key_plan_project key_proj_1;
            key_proj_1.id_plan_project = key_plan_proj_1;
            key_proj_1.node_project = "X";
            unsigned short __order_eq_proj_1[] = {9};
            Order_eval_eq order_eq_proj_1(__order_eq_proj_1, __order_eq_proj_1 + sizeof(__order_eq_proj_1) / sizeof(unsigned short));
            Plan_project __plan_proj_1(key_proj_1 , order_eq_proj_1);
            eval_plans_project.push_back(__plan_proj_1);

            Key_plan key_plan_proj_2;
            unsigned short __context_key_plan_proj_2[] = {1,4,2,5};
            Order_rule context_key_plan_proj_2(__context_key_plan_proj_2, __context_key_plan_proj_2 + sizeof(__context_key_plan_proj_2) / sizeof(unsigned short));
            key_plan_proj_2.id_plan = context_key_plan_proj_2;
            unsigned short __key_order_eq_key_plan_proj_2[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj_2(__key_order_eq_key_plan_proj_2, __key_order_eq_key_plan_proj_2 + sizeof(__key_order_eq_key_plan_proj_2) / sizeof(unsigned short));
            key_plan_proj_2.plan = key_order_eq_key_plan_proj_2;

            Key_plan_project key_proj_2;
            key_proj_2.id_plan_project = key_plan_proj_2;
            key_proj_2.node_project = "Y";
            unsigned short __order_eq_proj_2[] = {6,5};
            Order_eval_eq order_eq_proj_2(__order_eq_proj_2, __order_eq_proj_2 + sizeof(__order_eq_proj_2) / sizeof(unsigned short));
            Plan_project __plan_proj_2(key_proj_2 , order_eq_proj_2);
            eval_plans_project.push_back(__plan_proj_2);

            Key_plan key_plan_proj_3;
            unsigned short __context_key_plan_proj_3[] = {1,4,3,5};
            Order_rule context_key_plan_proj_3(__context_key_plan_proj_3, __context_key_plan_proj_3 + sizeof(__context_key_plan_proj_3) / sizeof(unsigned short));
            key_plan_proj_3.id_plan = context_key_plan_proj_3;
            unsigned short __key_order_eq_key_plan_proj_3[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj_3(__key_order_eq_key_plan_proj_3, __key_order_eq_key_plan_proj_3 + sizeof(__key_order_eq_key_plan_proj_3) / sizeof(unsigned short));
            key_plan_proj_3.plan = key_order_eq_key_plan_proj_3;

            Key_plan_project key_proj_3;
            key_proj_3.id_plan_project = key_plan_proj_3;
            key_proj_3.node_project = "Y";
            unsigned short __order_eq_proj_3[] = {7,8};
            Order_eval_eq order_eq_proj_3(__order_eq_proj_3, __order_eq_proj_3 + sizeof(__order_eq_proj_3) / sizeof(unsigned short));
            Plan_project __plan_proj_3(key_proj_3 , order_eq_proj_3);
            eval_plans_project.push_back(__plan_proj_3);

            Key_plan key_plan_proj_4;
            unsigned short __context_key_plan_proj_4[] = {5,2};
            Order_rule context_key_plan_proj_4(__context_key_plan_proj_4, __context_key_plan_proj_4 + sizeof(__context_key_plan_proj_4) / sizeof(unsigned short));
            key_plan_proj_4.id_plan = context_key_plan_proj_4;
            unsigned short __key_order_eq_key_plan_proj_4[] = {10};
            Order_eval_eq key_order_eq_key_plan_proj_4(__key_order_eq_key_plan_proj_4, __key_order_eq_key_plan_proj_4 + sizeof(__key_order_eq_key_plan_proj_4) / sizeof(unsigned short));
            key_plan_proj_4.plan = key_order_eq_key_plan_proj_4;

            Key_plan_project key_proj_4;
            key_proj_4.id_plan_project = key_plan_proj_4;
            key_proj_4.node_project = "Y";
            unsigned short __order_eq_proj_4[] = {5,6};
            Order_eval_eq order_eq_proj_4(__order_eq_proj_4, __order_eq_proj_4 + sizeof(__order_eq_proj_4) / sizeof(unsigned short));
            Plan_project __plan_proj_4(key_proj_4 , order_eq_proj_4);
            eval_plans_project.push_back(__plan_proj_4);

            Key_plan key_plan_proj_5;
            unsigned short __context_key_plan_proj_5[] = {5,3};
            Order_rule context_key_plan_proj_5(__context_key_plan_proj_5, __context_key_plan_proj_5 + sizeof(__context_key_plan_proj_5) / sizeof(unsigned short));
            key_plan_proj_5.id_plan = context_key_plan_proj_5;
            unsigned short __key_order_eq_key_plan_proj_5[] = {10};
            Order_eval_eq key_order_eq_key_plan_proj_5(__key_order_eq_key_plan_proj_5, __key_order_eq_key_plan_proj_5 + sizeof(__key_order_eq_key_plan_proj_5) / sizeof(unsigned short));
            key_plan_proj_5.plan = key_order_eq_key_plan_proj_5;

            Key_plan_project key_proj_5;
            key_proj_5.id_plan_project = key_plan_proj_5;
            key_proj_5.node_project = "Y";
            unsigned short __order_eq_proj_5[] = {7,8};
            Order_eval_eq order_eq_proj_5(__order_eq_proj_5, __order_eq_proj_5 + sizeof(__order_eq_proj_5) / sizeof(unsigned short));
            Plan_project __plan_proj_5(key_proj_5 , order_eq_proj_5);
            eval_plans_project.push_back(__plan_proj_5);

            Key_plan key_plan_proj_6;
            unsigned short __context_key_plan_proj_6[] = {1,4,2,5};
            Order_rule context_key_plan_proj_6(__context_key_plan_proj_6, __context_key_plan_proj_6 + sizeof(__context_key_plan_proj_6) / sizeof(unsigned short));
            key_plan_proj_6.id_plan = context_key_plan_proj_6;
            unsigned short __key_order_eq_key_plan_proj_6[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj_6(__key_order_eq_key_plan_proj_6, __key_order_eq_key_plan_proj_6 + sizeof(__key_order_eq_key_plan_proj_6) / sizeof(unsigned short));
            key_plan_proj_6.plan = key_order_eq_key_plan_proj_6;

            Key_plan_project key_proj_6;
            key_proj_6.id_plan_project = key_plan_proj_6;
            key_proj_6.node_project = "Z";
            unsigned short __order_eq_proj_6[] = {10};
            Order_eval_eq order_eq_proj_6(__order_eq_proj_6, __order_eq_proj_6 + sizeof(__order_eq_proj_6) / sizeof(unsigned short));
            Plan_project __plan_proj_6(key_proj_6 , order_eq_proj_6);
            eval_plans_project.push_back(__plan_proj_6);

            Key_plan key_plan_proj_7;
            unsigned short __context_key_plan_proj_7[] = {1,4,3,5};
            Order_rule context_key_plan_proj_7(__context_key_plan_proj_7, __context_key_plan_proj_7 + sizeof(__context_key_plan_proj_7) / sizeof(unsigned short));
            key_plan_proj_7.id_plan = context_key_plan_proj_7;
            unsigned short __key_order_eq_key_plan_proj_7[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj_7(__key_order_eq_key_plan_proj_7, __key_order_eq_key_plan_proj_7 + sizeof(__key_order_eq_key_plan_proj_7) / sizeof(unsigned short));
            key_plan_proj_7.plan = key_order_eq_key_plan_proj_7;

            Key_plan_project key_proj_7;
            key_proj_7.id_plan_project = key_plan_proj_7;
            key_proj_7.node_project = "Z";
            unsigned short __order_eq_proj_7[] = {10};
            Order_eval_eq order_eq_proj_7(__order_eq_proj_7, __order_eq_proj_7 + sizeof(__order_eq_proj_7) / sizeof(unsigned short));
            Plan_project __plan_proj_7(key_proj_7 , order_eq_proj_7);
            eval_plans_project.push_back(__plan_proj_7);

            /**
              * Initialize of Visit Sequences.
              */

            int __order_0[] = {-2,-3,-4,-1};
            Visit_sequence order_0(__order_0, __order_0 + sizeof(__order_0) / sizeof(int));
            v_seq.push_back(order_0);

            int __order_1[] = {-4,-2,-3,-1};
            Visit_sequence order_1(__order_1, __order_1 + sizeof(__order_1) / sizeof(int));
            v_seq.push_back(order_1);

            int __order_2[] = {};
            Visit_sequence order_2(__order_2, __order_2 + sizeof(__order_2) / sizeof(int));
            v_seq.push_back(order_2);

            int __order_3[] = {};
            Visit_sequence order_3(__order_3, __order_3 + sizeof(__order_3) / sizeof(int));
            v_seq.push_back(order_3);

            int __order_4[] = {};
            Visit_sequence order_4(__order_4, __order_4 + sizeof(__order_4) / sizeof(int));
            v_seq.push_back(order_4);

            int __order_5[] = {};
            Visit_sequence order_5(__order_5, __order_5 + sizeof(__order_5) / sizeof(int));
            v_seq.push_back(order_5);

            int __order_6[] = {};
            Visit_sequence order_6(__order_6, __order_6 + sizeof(__order_6) / sizeof(int));
            v_seq.push_back(order_6);

            int __order_7[] = {};
            Visit_sequence order_7(__order_7, __order_7 + sizeof(__order_7) / sizeof(int));
            v_seq.push_back(order_7);

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

        void traverse(struct Node * node, Order_eval_eq order)
        {
            Key_plan k_plan;
            k_plan.id_plan.push_back(node->rule_id);
            for(size_t i(0); i < node->childs.size(); i++)
            {
                k_plan.id_plan.push_back(node->childs[i]->rule_id);
            }
            k_plan.plan = order;
            bool find_plan(false);
            for(size_t i(0); i < eval_plans.size(); i++)
            {
                if (eval_plans[i].first == k_plan)
                {
                    node->index_plan_v_seq = i;
                    node->num_v_seq = 0;
                    find_plan = true;
                    break;
                }
            }
            if(!find_plan)
            {
                cerr << "ERROR: the AST input is wrong create." << endl;
                exit(-1);
            }
            Rule &rule(rules[node->rule_id - 1]);
            for(size_t i(0); i < node->childs.size(); i++)
            {
                Key_plan_project k_plan_proj;
                k_plan_proj.id_plan_project = k_plan;
                k_plan_proj.node_project = rule[i+1];
                for(size_t j(0); j < eval_plans_project.size(); j++)
                {
                    if (eval_plans_project[j].first == k_plan_proj)
                    {
                        traverse(node->childs[i], eval_plans_project[j].second);
                        break;
                    }
                }
            }
        }

        void translate_mag()
        {
            for(size_t v_s(0); v_s < v_seq.size(); v_s++)
            {
                for(size_t i(0); i < v_seq[v_s].size(); i++)
                {
                    if(v_seq[v_s][i] > 0)
                    {
                        cout << "Visit child " << v_seq[v_s][i];
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
        }

        // Eq (1) S[0].s0 = (((X[0].s1 + Y[0].s2) + Y[0].s3) + Z[0].s4);
        void compute_eq_1(struct Node *root)
        {
            S *node((S*) root);
            node->s0 = (((((X*)node->childs[0])->s1 + ((Y*)node->childs[1])->s2) + ((Y*)node->childs[1])->s3) + ((Z*)node->childs[2])->s4);
        }

        // Eq (2) X[0].i1 = Y[0].s3;
        void compute_eq_2(struct Node *root)
        {
            S *node((S*) root);
            ((X*)node->childs[0])->i1 = ((Y*)node->childs[1])->s3;
        }

        // Eq (3) Y[0].i2 = X[0].s1;
        void compute_eq_3(struct Node *root)
        {
            S *node((S*) root);
            ((Y*)node->childs[1])->i2 = ((X*)node->childs[0])->s1;
        }

        // Eq (4) Y[0].i3 = Y[0].s2;
        void compute_eq_4(struct Node *root)
        {
            S *node((S*) root);
            ((Y*)node->childs[1])->i3 = ((Y*)node->childs[1])->s2;
        }

        // Eq (5) Y[0].s2 = Y[0].i2;
        void compute_eq_5(struct Node *root)
        {
            Y *node((Y*) root);
            node->s2 = node->i2;
        }

        // Eq (6) Y[0].s3 = 1;
        void compute_eq_6(struct Node *root)
        {
            Y *node((Y*) root);
            node->s3 = 1;
        }

        // Eq (7) Y[0].s2 = 2;
        void compute_eq_7(struct Node *root)
        {
            Y *node((Y*) root);
            node->s2 = 2;
        }

        // Eq (8) Y[0].s3 = Y[0].i3;
        void compute_eq_8(struct Node *root)
        {
            Y *node((Y*) root);
            node->s3 = node->i3;
        }

        // Eq (9) X[0].s1 = X[0].i1;
        void compute_eq_9(struct Node *root)
        {
            X *node((X*) root);
            node->s1 = node->i1;
        }

        // Eq (10) Z[0].s4 = Y[0].s3;
        void compute_eq_10(struct Node *root)
        {
            Z *node((Z*) root);
            node->s4 = ((Y*)node->childs[0])->s3;
        }

        // Eq (11) Y[0].i2 = 3;
        void compute_eq_11(struct Node *root)
        {
            Z *node((Z*) root);
            ((Y*)node->childs[0])->i2 = 3;
        }

        // Eq (12) Y[0].i3 = Y[0].s2;
        void compute_eq_12(struct Node *root)
        {
            Z *node((Z*) root);
            ((Y*)node->childs[0])->i3 = ((Y*)node->childs[0])->s2;
        }

    	void compute_eq(int num_eq, struct Node *root)
     	{
    		switch ( num_eq ) {
    		  case 1: compute_eq_1(root); break;

    		  case 2: compute_eq_2(root); break;

    		  case 3: compute_eq_3(root); break;

    		  case 4: compute_eq_4(root); break;

    		  case 5: compute_eq_5(root); break;

    		  case 6: compute_eq_6(root); break;

    		  case 7: compute_eq_7(root); break;

    		  case 8: compute_eq_8(root); break;

    		  case 9: compute_eq_9(root); break;

    		  case 10: compute_eq_10(root); break;

    		  case 11: compute_eq_11(root); break;

    		  case 12: compute_eq_12(root); break;

     		  default: cout << "ERROR: Fatal action." << endl;
    		}
     	}

        void eval_visiter(struct Node *root)
        {
        	for(size_t i(root->num_v_seq); i < v_seq[root->index_plan_v_seq].size(); i++)
        	{
        		int item_visit(v_seq[root->index_plan_v_seq][i]);
        		if (item_visit > 0)
        		{
        		    eval_visiter(root->childs[item_visit - 1]);
        		}
        		else if (item_visit < 0)
        		{
    				compute_eq((item_visit * -1), root);
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
            vector < Order_eval_eq > orders_init;
            unsigned short __order_root_0[] = {1};
            Order_eval_eq order_root_0(__order_root_0, __order_root_0 + sizeof(__order_root_0) / sizeof(unsigned short));
            orders_init.push_back(order_root_0);
        	traverse(root, orders_init[root->rule_id - 1]);
        	eval_visiter(root);
        }
};

} /* end namespace */

#endif /* EVAL_MAG_HPP_ */

