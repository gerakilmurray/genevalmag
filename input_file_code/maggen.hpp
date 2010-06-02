/**
  *  \file      maggen.hpp
  *  \brief     Class generator from static evaluator generator: GENEVALMAG 
  *  \date      Wed Jun  2 11:02:50 2010
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
*/

#ifndef _MAGGEN_HPP_
#define _MAGGEN_HPP_

#include <vector>

#include "Node.hpp"
#include "Plan.hpp"

using namespace std;
using namespace util_ag;

namespace evalmag
{

/**
  * Structs of the symbols.
  */
typedef struct Symbol_S: Node
{
    int s0;

    Symbol_S(const unsigned short &r_id);

    string to_string() const;
} S ;

typedef struct Symbol_X: Node
{
    int i1;
    int s1;

    Symbol_X(const unsigned short &r_id);

    string to_string() const;
} X ;

typedef struct Symbol_Y: Node
{
    int i2;
    int i3;
    int s2;
    int s3;

    Symbol_Y(const unsigned short &r_id);

    string to_string() const;
} Y ;

typedef struct Symbol_Z: Node
{
    int s4;

    Symbol_Z(const unsigned short &r_id);

    string to_string() const;
} Z ;

/**
  * Main class of GenEvalMag.
  */
class maggen
{
    private:
        vector < Visit_sequence >    v_seq;

        vector < Order_rule >        contexts_rule;

        /* "ro" function. Wuu Yang's paper. */
        vector < Plan >              eval_plans;

        /* "theta" function. Wuu Yang's paper. */
        vector < Plan_project >      eval_plans_project;

        vector < Rule >              rules;

        void add_plan(const Key_plan &k_plan, unsigned short index_order);
        void add_plan_project(const Key_plan_project &k_plan_p, unsigned short index_order);
        void compute_eq(int num_eq, struct Node *root);
        void traverse(struct Node * node, unsigned short order);
        void eval_visiter(struct Node *root);

    public:
        maggen();

        void print_visit_seqs();

        void translates_visit_segs();

        void evaluator_mag(struct Node *root);

};

} /* end evalmag */

#endif /* _MAGGEN_HPP_ */

