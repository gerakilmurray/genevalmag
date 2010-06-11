/**
  *  \file    Node.h
  *  \brief   Header for node AST inside the MAG Evaluator.
  *  \date    17/03/2010
  *  \author  Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author  Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef NODE_HPP_
#define NODE_HPP_

#include <vector>
#include <string>

using namespace std;

namespace util_ag
{

struct Node
{
    struct Node *parent;
    vector <struct Node*> childs;
    unsigned short rule_id;

    /* Index of vector de visit sequence. */
    unsigned short visit_seq_index;

    /* Keeps the index of the current visit sequence item. */
    unsigned short pos_visit_seq;

    virtual string to_string() const = 0;
    
    Node(const unsigned short &r_id)
    {
        rule_id = r_id;
        parent = NULL;
    }
    
    struct Node &add(struct Node *child)
    {
        childs.push_back(child);
        child->parent = this;
        return *this;
    }
};

}/* end namespace */

#endif /* NODE_HPP_ */
