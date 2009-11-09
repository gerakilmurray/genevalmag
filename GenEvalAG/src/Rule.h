/*
 * Rule.h
 *
 *  Created on: 05/11/2009
 *      Author: gera
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

		void setLeft_symbol(const Symbol symb);
		void addRight_symbol(const Symbol symb);

		Symbol getLeft_symbol() const;
		vector<Symbol> getRight_side()const;
		bool equals(Rule rule) const;
		string to_string() const;
};

}

#endif /* RULE_H_ */
