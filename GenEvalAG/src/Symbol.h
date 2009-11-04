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

class Symbol {
	private:
		string name;
		vector<Attribute>  attrs;
		bool terminal; // si es verdadero el simbolo es terminal, de otro modo es nonterminal.

	public:
		virtual ~Symbol();
		Symbol();
		void addAttr(const Attribute attr);
		void removeAttr(const int index);
		string getName();
		void setName(string name);
};

}

#endif /* SYMBOL_H_ */
