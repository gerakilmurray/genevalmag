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
		Rule(const Symbol lf, const vector<Symbol> rs);
		virtual ~Rule();
		void addSymbol(const Symbol s);
		void removeSymbol(const int index);
		Symbol getLeft_symbol();
		vector <Symbol> getRight_side();
		void setLeft_symbol(Symbol left_symbol);
		void setRight_side(const vector <Symbol> right_side);
};

}

#endif /* RULE_H_ */
