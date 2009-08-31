/**
  * TerminalSymbol.h
  *
  *  Created on: 31/08/2009
  *  Authors:
				 Kilmurray, Gerardo Luis.
                 Picco, Gonzalo M.
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
