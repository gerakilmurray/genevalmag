/**
  * \file Equation.h
  *		\brief Define equation of the Attribute Grammar
  *  \date 04/09/2009
  *  \author Kilmurray, Gerardo Luis.
  *	 \author Picco, Gonzalo M.
  */

#ifndef EQUATION_H_
#define EQUATION_H_

#include <boost/graph/graph_as_tree.hpp>
#include "Symbol.h"
#include "MultiTree.h"

namespace gen_eval_mag {

class Equation {
private:
	MultiTree <Symbol> *body;

public:
	Equation();
	virtual ~Equation();
	Symbol * getLeftSide();
	Symbol * getRightSide();
};

}

#endif /* EQUATION_H_ */
