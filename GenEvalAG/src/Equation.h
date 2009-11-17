/**
 * \file Equation.h
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 05/11/2009
 *  \author    Kilmurray, Gerardo Luis.
 *  \author    Picco, Gonzalo M.
 */

#ifndef EQUATION_H_
#define EQUATION_H_


#include "MultiTree.h"

namespace genevalmag {

class Equation {
	private:
		n_term l_value;
		MultiTree r_value;

	public:
		Equation();
		virtual ~Equation();
		Symbol get_l_value();
		vector <Symbol> get_body();
};

}

#endif /* EQUATION_H_ */
