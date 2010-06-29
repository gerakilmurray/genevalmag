/**
  *  \file      ag_wuu_yang.cpp
  *  \brief     File of proof from Wuu Yang's paper.
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

    S node_s1(1);
	  X node_s1_x(4);
	  Y node_s1_y2(2);
	  Z node_s1_z(5);
	  Y node_s1_z_y3(2);

	  node_s1.add(&node_s1_x).add(&node_s1_y2).add(&(node_s1_z.add(&node_s1_z_y3)));
	
    eval_mag.evaluator_mag(&node_s1);

    cout << " After evaluation." << endl;
    cout << node_s1.to_string() << endl;

    return 0;
}
