/**
  * Symbol.h
  *
  *  Created on: 31/08/2009
  *  Authors:
				 Kilmurray, Gerardo Luis.
                 Picco, Gonzalo M.
 */

#ifndef SYMBOL_H_
#define SYMBOL_H_

#include "Attribute.h"

namespace gen_eval_mag {

class Symbol {
private:
	Attribute attrs[];

public:
	virtual ~Symbol();
	Symbol();
};

}

#endif /* SYMBOL_H_ */
