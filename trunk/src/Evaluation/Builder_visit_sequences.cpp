/**
  *  \file      Builder_visit_sequences.h
  *  \brief     Implementation of the methods the Builder_visit_sequences.h.
  *  \date      17/03/2010
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>

#include "../Util/Utilities.h"

#include "Builder_visit_sequences.h"

using namespace utilities;

namespace genevalmag
{

const unsigned short LEAVE(0);

/**
  * Contructor empty of Builder_visit_sequences.
  */
Builder_visit_sequences::Builder_visit_sequences()
{
}

/**
  * Destructor of Builder_visit_sequences.
  */
Builder_visit_sequences::~Builder_visit_sequences()
{
}

/**
  * Searches this instance on the list passed as parameter.
  * If found the instance return true.
  */
bool ins_attr_computed(const Ast_instance *ins, const vector<Ast_instance> &vec)
{
    for(size_t i(0); i < vec.size(); i++)
    {
        if(vec[i].equals(ins))
        {
            return true;
        }
    }
    return false;
}

/**
  * Obtains the instances of inherit attributes that this symbol.
  */
void get_inherits_of(const Symbol *symb, const vector<Ast_instance> &computed, vector<Ast_instance> &rec_child)
{
    for(size_t i(0); i < computed.size(); i++)
    {
        if (computed[i].get_symb()->equals(*symb) && computed[i].get_attr()->is_inherit())
        {
            rec_child.push_back(computed[i]);
            rec_child.back().set_num(0);
        }
    }
}

void merge_vec(const vector<unsigned short> &vec_source, vector<unsigned short> &vec_targed)
{
	if(vec_targed.size() == 0)
	{
		vec_targed = vec_source;
	}
	else
	{
		for(size_t i(0); i < vec_source.size(); i++)
		{
			if(!belong_index(vec_source[i],vec_targed))
			{
				vec_targed.push_back(vec_source[i]);
			}
		}
	}
}

/**
  * Generates recursively the visit sequence, navigating the tree as
  * indicated by the plans, visiting the children, returning to the
  * parent or generating a compute attribute.
  */
