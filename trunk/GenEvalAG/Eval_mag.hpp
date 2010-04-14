/**
  *  \file      Eval_mag.hpp
  *  \brief     Class generator from static evaluator generator: GENEVALMAG 
  *  \date      Tue Apr 13 22:57:29 2010
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
*/

#ifndef _EVAL_MAG_HPP_
#define _EVAL_MAG_HPP_

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

    string to_string() const;
} S ;

typedef struct Symbol_X: Node
{
    int i1;
    int s1;

    string to_string() const;
} X ;

typedef struct Symbol_Y: Node
{
    int i2;
    int i3;
    int s2;
    int s3;

    string to_string() const;
} Y ;

typedef struct Symbol_Z: Node
{
    int s4;

    string to_string() const;
} Z ;

/**
  * Main class of GenEvalMag.
  */
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
        Eval_mag();

        void print_v_seq();

        void traverse(struct Node * node, Order_eval_eq order);

        void translate_mag();

        void compute_eq(int num_eq, struct Node *root);

        void eval_visiter(struct Node *root);

        void evaluator_mag(struct Node *root);
};

} /* end evalmag */

#endif /* _EVAL_MAG_HPP_ */

