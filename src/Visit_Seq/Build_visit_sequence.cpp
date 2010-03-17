/**
  *  \file		Build_visit_sequence.h
  *  \brief		Implementation of the methods the Build_visit_sequence.h.
  *  \date		17/03/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>

#include "Build_visit_sequence.h"

namespace visit_seq
{


Build_visit_sequence::Build_visit_sequence()
{
}

Build_visit_sequence::~Build_visit_sequence()
{
}

bool ins_attr_computed(const Ast_instance *ins, const vector<const Ast_instance*> &vec)
{
	for(size_t i(0); i < vec.size(); i++)
	{
		if(vec[i]->equals(ins))
		{
			return true;
		}
	}
	return false;
}

void Build_visit_sequence::generate_seq_visit(const Attr_grammar &attr_grammar, const map < Key_plan, Order_eval_eq > &plans)
{
	for(map < Key_plan, Order_eval_eq >::const_iterator plan(plans.begin()); plan != plans.end(); plan++)
	{
		Visit_seq sequence;
		vector<const Ast_instance*> computed;
		const Rule& rule(attr_grammar.get_rule(plan->first.id_plan.context[0]));

		for(size_t i(0); i < plan->second.size(); i++)
		{
			const Equation *eq(rule.get_eq(plan->second[i]));

			/* Insert left instance. */
			vector<const Ast_instance*> instances_right_side;
			eq->inorder_only_instance(eq->get_r_value(), instances_right_side);

			for(size_t j(0); j < instances_right_side.size(); j++)
			{
				const Ast_instance* ins(instances_right_side[j]);

				if(!ins_attr_computed(ins, computed))
				{
					if(ins->get_symb()->equals(*rule.get_left_symbol()))
					{
						if(ins->get_attr()->is_inherit())
						{
							/* Checks that is not the first */
							if(sequence.size() > 0)
							{
								/* Leave this rule for superior context */
								sequence.push_back(0);
							}
						}
					}
					else
					{
						/* The attr symbols belong to right side of the rule */
						if(!ins->get_attr()->is_inherit())
						{
							vector<const Symbol*> non_term(rule.get_non_terminals_right_side());
							for(size_t k(0); k < non_term.size(); k++)
							{
								if(non_term[k]->equals(*ins->get_symb()))
								{
									/* Visit this rule */
									sequence.push_back(plan->first.id_plan.context[k+1]);
									break;
								}
							}
						}
					}

					/* Mark the instance */
					computed.push_back(ins);
				}
			}
			/* Compute this equation */
			sequence.push_back(eq->get_id()*(-1));
		}

		all_visit_seqs.push_back(sequence);
	}
}

void Build_visit_sequence::print_all_visit_sequences() const
{
	for(size_t i(0); i < all_visit_seqs.size(); i++)
	{
		cout << "Visit Sequence Nro " << i+1 << ": ";
		for(size_t j(0); j < all_visit_seqs[i].size(); j++)
		{
			cout << all_visit_seqs[i][j];
			if(j < all_visit_seqs[i].size() - 1)
			{
				cout << ", ";
			}
		}
		cout << "." << endl;
	}
}

} /* end namespace */
