/**
  *  \file      Builder_visit_sequences.h
  *  \brief     Header with the functions for build the visits sequences of grammar.
  *  \date      17/03/2010
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef BUILDER_VISIT_SEQUENCES_H_
#define BUILDER_VISIT_SEQUENCES_H_

#include <map>

#include "../Attr_grammar/Attr_grammar.h"
#include "Builder_plans.h"

using namespace std;

namespace genevalmag
{

/*
 * Where     item  > 0 represent to visit to this rule number.
 *           item == 0 represent to leave.
 *           item  < 0 represent to compute this equation number.
 */
typedef vector <int> Visit_seq;

class Builder_visit_sequences
{
    private:
		/**
		  * \var b_plans.
		  * \brief References to all plans generates.
		  */
		const Builder_plans &b_plans;

		/**
		  * \var attr_grammar.
		  * \brief References to the attribute grammar.
		  */
		const Attr_grammar &attr_grammar;

		/**
		  * \var all_visit_seqs.
		  * \brief Stores all visit sequences generates.
		  */
        vector < Visit_seq > all_visit_seqs;

        /**
          * Generates recursively the visit sequence, navigating the tree as
          * indicated by the plans, visiting the children, returning to the
          * parent or generating a compute attribute.
          *
          * @param it_plan
          * @param ins_computed
          * @param plans_computed
          * @param v_seq_computed
          * @return
          */
        bool gen_visit_seq
        (
        	const map<Key_plan, unsigned short>::const_iterator &it_plan,
        	vector<Ast_instance> &ins_computed,
        	vector< map<Key_plan, unsigned short>::const_iterator > &plans_computed,
        	const vector<unsigned short> &v_seq_computed
        );

        /**
          * Saves the visit sequence generate, mixing with pre-generated
          * visit sequences.
          * @param sequence
          * @param i_plan
          */
        void save_visit_sequence(const Visit_seq &sequence, const size_t i_plan);

    public:
        /**
          * Contructor empty of Builder_visit_sequences.
          * @param builder_plan
          * @param attribute_grammar
          * @return
          */
        Builder_visit_sequences(const Builder_plans &builder_plan, const Attr_grammar &attribute_grammar);

        /**
          * Destructor of Builder_visit_sequences.
          * @return
          */
        virtual ~Builder_visit_sequences();

        /**
          * Generates a visit sequence for each evaluation plan.
          * @return
          */
        bool generate_visit_sequences();

        /**
          * Returns the vector with all visit sequences generates.
          * @return
          */
        const vector < Visit_seq > &get_visit_seq() const;

        /**
          * Print in console, all visit sequences generates.
          */
        void print_all_visit_sequences() const;
};

} /* end genevalmag */

#endif /* BUILDER_VISIT_SEQUENCES_H_ */
