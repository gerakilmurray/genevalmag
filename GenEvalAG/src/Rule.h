/**
 * \file Rule.h
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 05/11/2009
 *  \author    Kilmurray, Gerardo Luis.
 *  \author    Picco, Gonzalo M.
 */

#ifndef RULE_H_
#define RULE_H_

#include <vector>

#include "Symbol.h"
#include "Equation.h"

namespace genevalmag {

class Rule {
	private:
		Symbol left_symbol;
		vector <Symbol> right_side;
		vector <Equation> eqs;

	public:
		Rule();
		virtual ~Rule();

		void set_left_symbol(const Symbol symb);
		void add_right_symbol(const Symbol symb);

		Symbol get_left_symbol() const;
		vector<Symbol> get_right_side()const;
		bool equals(Rule rule) const;
		string to_string() const;
};

}

#endif /* RULE_H_ */
