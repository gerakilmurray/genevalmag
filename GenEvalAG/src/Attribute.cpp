/**
 * \file Attribute.cpp
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 23/10/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#include "Attribute.h"

namespace genevalmag {

Attribute::Attribute() {
	// TODO Auto-generated constructor stub
}
Attribute::Attribute(string name, string type, TipeAttr mod, string merberships)
{
	this->a_name = name;
	this->a_type = type;
	this->a_mod_type = mod;
	this->a_member_symbol = merberships;
}

Attribute::~Attribute() {
	// TODO Auto-generated destructor stub
}

string Attribute::getMember_symbol() const
{
    return a_member_symbol;
}

TipeAttr Attribute::getMod_type() const
{
    return a_mod_type;
}

string Attribute::getName() const
{
    return a_name;
}

string Attribute::getType() const
{
    return a_type;
}

void Attribute::setMember_symbol(string a_member_symbol)
{
    this->a_member_symbol = a_member_symbol;
}

void Attribute::setMod_type(TipeAttr a_mod_type)
{
    this->a_mod_type = a_mod_type;
}

void Attribute::setName(string a_name)
{
    this->a_name = a_name;
}

void Attribute::setType(string a_type)
{
    this->a_type = a_type;
}

string Attribute::to_string() const
{
	string att;
	att.append(this->getName());
	att.append(": ");
	if (this->getMod_type() == kSyntetize)
		att.append("syn");
	else
		att.append("inh");
	att.append(" <");
	att.append(this->getType());
	att.append("> of ");
	att.append(this->getMember_symbol());
	return att;
}

///////////////////////////////////////////////
// compares the attribute with other.
///////////////////////////////////////////////
bool Attribute::equals(Attribute attr) const
// compare for name, mod_type and type.
{
	return	(this->a_name.compare(attr.getName())== 0) &&
			(this->a_mod_type == attr.getMod_type()) &&
			(this->a_type.compare(attr.getType()) == 0) &&
			(this->a_member_symbol.compare(attr.getMember_symbol()) == 0);
}

}
