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
    eval_mag.translate_mag();

// ROOT
    T node_1;
	node_1.rule_id = 1;
	node_1.parent = NULL;
	
// childs ROOT
    T2 node_20;
	node_20.rule_id = 2;
	node_20.parent = &node_1;

		
    T node_21;
	node_21.rule_id = 1;
	node_21.parent = &node_1;

    T node_22;
	node_22.rule_id = 3;
	node_22.parent = &node_1;

	node_1.childs.push_back(&node_20);
	node_1.childs.push_back(&node_21);
	node_1.childs.push_back(&node_22);
	
// childs of my second childs.
	
    T2 node_210;
	node_210.rule_id = 2;
	node_210.parent = &node_21;

		
    T node_211;
	node_211.rule_id = 3;
	node_211.parent = &node_21;

    T node_212;
	node_212.rule_id = 1;
	node_212.parent = &node_21;

	node_21.childs.push_back(&node_210);
	node_21.childs.push_back(&node_211);
	node_21.childs.push_back(&node_212);	


// childs of thirtd child of my second child.
	
    T2 node_2120;
	node_2120.rule_id = 2;
	node_2120.parent = &node_212;

		
    T node_2121;
	node_2121.rule_id = 3;
	node_2121.parent = &node_212;

    T node_2122;
	node_2122.rule_id = 3;
	node_2122.parent = &node_212;

	node_212.childs.push_back(&node_2120);
	node_212.childs.push_back(&node_2121);
	node_212.childs.push_back(&node_2122);


		
	eval_mag.evaluator_mag(&node_1);

    cout << " After evaluation." << endl;
    cout << node_1.to_string() << endl;
    
    cout << "FIN EVAL_AG" << endl;

    return 0;
}
