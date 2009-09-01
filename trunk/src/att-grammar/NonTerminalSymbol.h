/**
  * \file NonTerminalSymbol.h
  *		\brief Define a non-terminal symbol of a attribute grammar.
  *  \date 31/08/2009
  *  \author Kilmurray, Gerardo Luis.
	 \author Picco, Gonzalo M.
 */


#ifndef NONTERMINALSYMBOL_H_
#define NONTERMINALSYMBOL_H_

#include "Symbol.h"

namespace gen_eval_mag {

class NonTerminalSymbol : public Symbol{
public:
	NonTerminalSymbol();
	virtual ~NonTerminalSymbol();
};

}

#endif /* NONTERMINALSYMBOL_H_ */
