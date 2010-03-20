/**
  *  \file		Build_visit_sequence.h
  *  \brief		Header with the functions for build the visits sequences of grammar.
  *  \date		17/03/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
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
 * Where 	item > 0 represent to visit to this rule number.
 * 			item == 0 represent to leave;
 * 			item < 0  represent to compute this equation number.
 */
typedef vector <int> Visit_seq;

class Build_visit_sequence
{
	private:
		vector<Visit_seq> all_visit_seqs;

	public:
		Build_visit_sequence();
		virtual ~Build_visit_sequence();

		bool generate_seq_visit(const Attr_grammar &attr_grammar, const map < Key_plan, Order_eval_eq > &plans);

		bool gen_seq_visit(const Attr_grammar &attr_grammar, const vector < pair < Key_plan, Order_eval_eq > > &plans, size_t i_plan, vector<const Ast_instance*> &computed);

		void print_all_visit_sequences() const;

		const vector<Visit_seq> &get_visit_seq() const;
};

} /* end namespace */

#endif /* BUILD_VISIT_SEQUENCE_H_ */


