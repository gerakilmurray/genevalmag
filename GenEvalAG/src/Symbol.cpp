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

Symbol::Symbol(string name, symb_type type)
{
	sym_name = name;
	sym_type = type;
}

Symbol::~Symbol() {
	// TODO Auto-generated destructor stub
}

void Symbol::add_attr(const Attribute attr)
{
	attrs.push_back(attr);
}

void Symbol::remove_attr(int index)
{
	////////
}

string Symbol::get_name() const
{
	return sym_name;
}

void Symbol::set_name(string name)
{
	sym_name = name;
}

symb_type Symbol::get_type() const
{
	return sym_type;
}

void Symbol::set_type(symb_type type)
{
	sym_type = type;
}

bool Symbol::equals(Symbol symb) const
{
	return sym_name.compare(symb.get_name()) == 0;
}

vector<Attribute> Symbol::get_attrs() const
{
	return attrs;
}


string Symbol::to_string() const
{
	string symb("symbol ");
	symb.append(get_name());
	switch (sym_type)
	{
		case k_non_terminal:
			symb.append("\tNonTerminal");

			symb.append("\tAttributes: ");
			for (vector<Attribute>::size_type i = 0; i < attrs.size(); i++)
			{
				symb.append(attrs[i].get_name());
				if (i < attrs.size() - 1)
					symb.append(",");
			}

			break;
		case k_terminal:
			symb.append("\tTerminal");
			break;
	}
	symb.append(";");


	return symb;
}

bool Symbol::is_non_terminal() const
{
	return sym_type == k_non_terminal;
}

}
