/**
  *  \file      Builder_visit_sequences.h
  *  \brief     Implementation of the methods the Builder_visit_sequences.h.
  *  \date      17/03/2010
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>

#include "../../include/Util/Utilities.h"

#include "../../include/Builders/Builder_visit_sequences.h"

using namespace utilities;

namespace genevalmag
{

const unsigned short LEAVE(0);

/**
  * Contructor empty of Builder_visit_sequences.
  */
Builder_visit_sequences::Builder_visit_sequences
(
	const Builder_plans &builder_plan,
	const Attr_grammar &attribute_grammar
)
	: b_plans(builder_plan),
	  attr_grammar(attribute_grammar)
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
bool ins_attr_computed(const Expr_instance *ins, const vector<Expr_instance> &vec)
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
void get_inherits_of(const Symbol *symb, const vector<Expr_instance> &computed, vector<Expr_instance> &rec_child)
{
	/* For all computed's vector. */
	for(size_t i(0); i < computed.size(); i++)
    {
        if (computed[i].get_symb()->equals(*symb) && computed[i].get_attr()->is_inherit())
        {
        	/* Push in the rec_child vector */
            rec_child.push_back(computed[i]);
            rec_child.back().set_num(0);
        }
    }
}

/**
  * Returns true if the iterator belongs to the vector passed as parameter.
  */
bool belong_it(const map<Key_plan, unsigned short>::const_iterator it, const vector< map<Key_plan, unsigned short>::const_iterator > &vec)
{
	for(size_t i(0); i < vec.size(); i++)
	{
		if(it == vec[i])
		{
			return true;
		}
	}
	return false;
}

/**
  * Merge two vector in the vec_target argument.
  */
void merge_vec(const vector< map<Key_plan, unsigned short>::const_iterator> &vec_source, vector< map<Key_plan, unsigned short>::const_iterator> &vec_targed)
{
	if(vec_targed.size() == 0)
	{
		/* Non necesary merge */
		vec_targed = vec_source;
	}
	else
	{
		/* Merge necesary */
		for(size_t i(0); i < vec_source.size(); i++)
		{
			if(!belong_it(vec_source[i],vec_targed))
			{
				vec_targed.push_back(vec_source[i]);
			}
		}
	}
}

/**
  * Merge two vector in the vec_target argument without the iterator passed as parameter.
  */
void merge_vec_without_plan
(
	const vector< map<Key_plan, unsigned short>::const_iterator> &vec_source,
	vector< map<Key_plan, unsigned short>::const_iterator> &vec_targed,
	const map<Key_plan, unsigned short>::const_iterator &plan
)
{
	if(vec_targed.size() == 0)
	{
		/* Non necesary merge */
		vec_targed = vec_source;
	}
	else
	{
		/* Merge necesary */
		for(size_t i(0); i < vec_source.size(); i++)
		{
			if(!belong_it(vec_source[i], vec_targed) && vec_source[i] != plan)
			{
				vec_targed.push_back(vec_source[i]);
			}
		}
	}
}

/**
  * Converts the vector of iterators over evaluations plans, in their indexs inside of plans uniques.
  */
