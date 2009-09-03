/**
  * \file Rule.h
  *		\brief Define a rule of a attribute grammar.
  *  \date 31/08/2009
  *  \author Kilmurray, Gerardo Luis.
	 \author Picco, Gonzalo M.
 */

#ifndef RULE_H_
#define RULE_H_

#include "Symbol.h"
#include "NonTerminalSymbol.h"

namespace gen_eval_mag {

class Rule {
public:
	Rule();
	Rule(NonTerminalSymbol lf, Symbol rs[]);
    virtual ~Rule();
    void addSymbol(Symbol s);
    void removeSymbol(int index);
    NonTerminalSymbol getLeft_symbol();
    Symbol* getRight_side();
    void setLeft_symbol(NonTerminalSymbol left_symbol);
    //void setRight_side(Symbol right_side[]);


private:
    NonTerminalSymbol left_symbol;
    Symbol right_side[];
};

}

#endif /* RULE_H_ */
