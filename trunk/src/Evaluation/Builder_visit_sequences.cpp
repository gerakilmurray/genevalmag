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
					const vector < pair < Key_plan, Order_eval_eq > > &plans,
					size_t i_plan,
					vector<Ast_instance> &computed,
					vector<unsigned short> &plans_computed_f,
					const vector<unsigned short> & v_seq_computed_f
			)
{
    bool leaves(false);
    Visit_seq sequence;
    vector<Ast_instance> computed_own;

    const Rule& rule(attr_grammar.get_rule(plans[i_plan].first.id_plan[0]));

    for(size_t i(0); i < plans[i_plan].second.size(); i++)
    {
        const Equation *eq(rule.get_eq(plans[i_plan].second[i]));

        vector<const Ast_instance*> instances_right_side;
//        instances_right_side = eq->inorder_only_instance(); ARREGLAR!!!!!!!!!!!!!!!
        eq->inorder_only_instance(eq->get_r_value(), instances_right_side);

        for(size_t j(0); j < instances_right_side.size(); j++)
        {
            const Ast_instance *ins(instances_right_side[j]);

            if((ins->get_symb()->equals(*rule.get_left_symbol())) &&
               (ins->get_num() == 0) &&
               (ins->get_attr()->is_inherit()) &&
			   (!ins_attr_computed(ins, computed)))
			/* Non computed in superior context, need leave to computed. */
			{
            	cout << "LEAVE"<<endl;
				sequence.push_back(LEAVE);
				leaves = true;
			}
            else
            {
                /* The attr symbols belongs to some right side symbol of the rule. */
                if((ins->get_attr()->is_synthetize()) &&
                   (!ins_attr_computed(ins, computed_own)))
                /* Non computed in this context, proceed to compute. */
				{
                	cout << "Sinte y no comp"<<endl;
                	short index_ins(ins->get_num());
                	if(ins->get_symb()->equals(*rule.get_left_symbol()))
					{
                		cout << "Igual al left resta uno"<<endl;
						/* It should consider that the left instance has zero index. */
						index_ins--;
					}

                    vector <unsigned short> v_seq_child;
                    for(size_t k(0); k < plans.size(); k++)
                    {
                    	cout << "cicla en los planes"<<endl;
                        const Rule &rule_child(attr_grammar.get_rule(plans[k].first.id_plan[0]));
                        if (rule_child.get_left_symbol()->equals(*ins->get_symb()))
                        {
                        	cout << "left de regla igual al simbol de la ins"<<endl;
                        	if (index_ins == 0)
                        	{
                        		cout << "index ins es CERO"<<endl;
								for(size_t i_c(1); i_c < plans[k].first.id_plan.size(); i_c++)
								{
									if(plans[k].first.id_plan[i_c] == rule_child.key())
									{
										cout << "Contexto igual al rule key"<<endl;
										/* Visit this child. */
										sequence.push_back(i_c);

										vector<Ast_instance> ins_computed_child;
										get_inherits_of(ins->get_symb(), computed_own, ins_computed_child);

										vector<unsigned short> p_computed_child;
										gen_visit_seq(attr_grammar, plans, k, ins_computed_child, p_computed_child, v_seq_child);

										merge_vec(p_computed_child, v_seq_child);

										for(size_t i_rec(0); i_rec < ins_computed_child.size(); i_rec++)
										{
											if(ins_computed_child[i_rec].get_attr()->is_synthetize())
											{
												cout << "rec child es sintetizado"<<endl;
												ins_computed_child[i_rec].set_num(ins->get_num());
												computed_own.push_back(ins_computed_child[i_rec]);
											}
										}


									}
								}
                        	}
                        	index_ins--;
                        }
                    }

//					vector<const Symbol*> non_terminals(rule.get_non_terminals_right_side());
//
//					short index_ins(ins->get_num());
//					if(ins->get_symb()->equals(*rule.get_left_symbol()))
//					{
//						/* It should consider that the left instance has zero index. */
//						index_ins--;
//					}
//
//					vector<unsigned short> plans_computed_own;
//
//					for(size_t k(0); k < non_terminals.size(); k++)
//					{
//						if(non_terminals[k]->equals(*ins->get_symb()))
//						{
//							if (index_ins == 0)
//							{
//								/* Visit this child with these rule */
//								sequence.push_back(k+1);
//
//								for(size_t index_p(0); index_p < plans.size(); index_p++)
//								{
//									unsigned short plan_num_child(index_p+1);
//									if(!belong_index(plan_num_child, plans_computed_f))
//									{
//										Ast_instance ins_eq(*ins);
//										ins_eq.set_num(0);
//										vector<unsigned short> context_visit;
//										context_visit.push_back(plans[i_plan].first.id_plan[k+1]);
//										unsigned short index_num(attr_grammar.get_index_eq_with_context(&ins_eq, context_visit));
//
//										if ((plans[index_p].first.id_plan[0] == plans[i_plan].first.id_plan[k+1]) &&
//											(plans[index_p].first.plan[0] == index_num))
//										{
//											vector<Ast_instance> rec_child;
//											get_inherits_of(ins->get_symb(), computed_own, rec_child);
//
//											gen_visit_seq(attr_grammar, plans, index_p, rec_child, plans_computed_f, v_seq_computed);
//
//											for(size_t i_rec(0); i_rec < rec_child.size(); i_rec++)
//											{
//												if(rec_child[i_rec].get_attr()->is_synthetize())
//												{
//													rec_child[i_rec].set_num(ins->get_num());
//													computed_own.push_back(rec_child[i_rec]);
//												}
//											}
//										}
//									}
//								}
//								break;
//							}
//							index_ins--;
//						}
				}
            }
            computed_own.push_back(*ins);
        }

        /* Compute this equation */
        sequence.push_back(eq->get_id()*(-1));

        if (!leaves)
        {
			/* Mark the instance */
			const Ast_instance *l_v(eq->get_l_value());
			if (l_v->get_attr()->is_synthetize())
			{
				computed.push_back(*l_v);
			}
			computed_own.push_back(*l_v);
        }
        else
        {
        	break;
        }
    }

    cout << "seq ";
    for(size_t jj(0); jj < sequence.size(); jj++)
    	cout << sequence[jj] << ",";
    cout << endl;


    if (!belong_index(i_plan, v_seq_computed_f))
    {
    	cout << "entro"<< endl;
    	save_visit_sequence(sequence, i_plan);
    }

    if(!leaves)
    /* Se guardo sin estados conflictivos. */
    {
        plans_computed_f.push_back(i_plan);
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
bool Builder_visit_sequences::generate_visit_sequences(const Attr_grammar &attr_grammar, const map < Key_plan, Order_eval_eq > &plans)
{
    vector< pair < Key_plan, Order_eval_eq > > planes;

    for(map < Key_plan, Order_eval_eq >::const_iterator it(plans.begin()); it != plans.end(); it++)
    {
        pair<Key_plan, Order_eval_eq> p(it->first, it->second);
        planes.push_back(p);
        Visit_seq v_s;
        all_visit_seqs.push_back(v_s);
    }

    vector <unsigned short> visit_seq_computed;
    for(size_t i(0); i < planes.size(); i++)
    {
        const Rule &rule(attr_grammar.get_rule(planes[i].first.id_plan[0]));
        if (rule.get_left_symbol()->equals(*attr_grammar.get_initial_symb()))
        {
            vector<Ast_instance> ins_computed;
            vector<unsigned short> plans_computed;
            gen_visit_seq(attr_grammar, planes, i, ins_computed, plans_computed, visit_seq_computed);

            merge_vec(plans_computed, visit_seq_computed);
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
