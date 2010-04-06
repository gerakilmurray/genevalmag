/**
  *  \file      Build_visit_sequence.h
  *  \brief     Implementation of the methods the Build_visit_sequence.h.
  *  \date      17/03/2010
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>

#include "../Util/Utilities.h"

#include "Build_visit_sequence.h"

using namespace utilities;

namespace genevalmag
{

const unsigned short LEAVE(0);

/**
  * Contructor empty of Build_visit_sequence.
  */
Build_visit_sequence::Build_visit_sequence()
{
}

/**
  * Destructor of Build_visit_sequence.
  */
Build_visit_sequence::~Build_visit_sequence()
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
void get_inherits_of(const Symbol &symb, const vector<Ast_instance> &computed, vector<Ast_instance> &rec_child)
{
    for(size_t i(0); i < computed.size(); i++)
    {
        if (computed[i].get_symb()->equals(symb) && computed[i].get_attr()->is_inherit())
        {
            rec_child.push_back(computed[i]);
            //rec_child.back().set_num(0);
        }
    }
}

/**
  * Generates recursively the visit sequence, navigating the tree as
  * indicated by the plans, visiting the children, returning to the
  * parent or generating a compute attribute.
  */
bool Build_visit_sequence::gen_seq_visit(const Attr_grammar &attr_grammar, const vector < pair < Key_plan, Order_eval_eq > > &plans, size_t i_plan, vector<Ast_instance> &computed, vector<unsigned short> &plans_computed, const vector<unsigned short> & v_seq_computed)
{
	cout << "plan  ";
	for (size_t k(0);k<plans_computed.size();k++)
	{
		cout << plans_computed[k] << ", ";
	}
	cout << endl;

    bool leaves(false);
    Visit_seq sequence;
    vector<Ast_instance> computed_own;

//    unsigned short plan_num((i_plan+1) * 100);
    unsigned short plan_num(i_plan+1);
//    if(!belong_index(plan_num,plans_computed))
//    {
    	plans_computed.push_back(plan_num);
    	cout << "current_plan ------->  "<< plan_num;
//    }
    const Rule& rule(attr_grammar.get_rule(plans[i_plan].first.id_plan[0]));

    for(size_t i(0); i < plans[i_plan].second.size(); i++)
    {
        const Equation *eq(rule.get_eq(plans[i_plan].second[i]));


        vector<const Ast_instance*> instances_right_side;
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
				sequence.push_back(LEAVE);
				leaves = true;
			}
            else
            {
                cout << "  buscando esta instancia " << eq->get_l_value()->to_string() << endl;
                cout << ins->to_string() << endl;
                /* The attr symbols belongs to some right side symbol of the rule. */
                if(ins->get_attr()->is_synthetize())
                {
                    if(!ins_attr_computed(ins, computed_own))
                    /* Non computed in this context, proceed to compute. */
                    {
                        vector<const Symbol*> non_terminals(rule.get_non_terminals_right_side());

                        short index_ins(ins->get_num());
                        if(ins->get_symb()->equals(*rule.get_left_symbol()))
						{
							/* It should consider that the left instance has zero index. */
                        	index_ins--;
						}

                        for(size_t k(0); k < non_terminals.size(); k++)
                        {
                        	if(non_terminals[k]->equals(*ins->get_symb()))
                            {
                        		if (index_ins == 0)
                        		{
									/* Visit this child with these rule */
									sequence.push_back(k+1);
									for(size_t index_p(0); index_p < plans.size(); index_p++)
									{
//										unsigned short plan_num_child(((i_plan+1) * 100) + (index_p+1));
										unsigned short plan_num_child(index_p+1);
										if(!belong_index(plan_num_child, plans_computed))
										{
											Ast_instance ins_eq(*ins);
											ins_eq.set_num(0);
											vector<unsigned short> context_visit;
											context_visit.push_back(plans[i_plan].first.id_plan[k+1]);
											unsigned short index_num(attr_grammar.get_index_eq_with_context(&ins_eq, context_visit));

											if ((plans[index_p].first.id_plan[0] == plans[i_plan].first.id_plan[k+1]) &&
												(plans[index_p].first.plan[0] == index_num))
											{
//												plans_computed.push_back(plan_num_child);
												//cout << "entro " << plan_num_child << endl;
												vector<Ast_instance> rec_child;
												get_inherits_of(*ins->get_symb(), computed_own, rec_child);

												gen_seq_visit(attr_grammar, plans, index_p, rec_child, plans_computed, v_seq_computed);

												if(ins->get_symb()->get_name().compare("Y")==0)
												{
													cout<<"\n---------------------------------------rec_Y ";
													for(size_t i_rec(0); i_rec < rec_child.size(); i_rec++)
													{
														cout<< rec_child[i_rec].to_string() <<",";
													}
													cout<<endl;
												}

												for(size_t i_rec(0); i_rec < rec_child.size(); i_rec++)
												{
													if(rec_child[i_rec].get_attr()->is_synthetize())
													{
														rec_child[i_rec].set_num(ins->get_num());
														computed_own.push_back(rec_child[i_rec]);
													}
												}
											}
										}
									}
									break;
                        		}
								index_ins--;
                            }
                        }
                    }
                }
            }
            computed_own.push_back(*ins);
        }
        /* Compute this equation */
        sequence.push_back(eq->get_id()*(-1));

        /* Mark the instance */
        const Ast_instance * l_v(eq->get_l_value());
        if (l_v->get_attr()->is_synthetize() && !leaves)
        {
        	computed.push_back(*l_v);
        }
        computed_own.push_back(*l_v);

//    	cout << "computed  "<< l_v->to_string() << endl;
    }

    if (!belong_index(i_plan+1,v_seq_computed))
    {
    	save_visit_sequence(sequence, i_plan);
    }
    return true;
}

/**
  * Saves the visit sequence generate, mixing with pre-generated
  * visit sequences.
  */
void Build_visit_sequence::save_visit_sequence(const Visit_seq &sequence, const size_t i_plan)
{
//	cout<<"plan"<<i_plan<<endl;
//	for (size_t k(0); k<sequence.size();k++)
//	{
//		cout << "seq  " << sequence[k] << endl;
//	}

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

    vector <unsigned short> visit_seq_computed;
    for(size_t i(0); i < planes.size(); i++)
    {
        const Rule &rule(attr_grammar.get_rule(planes[i].first.id_plan[0]));
        if (rule.get_left_symbol()->equals(*attr_grammar.get_initial_symb()))
        {
            vector<Ast_instance> ins_computed;
            vector<unsigned short> plans_computed;
            gen_seq_visit(attr_grammar, planes, i, ins_computed, plans_computed, visit_seq_computed);
//            for (size_t k(0);k<plans_computed.size();k++)
//            {
//            	cout << "plan  " << plans_computed[k] << endl;
//            }
            visit_seq_computed = plans_computed;

        }
    }
    return true;
}

/**
  * Returns the vector with all visit sequences generates.
  */
const vector<Visit_seq> &Build_visit_sequence::get_visit_seq() const
{
    return all_visit_seqs;
}

/**
  * Print in console, all visit sequences generates.
  */
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

} /* end genevalmag */
