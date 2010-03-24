/**
  *  \file		Build_visit_sequence.h
  *  \brief		Implementation of the methods the Build_visit_sequence.h.
  *  \date		17/03/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>

#include "Build_visit_sequence.h"

namespace genevalmag
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

bool Build_visit_sequence::generate_seq_visit(const Attr_grammar &attr_grammar, const map < Key_plan, Order_eval_eq > &plans)
{
	vector< pair < Key_plan, Order_eval_eq > > planes;

	for(map < Key_plan, Order_eval_eq >::const_iterator it(plans.begin()); it != plans.end(); it++)
	{
		pair<Key_plan, Order_eval_eq> p(it->first, it->second);
		planes.push_back(p);
		Visit_seq v_s;
		all_visit_seqs.push_back(v_s);
	}

	for(size_t i(0); i < planes.size(); i++)
	{
		const Rule& rule(attr_grammar.get_rule(planes[i].first.id_plan.context[0]));
		if (rule.get_left_symbol()->equals(*attr_grammar.get_initial_symb()))
		{
			vector<const Ast_instance*> ins_computed;
			gen_seq_visit(attr_grammar, planes, i, ins_computed);
		}
	}
	return true;
}

void purge_computed(const Symbol &symb, const vector<const Ast_instance*> &computed, vector<const Ast_instance*> &rec_child)
{
	for(size_t i(0); i < computed.size(); i++)
	{
		if (computed[i]->get_symb()->equals(symb) && computed[i]->get_attr()->is_inherit())
		{
			rec_child.push_back(computed[i]);
		}
	}
}

void Build_visit_sequence::save_visit_sequence(const Visit_seq &sequence, const size_t i_plan)
{
	size_t i(0);
	size_t j(0);
	while(i < sequence.size() && j < all_visit_seqs[i_plan].size())
	{
		if(all_visit_seqs[i_plan][j] == sequence[i])
		{
			i++;
			j++;
		}
		else
		{
			if(all_visit_seqs[i_plan][j] == 0)
			{
				j++;
			}
		}
	}

	unsigned short cant_leaves_copy(0);
	for(size_t index(i); index < sequence.size(); index++)
	{
		if(sequence[index] == 0)
		{
			cant_leaves_copy++;
		}
		if(cant_leaves_copy > 1)
		{
			break;
		}
		all_visit_seqs[i_plan].push_back(sequence[index]);
	}
}

bool Build_visit_sequence::gen_seq_visit(const Attr_grammar &attr_grammar, const vector < pair < Key_plan, Order_eval_eq > > &plans, size_t i_plan, vector<const Ast_instance*> &computed)
{
	bool leaves(false);
	Visit_seq sequence;
	vector<const Ast_instance*> computed_own;

	const Rule& rule(attr_grammar.get_rule(plans[i_plan].first.id_plan.context[0]));

	for(size_t i(0); i < plans[i_plan].second.size(); i++)
	{
		const Equation *eq(rule.get_eq(plans[i_plan].second[i]));

		vector<const Ast_instance*> instances_right_side;
		eq->inorder_only_instance(eq->get_r_value(), instances_right_side);

		for(size_t j(0); j < instances_right_side.size(); j++)
		{
			const Ast_instance* ins(instances_right_side[j]);

			if(ins->get_symb()->equals(*rule.get_left_symbol()))
			{
				if(ins->get_attr()->is_inherit())
				{
					if(!ins_attr_computed(ins, computed))
					{
						sequence.push_back(0);
						leaves = true;
					}
				}
			}
			else
			{
				/* The attr symbols belong to right side of the rule */
				if(ins->get_attr()->is_synthetize())
				{
					if(!ins_attr_computed(ins, computed_own))
					{
						vector<const Symbol*> non_term(rule.get_non_terminals_right_side());
						for(size_t k(0); k < non_term.size(); k++)
						{
							if(non_term[k]->equals(*ins->get_symb()))
							{
								/* Visit this rule */
								sequence.push_back(plans[i_plan].first.id_plan.context[k+1]);

								for(size_t p(0); p < plans.size(); p++)
								{
									if ((plans[p].first.id_plan.father == rule.key()) &&
										(plans[p].first.id_plan.context[0] == plans[i_plan].first.id_plan.context[k+1]))
									{
										vector<const Ast_instance*> rec_child;
										purge_computed(*ins->get_symb(),computed_own,rec_child);
										gen_seq_visit(attr_grammar, plans, p, rec_child);

										for(size_t i(0); i < rec_child.size(); i++)
										{
											if(rec_child[i]->get_attr()->is_synthetize())
											{
												computed_own.push_back(rec_child[i]);
											}
										}
									}
								}
							}
						}
					}
				}
			}
			computed_own.push_back(ins);
		}
		/* Compute this equation */
		sequence.push_back(eq->get_id()*(-1));

		/* Mark the instance */
		const Ast_instance *l_v(eq->get_l_value());
		if (l_v->get_attr()->is_synthetize() && !leaves)
		{
			computed.push_back(l_v);
		}
		computed_own.push_back(l_v);
	}

	save_visit_sequence(sequence, i_plan);
	return true;
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

const vector<Visit_seq> &Build_visit_sequence::get_visit_seq() const
{
	return all_visit_seqs;
}

} /* end namespace */
