/**
 * \file Symbol.h
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 04/11/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <vector>

#include "Attribute.h"

namespace genevalmag {

// Symbol's type.
enum SymbType
{
	k_terminal,
	k_nonTerminal
};

class Symbol {
	private:
		string sym_name;
		SymbType sym_type;
		vector<Attribute>  attrs;

	public:
		virtual ~Symbol();
		Symbol();
		void addAttr(const Attribute attr);
		void removeAttr(const int index);
		string getName();
		void setName(string name);
	    bool equals(Symbol symb) const;
};
}

#endif /* SYMBOL_H_ */