bool Builder_visit_sequences::gen_visit_seq
(
	const Attr_grammar &attr_grammar,
	const Builder_plans &b_plans,
	const map<Key_plan, Order_eval_eq>::const_iterator &it_plan,
	vector<Ast_instance> &ins_computed,
	vector<unsigned short> &plans_computed,
	const vector<unsigned short> &v_seq_computed
)
{
	unsigned short i_plan(b_plans.get_index_plan(it_plan));

    short leaves(0);
    Visit_seq sequence;
    vector<Ast_instance> ins_computed_own;

    const Rule &rule(attr_grammar.get_rule(it_plan->first.id_plan[0]));

    size_t i(0);
    for(; i < it_plan->second.size(); i++)
    {
        const Equation *eq(rule.get_eq(it_plan->second[i]));

        const vector<const Ast_instance*> &instances_right_side(eq->get_instance_right_side()); /* ver copia tmp */

        for(size_t j(0); j < instances_right_side.size(); j++)
		{
			const Ast_instance *ins(instances_right_side[j]);

			if((ins->get_symb()->equals(*rule.get_left_symbol())) &&
			   (ins->get_num() == 0) &&
			   (ins->get_attr()->is_inherit()) &&
			   (!ins_attr_computed(ins, ins_computed)))
			/* Non computed in superior context, need leave to computed. */
			{
				sequence.push_back(LEAVE);
				leaves++;
			}
			else
			{
				/* The attr symbols belongs to some right side symbol of the rule. */
				if((ins->get_attr()->is_synthetize()) &&
				   (!ins_attr_computed(ins, ins_computed_own)))
				/* Non computed in this context, proceed to compute. */
				{
					vector<const Symbol*> non_terminals(rule.get_non_terminals_right_side());

					short index_ins(ins->get_num());
					if(ins->get_symb()->equals(*rule.get_left_symbol()))
					{
						/* It should consider that the left instance has zero index. */
						index_ins--;
					}

					map<Key_plan_project, Order_eval_eq >::const_iterator it_plan_proj;

					for(size_t k(0); k < non_terminals.size(); k++)
					{
						if(non_terminals[k]->equals(*ins->get_symb()))
						{
							if (index_ins == 0)
							{
								/* Get project plan to find the plan with this order sup. */
								Key_plan_project key_p;
								key_p.id_plan_project = it_plan->first;
								key_p.symbol_project = ins->get_symb();
								key_p.index_ocurrence = k;
								it_plan_proj = (b_plans.get_plan_project(key_p));

								/* Visit this child. */
								sequence.push_back(k + 1);
							}
							index_ins--;
						}
					}

					vector <unsigned short> v_seq_child;
					for(map < Key_plan, Order_eval_eq >::const_iterator it(b_plans.get_plans().begin()); it != b_plans.get_plans().end(); it++)
					{
						unsigned short i_child(b_plans.get_index_plan(it));
						if((!belong_index(i_child, plans_computed)) && (it != it_plan))
						{
							const Rule &rule_child(attr_grammar.get_rule(it->first.id_plan[0]));

							if ((rule_child.get_left_symbol()->equals(*ins->get_symb())) &&
								(it->first.plan == it_plan_proj->second))
							{
								vector<Ast_instance> ins_computed_child;
								get_inherits_of(ins->get_symb(), ins_computed_own, ins_computed_child);

								vector<unsigned short> p_computed_child;
								p_computed_child.push_back(i_plan);
								merge_vec(plans_computed, p_computed_child);
								gen_visit_seq(attr_grammar, b_plans, it, ins_computed_child, p_computed_child, v_seq_child);
								merge_vec(p_computed_child, v_seq_child);

								for(size_t i_rec(0); i_rec < ins_computed_child.size(); i_rec++)
								{
									if(ins_computed_child[i_rec].get_attr()->is_synthetize())
									{
										ins_computed_child[i_rec].set_num(ins->get_num());
										ins_computed_own.push_back(ins_computed_child[i_rec]);
									}
								}
							}
						}
					}
				}
			}
			ins_computed_own.push_back(*ins);
		}

		/* Compute this equation */
		sequence.push_back(eq->get_id()*(-1));

		if (leaves < 1)
		{
			/* Mark the instance */
			const Ast_instance *l_v(eq->get_l_value());
			if (l_v->get_attr()->is_synthetize())
			{
				ins_computed.push_back(*l_v);
			}
			ins_computed_own.push_back(*l_v);
		}
		else
		{
			/* Cuts the generation unstable visit seq . */
			break;
		}
    }

    if (!belong_index(i_plan, v_seq_computed))
    {
    	save_visit_sequence(sequence, i_plan);
    }

    if(i == it_plan->second.size())
    /* Se guardo sin estados conflictivos. */
    {
        plans_computed.push_back(i_plan);
    }
    return true;
}

/**
  * Saves the visit sequence generate, mixing with pre-generated
  * visit sequences.
  */
void Builder_visit_sequences::save_visit_sequence(const Visit_seq &sequence, const size_t i_plan)
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

/**
  * Generates a visit sequence for each evaluation plan.
  */
bool Builder_visit_sequences::generate_visit_sequences(const Attr_grammar &attr_grammar, const Builder_plans &b_plans)
{
    for(size_t i(0); i < b_plans.get_plans().size(); i++)
    {
    	Visit_seq v_s;
        all_visit_seqs.push_back(v_s);
    }

    vector <unsigned short> visit_seq_computed;
	for(map < Key_plan, Order_eval_eq >::const_iterator it(b_plans.get_plans().begin()); it != b_plans.get_plans().end(); it++)
    {
        const Rule &rule(attr_grammar.get_rule(it->first.id_plan[0]));
        if (rule.get_left_symbol()->equals(*attr_grammar.get_initial_symb()))
        {
            unsigned short plan_inic(b_plans.get_index_plan(it));
            if(!belong_index(plan_inic, visit_seq_computed))
            {
                vector<Ast_instance> ins_computed;
                vector<unsigned short> plans_computed;
				gen_visit_seq(attr_grammar, b_plans, it, ins_computed, plans_computed, visit_seq_computed);
				merge_vec(plans_computed, visit_seq_computed);
            }
        }
    }
    return true;
}

/**
  * Returns the vector with all visit sequences generates.
  */
const vector<Visit_seq> &Builder_visit_sequences::get_visit_seq() const
{
    return all_visit_seqs;
}

/**
  * Print in console, all visit sequences generates.
  */
void Builder_visit_sequences::print_all_visit_sequences() const
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

} /* end genevalmag */
