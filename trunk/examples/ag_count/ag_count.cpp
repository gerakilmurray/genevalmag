/**
  *  \file      ag_count.cpp
  *  \brief     File of proof.
  *  \date      Thu Mar 25 21:04:46 2010
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
*/

#include<iostream>

#include "maggen.hpp"

using namespace std;
using namespace evalmag;

/**
  * Main method.
  */
int main()
{
    maggen eval_mag;

    // ROOT Extend
    S root(1);

    // ROOT
    T node_1(2);
  	root.add(&node_1);
	
    // childs ROOT
    T2 node_20(3);
    T node_21(2);
    T node_22(4);

	  node_1.add(&node_20);
	  node_1.add(&node_21);
	  node_1.add(&node_22);
	
    // childs of my second childs.
    T2 node_210(3);
    T node_211(4);
    T node_212(2);

	  node_21.add(&node_210);
	  node_21.add(&node_211);
	  node_21.add(&node_212);	

    // childs of thirtd child of my second child.
    T2 node_2120(3);
    T node_2121(4);
    T node_2122(4);

	  node_212.add(&node_2120);
	  node_212.add(&node_2121);
	  node_212.add(&node_2122);
		
  	eval_mag.evaluator_mag(&root);

    cout << " After evaluation." << endl;
    cout << root.to_string() << endl;

    return 0;
}
