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
Attribute::Attribute(const Attribute& other) {
	copy(other);
}

Attribute::Attribute(string name, string type, type_attr mod, string merberships)
{
	a_name = name;
	a_type = type;
	a_mod_type = mod;
	a_member_symbol = merberships;
}

Attribute::~Attribute()
{
	destroy();
}
Attribute& Attribute::operator= (Attribute const& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

void Attribute::copy(Attribute const& other)
{
	a_name			= other.get_name();
	a_type			= other.get_type();
	a_mod_type		= other.get_mod_type();
	a_member_symbol	= other.get_member_symbol();
}

void Attribute::destroy()
{
}
string Attribute::get_member_symbol() const
{
    return a_member_symbol;
}

type_attr Attribute::get_mod_type() const
{
    return a_mod_type;
}

string Attribute::get_name() const
{
    return a_name;
}

string Attribute::get_type() const
{
    return a_type;
}

void Attribute::set_member_symbol(string a_member_symbol)
{
    a_member_symbol = a_member_symbol;
}

void Attribute::set_mod_type(type_attr a_mod_type)
{
    a_mod_type = a_mod_type;
}

void Attribute::set_name(string a_name)
{
    a_name = a_name;
}

void Attribute::set_type(string a_type)
{
    a_type = a_type;
}

string Attribute::to_string() const
{
	string att;
	att.append(get_name());
	att.append("\t: ");
	if (is_syntetize())
		att.append("syn");
	else
		att.append("inh");
	att.append(" <");
	att.append(get_type());
	att.append("> of ");
	att.append(get_member_symbol());
	return att;
}

///////////////////////////////////////////////
// compares the attribute with other.
///////////////////////////////////////////////
bool Attribute::equals(Attribute attr) const
// compare for name, mod_type and type.
{
	return	(a_name.compare(attr.get_name())== 0) &&
			(a_mod_type == attr.get_mod_type()) &&
			(a_type.compare(attr.get_type()) == 0) &&
			(a_member_symbol.compare(attr.get_member_symbol()) == 0);
}

bool Attribute::is_syntetize() const
{
	return a_mod_type == k_syntetize;
}
}
