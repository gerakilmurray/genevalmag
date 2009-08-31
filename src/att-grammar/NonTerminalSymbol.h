/**
  * NonTerminalSymbol.h
  *
  *  Created on: 31/08/2009
  *  Authors:
				 Kilmurray, Gerardo Luis.
                 Picco, Gonzalo M.
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
