/**
  *  \file      Eval_mag.hpp
  *  \brief     Class generator from static evaluator generator: GENEVALMAG 
  *  \date      Mon Apr  5 17:07:16 2010
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

//extern int f (int p0);

//extern int operator+ (int p0, int p1);

namespace evalmag
{

/**
  * Structs of the symbols.
  */

typedef struct Symbol_T: Node
{
    int longi;

    string to_string() const
    {
        string text("Values of symbol T:\n");
        text.append(" Attr longi = ");
        stringstream str_longi;
        str_longi << longi;
        text.append(str_longi.str());
        text.append("\n");
        for(size_t i(0); i < childs.size(); i++)
        {
            text.append(childs[i]->to_string());
        }
        return text;
    }
} T ;

typedef struct Symbol_T2: Node
{
    int longi;

    string to_string() const
    {
        string text("Values of symbol T2:\n");
        text.append(" Attr longi = ");
        stringstream str_longi;
        str_longi << longi;
        text.append(str_longi.str());
        text.append("\n");
        for(size_t i(0); i < childs.size(); i++)
        {
            text.append(childs[i]->to_string());
        }
        return text;
    }
} T2 ;

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
            unsigned short __context_key_0[] = {1,2,2,2,2,1,1};
            Order_rule context_key_0(__context_key_0, __context_key_0 + sizeof(__context_key_0) / sizeof(unsigned short));
            key_0.id_plan = context_key_0;
            unsigned short __key_order_eq_key_0[] = {1};
            Order_eval_eq key_order_eq_key_0(__key_order_eq_key_0, __key_order_eq_key_0 + sizeof(__key_order_eq_key_0) / sizeof(unsigned short));
            key_0.plan = key_order_eq_key_0;

            unsigned short __order_eq_0[] = {1};
            Order_eval_eq order_eq_0(__order_eq_0, __order_eq_0 + sizeof(__order_eq_0) / sizeof(unsigned short));
            Plan __plan_0(key_0 , order_eq_0);
            eval_plans.push_back(__plan_0);

            Key_plan key_1;
            unsigned short __context_key_1[] = {1,2,2,2,2,1,3};
            Order_rule context_key_1(__context_key_1, __context_key_1 + sizeof(__context_key_1) / sizeof(unsigned short));
            key_1.id_plan = context_key_1;
            unsigned short __key_order_eq_key_1[] = {1};
            Order_eval_eq key_order_eq_key_1(__key_order_eq_key_1, __key_order_eq_key_1 + sizeof(__key_order_eq_key_1) / sizeof(unsigned short));
            key_1.plan = key_order_eq_key_1;

            unsigned short __order_eq_1[] = {1};
            Order_eval_eq order_eq_1(__order_eq_1, __order_eq_1 + sizeof(__order_eq_1) / sizeof(unsigned short));
            Plan __plan_1(key_1 , order_eq_1);
            eval_plans.push_back(__plan_1);

            Key_plan key_2;
            unsigned short __context_key_2[] = {1,2,2,2,2,3,1};
            Order_rule context_key_2(__context_key_2, __context_key_2 + sizeof(__context_key_2) / sizeof(unsigned short));
            key_2.id_plan = context_key_2;
            unsigned short __key_order_eq_key_2[] = {1};
            Order_eval_eq key_order_eq_key_2(__key_order_eq_key_2, __key_order_eq_key_2 + sizeof(__key_order_eq_key_2) / sizeof(unsigned short));
            key_2.plan = key_order_eq_key_2;

            unsigned short __order_eq_2[] = {1};
            Order_eval_eq order_eq_2(__order_eq_2, __order_eq_2 + sizeof(__order_eq_2) / sizeof(unsigned short));
            Plan __plan_2(key_2 , order_eq_2);
            eval_plans.push_back(__plan_2);

            Key_plan key_3;
            unsigned short __context_key_3[] = {1,2,2,2,2,3,3};
            Order_rule context_key_3(__context_key_3, __context_key_3 + sizeof(__context_key_3) / sizeof(unsigned short));
            key_3.id_plan = context_key_3;
            unsigned short __key_order_eq_key_3[] = {1};
            Order_eval_eq key_order_eq_key_3(__key_order_eq_key_3, __key_order_eq_key_3 + sizeof(__key_order_eq_key_3) / sizeof(unsigned short));
            key_3.plan = key_order_eq_key_3;

            unsigned short __order_eq_3[] = {1};
            Order_eval_eq order_eq_3(__order_eq_3, __order_eq_3 + sizeof(__order_eq_3) / sizeof(unsigned short));
            Plan __plan_3(key_3 , order_eq_3);
            eval_plans.push_back(__plan_3);

            Key_plan key_4;
            unsigned short __context_key_4[] = {2};
            Order_rule context_key_4(__context_key_4, __context_key_4 + sizeof(__context_key_4) / sizeof(unsigned short));
            key_4.id_plan = context_key_4;
            unsigned short __key_order_eq_key_4[] = {2};
            Order_eval_eq key_order_eq_key_4(__key_order_eq_key_4, __key_order_eq_key_4 + sizeof(__key_order_eq_key_4) / sizeof(unsigned short));
            key_4.plan = key_order_eq_key_4;

            unsigned short __order_eq_4[] = {2};
            Order_eval_eq order_eq_4(__order_eq_4, __order_eq_4 + sizeof(__order_eq_4) / sizeof(unsigned short));
            Plan __plan_4(key_4 , order_eq_4);
            eval_plans.push_back(__plan_4);

            Key_plan key_5;
            unsigned short __context_key_5[] = {3};
            Order_rule context_key_5(__context_key_5, __context_key_5 + sizeof(__context_key_5) / sizeof(unsigned short));
            key_5.id_plan = context_key_5;
            unsigned short __key_order_eq_key_5[] = {3};
            Order_eval_eq key_order_eq_key_5(__key_order_eq_key_5, __key_order_eq_key_5 + sizeof(__key_order_eq_key_5) / sizeof(unsigned short));
            key_5.plan = key_order_eq_key_5;

            unsigned short __order_eq_5[] = {3};
            Order_eval_eq order_eq_5(__order_eq_5, __order_eq_5 + sizeof(__order_eq_5) / sizeof(unsigned short));
            Plan __plan_5(key_5 , order_eq_5);
            eval_plans.push_back(__plan_5);

            /**
              * Initialize of Evaluation Plans Project.
              */

            Key_plan key_plan_proj_0;
            unsigned short __context_key_plan_proj_0[] = {1,2,2,2,2,1,1};
            Order_rule context_key_plan_proj_0(__context_key_plan_proj_0, __context_key_plan_proj_0 + sizeof(__context_key_plan_proj_0) / sizeof(unsigned short));
            key_plan_proj_0.id_plan = context_key_plan_proj_0;
            unsigned short __key_order_eq_key_plan_proj_0[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj_0(__key_order_eq_key_plan_proj_0, __key_order_eq_key_plan_proj_0 + sizeof(__key_order_eq_key_plan_proj_0) / sizeof(unsigned short));
            key_plan_proj_0.plan = key_order_eq_key_plan_proj_0;

            Key_plan_project key_proj_0;
            key_proj_0.id_plan_project = key_plan_proj_0;
            key_proj_0.node_project = "T";
            unsigned short __order_eq_proj_0[] = {1};
            Order_eval_eq order_eq_proj_0(__order_eq_proj_0, __order_eq_proj_0 + sizeof(__order_eq_proj_0) / sizeof(unsigned short));
            Plan_project __plan_proj_0(key_proj_0 , order_eq_proj_0);
            eval_plans_project.push_back(__plan_proj_0);

            Key_plan key_plan_proj_1;
            unsigned short __context_key_plan_proj_1[] = {1,2,2,2,2,1,3};
            Order_rule context_key_plan_proj_1(__context_key_plan_proj_1, __context_key_plan_proj_1 + sizeof(__context_key_plan_proj_1) / sizeof(unsigned short));
            key_plan_proj_1.id_plan = context_key_plan_proj_1;
            unsigned short __key_order_eq_key_plan_proj_1[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj_1(__key_order_eq_key_plan_proj_1, __key_order_eq_key_plan_proj_1 + sizeof(__key_order_eq_key_plan_proj_1) / sizeof(unsigned short));
            key_plan_proj_1.plan = key_order_eq_key_plan_proj_1;

            Key_plan_project key_proj_1;
            key_proj_1.id_plan_project = key_plan_proj_1;
            key_proj_1.node_project = "T";
            unsigned short __order_eq_proj_1[] = {1};
            Order_eval_eq order_eq_proj_1(__order_eq_proj_1, __order_eq_proj_1 + sizeof(__order_eq_proj_1) / sizeof(unsigned short));
            Plan_project __plan_proj_1(key_proj_1 , order_eq_proj_1);
            eval_plans_project.push_back(__plan_proj_1);

            Key_plan key_plan_proj_2;
            unsigned short __context_key_plan_proj_2[] = {1,2,2,2,2,3,1};
            Order_rule context_key_plan_proj_2(__context_key_plan_proj_2, __context_key_plan_proj_2 + sizeof(__context_key_plan_proj_2) / sizeof(unsigned short));
            key_plan_proj_2.id_plan = context_key_plan_proj_2;
            unsigned short __key_order_eq_key_plan_proj_2[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj_2(__key_order_eq_key_plan_proj_2, __key_order_eq_key_plan_proj_2 + sizeof(__key_order_eq_key_plan_proj_2) / sizeof(unsigned short));
            key_plan_proj_2.plan = key_order_eq_key_plan_proj_2;

            Key_plan_project key_proj_2;
            key_proj_2.id_plan_project = key_plan_proj_2;
            key_proj_2.node_project = "T";
            unsigned short __order_eq_proj_2[] = {3};
            Order_eval_eq order_eq_proj_2(__order_eq_proj_2, __order_eq_proj_2 + sizeof(__order_eq_proj_2) / sizeof(unsigned short));
            Plan_project __plan_proj_2(key_proj_2 , order_eq_proj_2);
            eval_plans_project.push_back(__plan_proj_2);

            Key_plan key_plan_proj_3;
            unsigned short __context_key_plan_proj_3[] = {1,2,2,2,2,3,3};
            Order_rule context_key_plan_proj_3(__context_key_plan_proj_3, __context_key_plan_proj_3 + sizeof(__context_key_plan_proj_3) / sizeof(unsigned short));
            key_plan_proj_3.id_plan = context_key_plan_proj_3;
            unsigned short __key_order_eq_key_plan_proj_3[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj_3(__key_order_eq_key_plan_proj_3, __key_order_eq_key_plan_proj_3 + sizeof(__key_order_eq_key_plan_proj_3) / sizeof(unsigned short));
            key_plan_proj_3.plan = key_order_eq_key_plan_proj_3;

            Key_plan_project key_proj_3;
            key_proj_3.id_plan_project = key_plan_proj_3;
            key_proj_3.node_project = "T";
            unsigned short __order_eq_proj_3[] = {3};
            Order_eval_eq order_eq_proj_3(__order_eq_proj_3, __order_eq_proj_3 + sizeof(__order_eq_proj_3) / sizeof(unsigned short));
            Plan_project __plan_proj_3(key_proj_3 , order_eq_proj_3);
            eval_plans_project.push_back(__plan_proj_3);

            Key_plan key_plan_proj_4;
            unsigned short __context_key_plan_proj_4[] = {1,2,2,2,2,1,1};
            Order_rule context_key_plan_proj_4(__context_key_plan_proj_4, __context_key_plan_proj_4 + sizeof(__context_key_plan_proj_4) / sizeof(unsigned short));
            key_plan_proj_4.id_plan = context_key_plan_proj_4;
            unsigned short __key_order_eq_key_plan_proj_4[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj_4(__key_order_eq_key_plan_proj_4, __key_order_eq_key_plan_proj_4 + sizeof(__key_order_eq_key_plan_proj_4) / sizeof(unsigned short));
            key_plan_proj_4.plan = key_order_eq_key_plan_proj_4;

            Key_plan_project key_proj_4;
            key_proj_4.id_plan_project = key_plan_proj_4;
            key_proj_4.node_project = "T2";
            unsigned short __order_eq_proj_4[] = {2};
            Order_eval_eq order_eq_proj_4(__order_eq_proj_4, __order_eq_proj_4 + sizeof(__order_eq_proj_4) / sizeof(unsigned short));
            Plan_project __plan_proj_4(key_proj_4 , order_eq_proj_4);
            eval_plans_project.push_back(__plan_proj_4);

            Key_plan key_plan_proj_5;
            unsigned short __context_key_plan_proj_5[] = {1,2,2,2,2,1,3};
            Order_rule context_key_plan_proj_5(__context_key_plan_proj_5, __context_key_plan_proj_5 + sizeof(__context_key_plan_proj_5) / sizeof(unsigned short));
            key_plan_proj_5.id_plan = context_key_plan_proj_5;
            unsigned short __key_order_eq_key_plan_proj_5[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj_5(__key_order_eq_key_plan_proj_5, __key_order_eq_key_plan_proj_5 + sizeof(__key_order_eq_key_plan_proj_5) / sizeof(unsigned short));
            key_plan_proj_5.plan = key_order_eq_key_plan_proj_5;

            Key_plan_project key_proj_5;
            key_proj_5.id_plan_project = key_plan_proj_5;
            key_proj_5.node_project = "T2";
            unsigned short __order_eq_proj_5[] = {2};
            Order_eval_eq order_eq_proj_5(__order_eq_proj_5, __order_eq_proj_5 + sizeof(__order_eq_proj_5) / sizeof(unsigned short));
            Plan_project __plan_proj_5(key_proj_5 , order_eq_proj_5);
            eval_plans_project.push_back(__plan_proj_5);

            Key_plan key_plan_proj_6;
            unsigned short __context_key_plan_proj_6[] = {1,2,2,2,2,3,1};
            Order_rule context_key_plan_proj_6(__context_key_plan_proj_6, __context_key_plan_proj_6 + sizeof(__context_key_plan_proj_6) / sizeof(unsigned short));
            key_plan_proj_6.id_plan = context_key_plan_proj_6;
            unsigned short __key_order_eq_key_plan_proj_6[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj_6(__key_order_eq_key_plan_proj_6, __key_order_eq_key_plan_proj_6 + sizeof(__key_order_eq_key_plan_proj_6) / sizeof(unsigned short));
            key_plan_proj_6.plan = key_order_eq_key_plan_proj_6;

            Key_plan_project key_proj_6;
            key_proj_6.id_plan_project = key_plan_proj_6;
            key_proj_6.node_project = "T2";
            unsigned short __order_eq_proj_6[] = {2};
            Order_eval_eq order_eq_proj_6(__order_eq_proj_6, __order_eq_proj_6 + sizeof(__order_eq_proj_6) / sizeof(unsigned short));
            Plan_project __plan_proj_6(key_proj_6 , order_eq_proj_6);
            eval_plans_project.push_back(__plan_proj_6);

            Key_plan key_plan_proj_7;
            unsigned short __context_key_plan_proj_7[] = {1,2,2,2,2,3,3};
            Order_rule context_key_plan_proj_7(__context_key_plan_proj_7, __context_key_plan_proj_7 + sizeof(__context_key_plan_proj_7) / sizeof(unsigned short));
            key_plan_proj_7.id_plan = context_key_plan_proj_7;
            unsigned short __key_order_eq_key_plan_proj_7[] = {1};
            Order_eval_eq key_order_eq_key_plan_proj_7(__key_order_eq_key_plan_proj_7, __key_order_eq_key_plan_proj_7 + sizeof(__key_order_eq_key_plan_proj_7) / sizeof(unsigned short));
            key_plan_proj_7.plan = key_order_eq_key_plan_proj_7;

            Key_plan_project key_proj_7;
            key_proj_7.id_plan_project = key_plan_proj_7;
            key_proj_7.node_project = "T2";
            unsigned short __order_eq_proj_7[] = {2};
            Order_eval_eq order_eq_proj_7(__order_eq_proj_7, __order_eq_proj_7 + sizeof(__order_eq_proj_7) / sizeof(unsigned short));
            Plan_project __plan_proj_7(key_proj_7 , order_eq_proj_7);
            eval_plans_project.push_back(__plan_proj_7);

            /**
              * Initialize of Visit Sequences.
              */

            int __order_0[] = {4,2,3,1,5,6,-1};
            Visit_sequence order_0(__order_0, __order_0 + sizeof(__order_0) / sizeof(int));
            v_seq.push_back(order_0);

            int __order_1[] = {4,2,3,1,5,6,-1};
            Visit_sequence order_1(__order_1, __order_1 + sizeof(__order_1) / sizeof(int));
            v_seq.push_back(order_1);

            int __order_2[] = {4,2,3,1,5,6,-1};
            Visit_sequence order_2(__order_2, __order_2 + sizeof(__order_2) / sizeof(int));
            v_seq.push_back(order_2);

            int __order_3[] = {4,2,3,1,5,6,-1};
            Visit_sequence order_3(__order_3, __order_3 + sizeof(__order_3) / sizeof(int));
            v_seq.push_back(order_3);

            int __order_4[] = {-2};
            Visit_sequence order_4(__order_4, __order_4 + sizeof(__order_4) / sizeof(int));
            v_seq.push_back(order_4);

            int __order_5[] = {-3};
            Visit_sequence order_5(__order_5, __order_5 + sizeof(__order_5) / sizeof(int));
            v_seq.push_back(order_5);

            /**
              * Initialize of Rules of grammar.
              */

            string __rule_non_terminal_0[] = {"T","T2","T2","T2","T2","T","T"};
            Rule rule_non_terminal_0(__rule_non_terminal_0, __rule_non_terminal_0 + sizeof(__rule_non_terminal_0) / sizeof(string));
            rules.push_back(rule_non_terminal_0);

            string __rule_non_terminal_1[] = {"T2"};
            Rule rule_non_terminal_1(__rule_non_terminal_1, __rule_non_terminal_1 + sizeof(__rule_non_terminal_1) / sizeof(string));
            rules.push_back(rule_non_terminal_1);

            string __rule_non_terminal_2[] = {"T"};
            Rule rule_non_terminal_2(__rule_non_terminal_2, __rule_non_terminal_2 + sizeof(__rule_non_terminal_2) / sizeof(string));
            rules.push_back(rule_non_terminal_2);

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

        void translate_mag(int v_s)
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

        // Eq (1) T[0].longi = ((((((T2[3].longi + T2[1].longi) + T2[2].longi) + T2[0].longi) + T[1].longi) + T[2].longi) + 1);
        void compute_eq_1(struct Node *root)
        {
            T *node((T*) root);
            node->longi = ((((((((T2*)node->childs[3])->longi + ((T2*)node->childs[1])->longi) + ((T2*)node->childs[2])->longi) + ((T2*)node->childs[0])->longi) + ((T*)node->childs[4])->longi) + ((T*)node->childs[5])->longi) + 1);
        }

        // Eq (2) T2[0].longi = 1;
        void compute_eq_2(struct Node *root)
        {
            T2 *node((T2*) root);
            node->longi = 1;
        }

        // Eq (3) T[0].longi = 0;
        void compute_eq_3(struct Node *root)
        {
            T *node((T*) root);
            node->longi = 0;
        }

    	void compute_eq(int num_eq, struct Node *root)
     	{
    		switch ( num_eq ) {
    		  case 1: compute_eq_1(root); break;

    		  case 2: compute_eq_2(root); break;

    		  case 3: compute_eq_3(root); break;

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
            unsigned short __order_root_1[] = {3};
            Order_eval_eq order_root_1(__order_root_1, __order_root_1 + sizeof(__order_root_1) / sizeof(unsigned short));
            orders_init.push_back(order_root_1);
        	traverse(root, orders_init[root->rule_id - 1]);
        	eval_visiter(root);
        }
};

} /* end namespace */

#endif /* EVAL_MAG_HPP_ */

