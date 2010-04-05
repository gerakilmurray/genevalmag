/**
  *  \file      Eval_mag_proof.cpp
  *  \brief     File of proof for Eval_mag. 
  *  \date      Thu Mar 25 21:04:46 2010
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
*/

#include "Eval_mag.hpp"

using namespace evalmag;


int  f(int j)
{
	return j*5;
}


/**
  * Main method of the Eval_mag.
  */
int main()
{
    Eval_mag eval_mag;
    eval_mag.print_v_seq();

    T node_1;
	node_1.rule_id = 1;
	node_1.parent = NULL;

    T2 node_2;
	node_2.rule_id = 2;
	node_2.parent = &node_1;

    T2 node_3;
	node_3.rule_id = 2;
	node_3.parent =&node_1;

    T2 node_4;
	node_4.rule_id = 2;
	node_4.parent = &node_1;

    T2 node_5;
	node_5.rule_id = 2;
	node_5.parent =&node_1;
		
    T node_21;
	node_21.rule_id = 1;
	node_21.parent = &node_1;

    T2 node_6;
	node_6.rule_id = 2;
	node_6.parent = &node_21;

    T2 node_7;
	node_7.rule_id = 2;
	node_7.parent =&node_21;

    T2 node_8;
	node_8.rule_id = 2;
	node_8.parent = &node_21;

    T2 node_9;
	node_9.rule_id = 2;
	node_9.parent =&node_21;
		
    T node_22;
	node_22.rule_id = 3;
	node_22.parent = &node_21;

	node_1.childs.push_back(&node_2);
	node_1.childs.push_back(&node_3);
	node_1.childs.push_back(&node_4);
	node_1.childs.push_back(&node_5);
	node_1.childs.push_back(&node_21);
	node_1.childs.push_back(&node_21);

	node_21.childs.push_back(&node_6);
	node_21.childs.push_back(&node_7);
	node_21.childs.push_back(&node_8);
	node_21.childs.push_back(&node_9);
	node_21.childs.push_back(&node_22);
	node_21.childs.push_back(&node_22);


		
	eval_mag.evaluator_mag(&node_1);

    cout << " After evaluation." << endl;
    cout << node_1.to_string() << endl;
    
    cout << "FIN EVAL_AG" << endl;

    return 0;
}
