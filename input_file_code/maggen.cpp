/**
  * \file    maggen.cpp
  * \brief   Implementation of methods of the evaluator of maggen.
  * \date    Thu Jun  3 17:34:53 2010
  * \author  Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  * \author  Picco, Gonzalo Martin <gonzalopicco@gmail.com>
*/

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <climits>
#include "maggen.hpp"

namespace evalmag
{

/**
  * Constructors of structs of the symbols.
  */
S::Symbol_S(const unsigned short &r_id): Node(r_id){}

X::Symbol_X(const unsigned short &r_id): Node(r_id){}

Y::Symbol_Y(const unsigned short &r_id): Node(r_id){}

Z::Symbol_Z(const unsigned short &r_id): Node(r_id){}

/**
  * To_string of structs of the symbols.
  */
string S::to_string() const
{
  string text("-- Values of symbol S:\n");
  text.append("   - Attribute synthesized s0 = ");
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

string X::to_string() const
{
  string text("-- Values of symbol X:\n");
  text.append("   - Attribute inherited i1 = ");
  stringstream str_i1;
  str_i1 << i1;
  text.append(str_i1.str());
  text.append("\n");
  text.append("   - Attribute synthesized s1 = ");
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

string Y::to_string() const
{
  string text("-- Values of symbol Y:\n");
  text.append("   - Attribute inherited i2 = ");
  stringstream str_i2;
  str_i2 << i2;
  text.append(str_i2.str());
  text.append("\n");
  text.append("   - Attribute inherited i3 = ");
  stringstream str_i3;
  str_i3 << i3;
  text.append(str_i3.str());
  text.append("\n");
  text.append("   - Attribute synthesized s2 = ");
  stringstream str_s2;
  str_s2 << s2;
  text.append(str_s2.str());
  text.append("\n");
  text.append("   - Attribute synthesized s3 = ");
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

string Z::to_string() const
{
  string text("-- Values of symbol Z:\n");
  text.append("   - Attribute synthesized s4 = ");
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

maggen::maggen()
{
  /**
    * Initialize of Contexts Rules.
    */
  unsigned short __context_0[] = {1,4,2,5};
  Order_rule context_0(__context_0, __context_0 + sizeof(__context_0) / sizeof(unsigned short));
  contexts_rule.push_back(context_0);

  unsigned short __context_1[] = {1,4,3,5};
  Order_rule context_1(__context_1, __context_1 + sizeof(__context_1) / sizeof(unsigned short));
  contexts_rule.push_back(context_1);

  unsigned short __context_2[] = {3};
  Order_rule context_2(__context_2, __context_2 + sizeof(__context_2) / sizeof(unsigned short));
  contexts_rule.push_back(context_2);

  unsigned short __context_3[] = {5,2};
  Order_rule context_3(__context_3, __context_3 + sizeof(__context_3) / sizeof(unsigned short));
  contexts_rule.push_back(context_3);

  unsigned short __context_4[] = {5,3};
  Order_rule context_4(__context_4, __context_4 + sizeof(__context_4) / sizeof(unsigned short));
  contexts_rule.push_back(context_4);

  unsigned short __context_5[] = {2};
  Order_rule context_5(__context_5, __context_5 + sizeof(__context_5) / sizeof(unsigned short));
  contexts_rule.push_back(context_5);

  unsigned short __context_6[] = {4};
  Order_rule context_6(__context_6, __context_6 + sizeof(__context_6) / sizeof(unsigned short));
  contexts_rule.push_back(context_6);

  /**
    * Initialize of Evaluation Plans.
    */
  Key_plan key_0(0, 0);
  add_plan(key_0 , 0);

  Key_plan key_1(1, 0);
  add_plan(key_1 , 1);

  Key_plan key_2(2, 4);
  add_plan(key_2 , 2);

  Key_plan key_3(3, 3);
  add_plan(key_3 , 3);

  Key_plan key_4(4, 3);
  add_plan(key_4 , 4);

  Key_plan key_5(5, 2);
  add_plan(key_5 , 6);

  Key_plan key_6(5, 5);
  add_plan(key_6 , 5);

  Key_plan key_7(6, 1);
  add_plan(key_7 , 7);

  /**
    * Initialize of Evaluation Plans Project.
    */
  Key_plan key_plan_proj_0(0, 0);
  Key_plan_project key_proj_0(key_plan_proj_0, 2, 0);
  add_plan_project(key_proj_0 , 1);

  Key_plan key_plan_proj_1(0, 0);
  Key_plan_project key_proj_1(key_plan_proj_1, 3, 1);
  add_plan_project(key_proj_1 , 2);

  Key_plan key_plan_proj_2(0, 0);
  Key_plan_project key_proj_2(key_plan_proj_2, 4, 2);
  add_plan_project(key_proj_2 , 3);

  Key_plan key_plan_proj_3(1, 0);
  Key_plan_project key_proj_3(key_plan_proj_3, 2, 0);
  add_plan_project(key_proj_3 , 1);

  Key_plan key_plan_proj_4(1, 0);
  Key_plan_project key_proj_4(key_plan_proj_4, 3, 1);
  add_plan_project(key_proj_4 , 4);

  Key_plan key_plan_proj_5(1, 0);
  Key_plan_project key_proj_5(key_plan_proj_5, 4, 2);
  add_plan_project(key_proj_5 , 3);

  Key_plan key_plan_proj_6(3, 3);
  Key_plan_project key_proj_6(key_plan_proj_6, 3, 0);
  add_plan_project(key_proj_6 , 5);

  Key_plan key_plan_proj_7(4, 3);
  Key_plan_project key_proj_7(key_plan_proj_7, 3, 0);
  add_plan_project(key_proj_7 , 4);

  /**
    * Initialize of Visit Sequences.
    */
  int __order_0[] = {2,-2,1,-3,2,-4,3,-1};
  Visit_sequence order_0(__order_0, __order_0 + sizeof(__order_0) / sizeof(int));
  v_seq.push_back(order_0);

  int __order_1[] = {2,-4,2,-2,1,-3,3,-1};
  Visit_sequence order_1(__order_1, __order_1 + sizeof(__order_1) / sizeof(int));
  v_seq.push_back(order_1);

  int __order_2[] = {-7,0,-8};
  Visit_sequence order_2(__order_2, __order_2 + sizeof(__order_2) / sizeof(int));
  v_seq.push_back(order_2);

  int __order_3[] = {-11,1,-12,-10};
  Visit_sequence order_3(__order_3, __order_3 + sizeof(__order_3) / sizeof(int));
  v_seq.push_back(order_3);

  int __order_4[] = {1,-12,-11,1,-10};
  Visit_sequence order_4(__order_4, __order_4 + sizeof(__order_4) / sizeof(int));
  v_seq.push_back(order_4);

  int __order_5[] = {-5,-6};
  Visit_sequence order_5(__order_5, __order_5 + sizeof(__order_5) / sizeof(int));
  v_seq.push_back(order_5);

  int __order_6[] = {-6,0,-5};
  Visit_sequence order_6(__order_6, __order_6 + sizeof(__order_6) / sizeof(int));
  v_seq.push_back(order_6);

  int __order_7[] = {-9};
  Visit_sequence order_7(__order_7, __order_7 + sizeof(__order_7) / sizeof(int));
  v_seq.push_back(order_7);

  /**
    * Initialize of Rules of grammar.
    */
  unsigned short __rule_non_terminal_0[] = {1,2,3,4};
  Rule rule_non_terminal_0(__rule_non_terminal_0, __rule_non_terminal_0 + sizeof(__rule_non_terminal_0) / sizeof(unsigned short));
  rules.push_back(rule_non_terminal_0);

  unsigned short __rule_non_terminal_1[] = {3};
  Rule rule_non_terminal_1(__rule_non_terminal_1, __rule_non_terminal_1 + sizeof(__rule_non_terminal_1) / sizeof(unsigned short));
  rules.push_back(rule_non_terminal_1);

  unsigned short __rule_non_terminal_2[] = {3};
  Rule rule_non_terminal_2(__rule_non_terminal_2, __rule_non_terminal_2 + sizeof(__rule_non_terminal_2) / sizeof(unsigned short));
  rules.push_back(rule_non_terminal_2);

  unsigned short __rule_non_terminal_3[] = {2};
  Rule rule_non_terminal_3(__rule_non_terminal_3, __rule_non_terminal_3 + sizeof(__rule_non_terminal_3) / sizeof(unsigned short));
  rules.push_back(rule_non_terminal_3);

  unsigned short __rule_non_terminal_4[] = {4,3};
  Rule rule_non_terminal_4(__rule_non_terminal_4, __rule_non_terminal_4 + sizeof(__rule_non_terminal_4) / sizeof(unsigned short));
  rules.push_back(rule_non_terminal_4);

}

void maggen::print_visit_seqs()
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

void maggen::add_plan(const Key_plan &k_plan, unsigned short index_order)
{
   Plan plan(k_plan, index_order);
   eval_plans.push_back(plan);
}

void maggen::add_plan_project(const Key_plan_project &k_plan_p, unsigned short index_order)
{
   Plan_project plan(k_plan_p, index_order);
   eval_plans_project.push_back(plan);
}

void maggen::translates_visit_segs()
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

unsigned short return_index_context(const Order_rule &context, const vector < Order_rule > &v_contexts)
{
  for(size_t i(0); i < v_contexts.size(); i++)
  {
    if(context == v_contexts[i])
    {
      return i;
    }
  }
  return USHRT_MAX;
}

void maggen::traverse(struct Node *node, unsigned short order)
{
  Order_rule context;
  context.push_back(node->rule_id);
  for(size_t i(0); i < node->childs.size(); i++)
  {
    context.push_back(node->childs[i]->rule_id);
  }
  unsigned short index_context(return_index_context(context, contexts_rule));
  if(index_context == USHRT_MAX)
  {
    cerr << "ERROR: the AST input is wrong create. Context rule does not exist." << endl;
    exit(-1);
  }
  Key_plan k_plan(index_context, order);
  bool find_plan(false);
  for(size_t i(0); i < eval_plans.size(); i++)
  {
    if (eval_plans[i].first == k_plan)
    {
      node->visit_seq_index = eval_plans[i].second;
      node->pos_visit_seq = 0;
      find_plan = true;
      break;
    }
  }
  if(!find_plan)
  {
    cerr << "ERROR: the AST input is wrong create. Evaluation plan does not exist." << endl;
    exit(-1);
  }
  Rule &rule(rules[node->rule_id - 1]);
  for(size_t i(0); i < node->childs.size(); i++)
  {
    Key_plan_project k_plan_proj(k_plan, rule[i+1], i);
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

// Eq /*1*/ S[0].s0 = (((X[0].s1 + Y[0].s2) + Y[0].s3) + Z[0].s4);
void compute_eq_1(struct Node *root)
{
  S *node((S*) root);
  node->s0 = (((((X*)node->childs[0])->s1 + ((Y*)node->childs[1])->s2) + ((Y*)node->childs[1])->s3) + ((Z*)node->childs[2])->s4);
}

// Eq /*2*/ X[0].i1 = Y[0].s3;
void compute_eq_2(struct Node *root)
{
  S *node((S*) root);
  ((X*)node->childs[0])->i1 = ((Y*)node->childs[1])->s3;
}

// Eq /*3*/ Y[0].i2 = X[0].s1;
void compute_eq_3(struct Node *root)
{
  S *node((S*) root);
  ((Y*)node->childs[1])->i2 = ((X*)node->childs[0])->s1;
}

// Eq /*4*/ Y[0].i3 = Y[0].s2;
void compute_eq_4(struct Node *root)
{
  S *node((S*) root);
  ((Y*)node->childs[1])->i3 = ((Y*)node->childs[1])->s2;
}

// Eq /*5*/ Y[0].s2 = Y[0].i2;
void compute_eq_5(struct Node *root)
{
  Y *node((Y*) root);
  node->s2 = node->i2;
}

// Eq /*6*/ Y[0].s3 = 1;
void compute_eq_6(struct Node *root)
{
  Y *node((Y*) root);
  node->s3 = 1;
}

// Eq /*7*/ Y[0].s2 = 2;
void compute_eq_7(struct Node *root)
{
  Y *node((Y*) root);
  node->s2 = 2;
}

// Eq /*8*/ Y[0].s3 = Y[0].i3;
void compute_eq_8(struct Node *root)
{
  Y *node((Y*) root);
  node->s3 = node->i3;
}

// Eq /*9*/ X[0].s1 = X[0].i1;
void compute_eq_9(struct Node *root)
{
  X *node((X*) root);
  node->s1 = node->i1;
}

// Eq /*10*/ Z[0].s4 = Y[0].s3;
void compute_eq_10(struct Node *root)
{
  Z *node((Z*) root);
  node->s4 = ((Y*)node->childs[0])->s3;
}

// Eq /*11*/ Y[0].i2 = 3;
void compute_eq_11(struct Node *root)
{
  Z *node((Z*) root);
  ((Y*)node->childs[0])->i2 = 3;
}

// Eq /*12*/ Y[0].i3 = Y[0].s2;
void compute_eq_12(struct Node *root)
{
  Z *node((Z*) root);
  ((Y*)node->childs[0])->i3 = ((Y*)node->childs[0])->s2;
}

void maggen::compute_eq(int num_eq, struct Node *root)
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

void maggen::eval_visiter(struct Node *root)
{
  for(size_t i(root->pos_visit_seq); i < v_seq[root->visit_seq_index].size(); i++)
  {
    int item_visit(v_seq[root->visit_seq_index][i]);
    if (item_visit > 0)
    {
      eval_visiter(root->childs[item_visit - 1]);
    }
    else if (item_visit < 0)
    {
      compute_eq((item_visit * (-1)), root);
    }
    else
    {
      /* Saves the index of the current v_seq item. */
      root->pos_visit_seq = i+1;
      return;
    }
  }
}

void maggen::evaluator_mag(struct Node *root)
{
  unsigned short order_init(0);
  traverse(root, order_init);
  eval_visiter(root);
}
} /* end evalmag */