void plan_family_computed(const vector< map<Key_plan, unsigned short>::const_iterator> &plans_computed, vector<unsigned short> &visit_seq_computed)
{
	for (size_t i(0); i < plans_computed.size(); i++)
	{
		unsigned short index_family(plans_computed[i]->second);
		if (!belong_index(index_family, visit_seq_computed))
		{
			visit_seq_computed.push_back(index_family);
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
	const map<Key_plan, unsigned short>::const_iterator &it_plan,
	vector<Expr_instance> &ins_computed,
	vector< map<Key_plan, unsigned short>::const_iterator > &plans_computed,
	const vector<unsigned short> &v_seq_computed
)
{
	const Order_eval_eq &plan(b_plans.get_plans_uniques()[it_plan->second]);

    bool leaves(false);
    Visit_seq sequence;
    vector<Expr_instance> ins_computed_own;

    const Rule &rule(attr_grammar.get_rule(b_plans.get_context_unique(it_plan->first.id_plan)[0]));

    size_t i(0);
    for(; i < plan.size(); i++)
    {
        const Equation *eq(rule.get_eq(plan[i]));

        const vector<const Expr_instance*> &instances_right_side(eq->get_instance_right_side());

        for(size_t j(0); j < instances_right_side.size(); j++)
		{
			const Expr_instance *ins(instances_right_side[j]);

			if((ins->get_symb()->equals(*rule.get_left_symbol())) &&
			   (ins->get_num() == 0) &&
			   (ins->get_attr()->is_inherit()) &&
			   (!ins_attr_computed(ins, ins_computed)))
			/* Non computed in superior context, need leave to computed. */
			{
				sequence.push_back(LEAVE);
				leaves = true;
				break;
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

					/* Generate visits */
					map<Key_plan_project, unsigned short >::const_iterator it_plan_proj;

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
					/* Generate the recursion to non computed child. */
					vector <unsigned short> v_seq_child;
					for(map < Key_plan, unsigned short >::const_iterator it(b_plans.get_plans().begin()); it != b_plans.get_plans().end(); it++)
					{
						if(!belong_it(it, plans_computed) && !belong_index(it->second, v_seq_computed) && it->second !=it_plan->second)
						{
							/* Plan to recurse: it */
							const Rule &rule_child(attr_grammar.get_rule(b_plans.get_context_unique(it->first.id_plan)[0]));
							if ((rule_child.get_left_symbol()->equals(*ins->get_symb())) &&
								(it->first.plan == it_plan_proj->second))
							/* The plan to launch the recursion has the need context. */
							{
								vector<Expr_instance> ins_computed_child;
								get_inherits_of(ins->get_symb(), ins_computed_own, ins_computed_child);
								vector< map<Key_plan, unsigned short>::const_iterator > p_computed_child;
								/* Adds as computed the current plan. */
								p_computed_child.push_back(it_plan);
								merge_vec(plans_computed, p_computed_child);

								gen_visit_seq(it, ins_computed_child, p_computed_child, v_seq_child);

								/* Removes current plan as computed. */
								merge_vec_without_plan(p_computed_child, plans_computed, it_plan);

								/* Update information_computed plans. */
								plan_family_computed(plans_computed, v_seq_child);

								/* Saves all instances calculated for the visit. */
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
			/* Save computed instance. */
			ins_computed_own.push_back(*ins);
		}

		if (!leaves)
		{
			/* Compute this equation */
			sequence.push_back(eq->get_id()*(-1));

			/* Mark the instance */
			const Expr_instance *l_v(eq->get_l_value());
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
    if (!belong_index(it_plan->second, v_seq_computed))
    {
    	update_visit_sequence(sequence, it_plan->second);
    }

    if(i == plan.size())
    /* Saves without conflicted states. */
    {
        plans_computed.push_back(it_plan);
    }
    return true;
}

/**
  * Update the visit sequence generate, mixing with pre-generated
  * visit sequences.
  */
void Builder_visit_sequences::update_visit_sequence(const Visit_seq &sequence, const size_t i_plan)
{
    size_t i(0);
    size_t j(0);
    /* Compares the two sequences for resolve conflitic sequence. */
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
    /* Check sequence leaves and save visit_sequence. */
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
    /* Only saves at most one leave */
    assert(cant_leaves_copy<2);
}

/**
  * Generates a visit sequence for each evaluation plan.
  */
bool Builder_visit_sequences::generate_visit_sequences()
{
    for(size_t i(0); i < b_plans.get_plans_uniques().size(); i++)
    {
    	Visit_seq v_s;
        all_visit_seqs.push_back(v_s);
    }

    vector <unsigned short> visit_seq_computed;
    vector <map<Key_plan, unsigned short>::const_iterator> plans_computed_all;
    /* For all plans */
	for(map < Key_plan, unsigned short >::const_iterator it(b_plans.get_plans().begin()); it != b_plans.get_plans().end(); it++)
    {
        const Rule &rule(attr_grammar.get_rule(b_plans.get_context_unique(it->first.id_plan)[0]));
        if (rule.get_left_symbol()->equals(*attr_grammar.get_initial_symb()))
        {
        	/* This plan is belong a initial symbol (initial rule). */
            if(!belong_index(it->second, visit_seq_computed))
            {
                vector<Expr_instance> ins_computed;
                vector< map<Key_plan, unsigned short>::const_iterator > plans_computed;
                merge_vec(plans_computed_all, plans_computed);
				gen_visit_seq(it, ins_computed, plans_computed, visit_seq_computed);
				merge_vec(plans_computed, plans_computed_all);
				plan_family_computed(plans_computed, visit_seq_computed);
            }
        }
    }
	cout << "* Build visit sequences ---- [  OK  ]" << endl;
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
