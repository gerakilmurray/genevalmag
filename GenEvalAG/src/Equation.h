/**
 * \file Equation.h
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 05/11/2009
 *  \author    Kilmurray, Gerardo Luis.
 *  \author    Picco, Gonzalo M.
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
		Symbol get_left_side();
		vector <Symbol> get_right_side();
};

}

#endif /* EQUATION_H_ */
