/**
  *  \file		Symbol.cpp
  *  \brief		Implementation of the methods the Symbol.h
  *  \date		04/11/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>

#include "Symbol.h"

namespace genevalmag
{

#ifdef _DEBUG
	// Numbers of symbols current in the system.
	static int symbols = 0;
#endif

/**
  * Constructor empty of symbol.
  */
Symbol::Symbol()
{
	#ifdef _DEBUG
		symbols++;
	#endif
}

/**
  * Constructor with name and type of symbol.
  */
Symbol::Symbol(string name, symbol_type type)
{
	symb_name = name;
	symb_type = type;

	#ifdef _DEBUG
		symbols++;
	#endif
}

/**
  * Constructor copy of symbol.
  */
Symbol::Symbol(Symbol const &other)
{
	copy(other);

	#ifdef _DEBUG
		symbols++;
	#endif
}

/**
  * Destructor of symbol.
  */
Symbol::~Symbol()
{
	destroy();
	#ifdef _DEBUG
		symbols--;
		if(symbols == 0)
			cout << symbols << " -> Symbols" << endl;
	#endif
}

/**
  * Operator assign(=) of symbol.
  */
Symbol &Symbol::operator=(Symbol const &other)
{
	if(this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

/**
  * Method of copy the symbol, STL-like C++.
  */
void Symbol::copy(Symbol const &other)
{
	symb_name	= other.get_name();
	symb_type	= other.get_type();
	symb_attrs	= other.get_attrs();
}

/**
  * Method destroy symbol, STL-like C++.
  */
void Symbol::destroy()
{
}

/**
  * Return the name of the symbol.
  */
string Symbol::get_name() const
{
	return symb_name;
}

/**
  * Return the type of the symbol.
  */
symbol_type Symbol::get_type() const
{
	return symb_type;
}

/**
  * Return the list of attributes of the symbol.
  */
const vector<const Attribute*> &Symbol::get_attrs() const
{
	return symb_attrs;
}

/**
  * Find in the list of attribute of the symbol and return the attribute with
  * that name passed as parameter.
  */
const Attribute *Symbol::get_attribute(string name_attr) const
{
	for(vector<Attribute*>::size_type i = 0; i < symb_attrs.size(); i++)
	{
		if(symb_attrs[i]->get_name().compare(name_attr) == 0)
				return symb_attrs[i];
	}
	return NULL;
}

/**
  * Set the name of the symbol.
  */
void Symbol::set_name(string name)
{
	symb_name = name;
}

/**
  * Set the type of the symbol.
  */
void Symbol::set_type(symbol_type type)
{
	symb_type = type;
}

/**
  * Enqueue a attribute in the list of the symbol.
  */
void Symbol::add_attr(const Attribute *attr)
{
	symb_attrs.push_back(attr);
}

/**
  * Return true if the symbol's type is Non Terminal.
  */
bool Symbol::is_non_terminal() const
{
	return symb_type == k_non_terminal;
}

/**
  * Generate and return a string reprensentation of a symbol.
  *
  * Result= "symbol" name type ";"
  *
  * where if 'type' is Non Terminal, then list the attributes of the symbol.
  *
  * list= "Attributes:" attr_1 "," ... "," attr_n
  */
string Symbol::to_string() const
{
	string symb("symbol ");
	symb.append(symb_name);
	switch(symb_type)
	{
		case k_non_terminal:
			symb.append("\tNonTerminal");

			symb.append("\tAttributes: ");
			for(vector<Attribute*>::size_type i = 0; i < symb_attrs.size(); i++)
			{
				symb.append(symb_attrs[i]->get_name());
				if(i+1 < symb_attrs.size())
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

/**
  * Compares the symbol with other.
  */
bool Symbol::equals(Symbol const &other) const
{
	return key().compare(other.key()) == 0;
}

/**
  * Generate and return the string key that identifies a symbol definitely.
  *
  * Result= name
  */
string Symbol::key() const
{
	return symb_name;
}

} // end genevalmag
