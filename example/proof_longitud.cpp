/**
  *  \file      Eval_mag_proof.cpp
  *  \brief     File of proof for Eval_mag. 
  *  \date      Thu Mar 25 21:04:46 2010
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
*/

#include "Eval_mag.hpp"

using namespace evalmag;

/**
  * Main method of the Eval_mag.
  */
int main()
{
    Eval_mag eval_mag;
    eval_mag.print_v_seq();
    eval_mag.translate_mag(0);
    eval_mag.translate_mag(1);
    eval_mag.translate_mag(2);
    eval_mag.translate_mag(3);
    eval_mag.translate_mag(4);
    eval_mag.translate_mag(5);

    T node_1;
	node_1.rule_id = 1;
	node_1.parent = NULL;

    T node_2;
	node_2.rule_id = 1;
	node_2.parent = &node_1;

    T node_3;
	node_3.rule_id = 1;
	node_3.parent =&node_2;

    T node_4;
	node_4.rule_id = 1;
	node_4.parent = &node_3;

    T node_5;
	node_5.rule_id = 1;
	node_5.parent = &node_4;

    T node_6;
	node_6.rule_id = 1;
	node_6.parent = &node_5;

    T node_7;
	node_7.rule_id = 1;
	node_7.parent = &node_6;

    T node_8;
	node_8.rule_id = 1;
	node_8.parent =&node_7;

    T node_9;
	node_9.rule_id = 1;
	node_9.parent = &node_8;

    T node_10;
	node_10.rule_id = 1;
	node_10.parent = &node_9;

    T node_11;
	node_11.rule_id = 1;
	node_11.parent = &node_10;
	
	    T node_12;
	node_12.rule_id = 1;
	node_12.parent = &node_11;

    T node_13;
	node_13.rule_id = 1;
	node_13.parent =&node_12;

    T node_14;
	node_14.rule_id = 1;
	node_14.parent = &node_13;

    T node_15;
	node_15.rule_id = 1;
	node_15.parent = &node_14;

    T node_16;
	node_16.rule_id = 1;
	node_16.parent = &node_15;

    T node_17;
	node_17.rule_id = 1;
	node_17.parent = &node_16;

    T node_18;
	node_18.rule_id = 1;
	node_18.parent =&node_17;

    T node_19;
	node_19.rule_id = 1;
	node_19.parent = &node_18;

    T node_20;
	node_20.rule_id = 1;
	node_20.parent = &node_19;

    T node_21;
	node_21.rule_id = 1;
	node_21.parent = &node_20;
	
    T node_22;
	node_22.rule_id = 2;
	node_22.parent = &node_21;

	node_1.childs.push_back(&node_2);
	node_2.childs.push_back(&node_3);
	node_3.childs.push_back(&node_4);
	node_4.childs.push_back(&node_5);
	node_5.childs.push_back(&node_6);
	node_6.childs.push_back(&node_7);
	node_7.childs.push_back(&node_8);
	node_8.childs.push_back(&node_9);
	node_9.childs.push_back(&node_10);
	node_10.childs.push_back(&node_11);
	node_11.childs.push_back(&node_12);
	node_12.childs.push_back(&node_13);
	node_13.childs.push_back(&node_14);
	node_14.childs.push_back(&node_15);
	node_15.childs.push_back(&node_16);
	node_16.childs.push_back(&node_17);
	node_17.childs.push_back(&node_18);
	node_18.childs.push_back(&node_19);
	node_19.childs.push_back(&node_20);
	node_20.childs.push_back(&node_21);
	node_21.childs.push_back(&node_22);
		
	eval_mag.evaluator_mag(&node_1);

    cout << " After evaluation." << endl;
    cout << node_1.to_string() << endl;
    
    cout << "FIN EVAL_AG" << endl;

    return 0;
}
