/**
  *  \file      Eval_mag_proof.cpp
  *  \brief     File of proof for Eval_mag. 
  *  \date      Thu Mar 25 21:04:46 2010
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
*/

#include <vector>
#include <iostream>

#include "maggen.hpp"

using namespace evalmag;

/**
  * Main method of the Eval_mag.
  */
int main()
{
    maggen eval_mag;
    eval_mag.print_v_seq();
	eval_mag.translate_mag();

/*    M root(1);
    E node_1(2);
    root.add(&node_1);
    
    E node_2(4);
    E node_3(7);
    node_1.add(&node_2).add(&node_3);
    
    E node_4(8);
    E node_5(8);
    node_2.add(&node_4).add(&node_5);
    
    E node_6(8);
    node_3.add(&node_6);
    
    num node_7(11);
    num node_8(9);
    num node_9(10);
    node_4.add(&node_7);
    node_5.add(&node_8);
    node_6.add(&node_9);
    
    digit node_11(16);
    digit node_12(13);
    num node_10(11);
    real node_16(22);
    node_7.add(&node_11);
    node_8.add(&node_12).add(&node_10);
    node_9.add(&node_16);

    digit node_13(19);
    digit node_14(14);
    digit node_15(18);
    node_10.add(&node_19);
    node_16.add(&node_14).add(&node_15);
*/    
    M root(1);
    E node_1(2);
    root.add(&node_1);
    
    E node_2(8);
    E node_3(8);
    node_1.add(&node_2).add(&node_3);
    
    num node_4(11);
    num node_5(11);
    node_2.add(&node_4);
    node_3.add(&node_5);
  
    digit node_6(16);
    digit node_7(19);
    node_4.add(&node_6);
    node_5.add(&node_7);
    
    eval_mag.evaluator_mag(&root);

    cout << " After evaluation." << endl;
    cout << root.to_string() << endl;
    
    cout << "FIN EVAL_AG" << endl;

    return 0;
}
