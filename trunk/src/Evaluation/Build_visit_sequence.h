/**
  *  \file      Build_visit_sequence.h
  *  \brief     Header with the functions for build the visits sequences of grammar.
  *  \date      17/03/2010
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef BUILD_VISIT_SEQUENCE_H_
#define BUILD_VISIT_SEQUENCE_H_

#include <map>

#include "../Attr_grammar/Attr_grammar.h"
#include "Builder_plan.h"

using namespace std;

namespace genevalmag
{

/*
 * Where     item  > 0 represent to visit to this rule number.
 *           item == 0 represent to leave.
 *           item  < 0 represent to compute this equation number.
 */
typedef vector <int> Visit_seq;

class Build_visit_sequence
{
    private:
        /**
          * Stores all visit sequences generates.
          */
        vector < Visit_seq > all_visit_seqs;

        /**
          * Generates recursively the visit sequence, navigating the tree as
          * indicated by the plans, visiting the children, returning to the
          * parent or generating a compute attribute.
          */
        bool gen_seq_visit(const Attr_grammar &attr_grammar, const vector < pair < Key_plan, Order_eval_eq > > &plans, size_t i_plan, vector<Ast_instance> &computed, vector<unsigned short> &plans_computed, const vector<unsigned short> &v_seq);

        /**
          * Saves the visit sequence generate, mixing with pre-generated
          * visit sequences.
          */
        void save_visit_sequence(const Visit_seq &sequence, const size_t i_plan);

    public:
        /**
          * Contructor empty of Build_visit_sequence.
          */
        Build_visit_sequence();

        /**
          * Destructor of Build_visit_sequence.
          */
        virtual ~Build_visit_sequence();

        /**
          * Generates a visit sequence for each evaluation plan.
          */
        bool generate_seq_visit(const Attr_grammar &attr_grammar, const map < Key_plan, Order_eval_eq > &plans);

        /**
          * Returns the vector with all visit sequences generates.
          */
        const vector < Visit_seq > &get_visit_seq() const;

        /**
          * Print in console, all visit sequences generates.
          */
        void print_all_visit_sequences() const;
};

} /* end genevalmag */

#endif /* BUILD_VISIT_SEQUENCE_H_ */
