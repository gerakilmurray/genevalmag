/**
  * \file Symbol.h
  *		\brief Define a symbol of a attribute grammar.
  *  \date 31/08/2009
  *  \author Kilmurray, Gerardo Luis.
	 \author Picco, Gonzalo M.
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
	void addAttr(Attribute attr);
	void removeAttr(int index);

};

}

#endif /* SYMBOL_H_ */
