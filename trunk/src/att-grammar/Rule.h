/**
  *  \file Rule.h
  *      \brief Define a rule of a attribute grammar.
  *  \date 31/08/2009
  *  \author Kilmurray, Gerardo Luis.
  *	 \author Picco, Gonzalo Martín.
  */

#ifndef RULE_H_
#define RULE_H_

#include "Symbol.h"
#include "NonTerminalSymbol.h"
#include "Equation.h"

namespace gen_eval_mag {

class Rule {
	private:
		NonTerminalSymbol *left_symbol;
		Symbol *right_side[];
		Equation *eqs[];

	public:
		Rule();
		Rule(const NonTerminalSymbol * lf, const Symbol * rs[]);
		virtual ~Rule();
		void addSymbol(const Symbol* s);
		void removeSymbol(const int index);
		NonTerminalSymbol* getLeft_symbol();
		Symbol** getRight_side();
		void setLeft_symbol(NonTerminalSymbol * left_symbol);
		void setRight_side(const Symbol * right_side[]);
};

}

#endif /* RULE_H_ */
