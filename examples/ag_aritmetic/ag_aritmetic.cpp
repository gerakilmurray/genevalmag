/**
  *  \file      ag_aritmetic.cpp
  *  \brief     File of proof.
  *  \date      Thu Mar 25 21:04:46 2010
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
*/

#include <vector>
#include <iostream>

#include "maggen.hpp"

using namespace evalmag;

/**
  * Main method.
  */
int main()
{
    maggen eval_mag;

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

    return 0;
}
