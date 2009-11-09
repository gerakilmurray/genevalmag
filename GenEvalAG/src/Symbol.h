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
#include <string>

#include "Attribute.h"

namespace genevalmag {

// Symbol's type.
enum SymbType
{
	kTerminal,
	kNonTerminal
};

class Symbol {
	private:
		string sym_name;
		SymbType sym_type;
		vector<Attribute>  attrs;

	public:
		Symbol();
		Symbol(string name, SymbType type);
		virtual ~Symbol();
		void addAttr(const Attribute attr);
		void removeAttr(const int index);
		string getName() const;
		void setName(string name);
		SymbType getType() const;
		void setType(SymbType type);
	    bool equals(Symbol symb) const;
	    string to_string() const;
	    vector<Attribute> getAttrs() const;
};
}

#endif /* SYMBOL_H_ */
