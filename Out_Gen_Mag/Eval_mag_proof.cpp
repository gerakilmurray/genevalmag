/**
  *  \file      Eval_mag_proof.cpp
  *  \brief     File of proof for Eval_mag. 
  *  \date      Thu Mar 25 21:04:46 2010
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
*/

#include <vector>

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


    S node_s1;
	node_s1.rule_id = 1;
	node_s1.parent = NULL;

	X node_s1_x;
	node_s1_x.rule_id = 4;
	node_s1_x.parent = &node_s1;

	Y node_s1_y2;
	node_s1_y2.rule_id = 2;
	node_s1_y2.parent = &node_s1;

	Z node_s1_z;
	node_s1_z.rule_id = 5;
	node_s1_z.parent = &node_s1;
	
	//X node_s1_x1;
	//node_s1_x1.rule_id = 4;
	//node_s1_x1.parent = &node_s1;

	Y node_s1_z_y3;
	node_s1_z_y3.rule_id = 2;
	node_s1_z_y3.parent = &node_s1_z;

	node_s1.childs.push_back(&node_s1_x);
	node_s1.childs.push_back(&node_s1_y2);
	node_s1.childs.push_back(&node_s1_z);
	//node_s1.childs.push_back(&node_s1_x1);

	node_s1_z.childs.push_back(&node_s1_z_y3);
    
    
    eval_mag.evaluator_mag(&node_s1);

    cout << " After evaluation." << endl;
    cout << node_s1.to_string() << endl;
    
    cout << "FIN EVAL_AG" << endl;

    return 0;
}
