/**
 * \file Symbol.cpp
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 04/11/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#include <iostream>

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

SymbType Symbol::getType() const
{
	return this->sym_type;
}

void Symbol::setType(SymbType type)
{
	this->sym_type = type;
}

bool Symbol::equals(Symbol symb) const
{
	return this->sym_name.compare(symb.getName()) == 0;
}

vector<Attribute> Symbol::getAttrs() const
{
	return this->attrs;
}


string Symbol::to_string() const
{
	string symb("symbol ");
	symb.append(this->getName());
	switch (this->sym_type)
	{
		case kNonTerminal:
			symb.append("\tNonTerminal");

			symb.append("\tAttributes: ");
			for (vector<Attribute>::size_type i = 0; i < this->attrs.size(); i++)
			{
				symb.append(this->attrs[i].getName());
				if (i < this->attrs.size() - 1)
					symb.append(",");
			}

			break;
		case kTerminal:
			symb.append("\tTerminal");
			break;
	}
	symb.append(";");


	return symb;
}
}
