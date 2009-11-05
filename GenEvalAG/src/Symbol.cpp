/**
 * \file Symbol.cpp
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 04/11/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#include "Symbol.h"

namespace genevalmag {

Symbol::Symbol()
{
}

Symbol::Symbol(string name, SymbType type)
{
	this->sym_name = name;
	this->sym_type = type;
}

Symbol::~Symbol() {
	// TODO Auto-generated destructor stub
}

void Symbol::addAttr(const Attribute attr)
{
	this->attrs.push_back(attr);
}

void Symbol::removeAttr(int index)
{
	////////
}

string Symbol::getName() const
{
	return this->sym_name;
}

void Symbol::setName(string name)
{
	this->sym_name = name;
}

bool Symbol::equals(Symbol symb) const
{
	return this->sym_name.compare(symb.getName()) == 0;
}

string Symbol::to_string() const
{
	string symb("symbol ");
	symb.append(this->getName());
	switch (this->sym_type)
	{
		case k_nonTerminal:
			symb.append(" NonTerminal");
			break;
		case k_terminal:
			symb.append(" Terminal");
			break;
	}
	symb.append(";");
	return symb;
}
}
