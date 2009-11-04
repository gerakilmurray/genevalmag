/**
 * \file Symbol.cpp
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 04/11/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#include "Symbol.h"

namespace genevalmag {

Symbol::Symbol() {
	// TODO Auto-generated constructor stub

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
}
string Symbol::getName()
{
	return this->name;
}
void Symbol::setName(string name)
{
	this->name = name;
}

}

