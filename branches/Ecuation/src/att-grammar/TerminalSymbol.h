/**
  * \file TerminalSymbol.h
  *		\brief Define a terminal symbol of a attribute grammar.
  *  \date 31/08/2009
  *  \author Kilmurray, Gerardo Luis.
	 \author Picco, Gonzalo M.
 */


#ifndef TERMINALSYMBOL_H_
#define TERMINALSYMBOL_H_

#include "Symbol.h"

namespace gen_eval_mag {

class TerminalSymbol : public Symbol {
public:
	TerminalSymbol();
	virtual ~TerminalSymbol();
};

}

#endif /* TERMINALSYMBOL_H_ */
