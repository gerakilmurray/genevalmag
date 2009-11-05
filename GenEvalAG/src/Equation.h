/*
 * Equation.h
 *
 *  Created on: 05/11/2009
 *      Author: gera
 */

#ifndef EQUATION_H_
#define EQUATION_H_

#include <vector>

#include "MultiTree.h"
#include "Symbol.h"

namespace genevalmag {

class Equation {
	private:
		MultiTree <Symbol> *body;

	public:
		Equation();
		virtual ~Equation();
		Symbol getLeftSide();
		vector <Symbol> getRightSide();
};

}

#endif /* EQUATION_H_ */
