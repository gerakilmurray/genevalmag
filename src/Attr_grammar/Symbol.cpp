/**
  *  \file      Symbol.cpp
  *  \brief     Implementation of the methods the Symbol.h
  *  \date      04/11/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>

#include "../../include/Attr_grammar/Symbol.h"

namespace genevalmag
{

#ifdef _DEBUG
    /* Numbers of Symbols current in the system. */
	static unsigned short symbols(0);
#endif

/**
  * Constructor empty of Symbol.
  */
Symbol::Symbol()
{
    #ifdef _DEBUG
        symbols++;
    #endif
}

/**
  * Constructor with name and type of Symbol.
  */
Symbol::Symbol(string &name, symbol_type type)
{
    symb_name = name;
    symb_type = type;

    #ifdef _DEBUG
        symbols++;
    #endif
}

/**
  * Constructor copy of Symbol.
  */
Symbol::Symbol(const Symbol &other)
{
    copy(other);

    #ifdef _DEBUG
        symbols++;
    #endif
}

/**
  * Destructor of Symbol.
  */
Symbol::~Symbol()
{
    destroy();
    #ifdef _DEBUG
        symbols--;
        if(symbols == 0)
        {
            cout << symbols << " -> Symbols" << endl;
        }
    #endif
}

/**
  * Operator assign(=) of Symbol.
  */
Symbol &Symbol::operator=(const Symbol &other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

/**
  * Method of copy the Symbol, STL-like C++.
  */
void Symbol::copy(const Symbol &other)
{
    symb_name     = other.get_name();
    symb_type     = other.get_type();
    symb_attrs    = other.get_attrs();
}

/**
  * Method destroy symbol, STL-like C++.
  */
void Symbol::destroy()
{
}

/**
  * Returns the name of the symbol.
  */
string Symbol::get_name() const
{
    return symb_name;
}

/**
  * Returns the type of the symbol.
  */
symbol_type Symbol::get_type() const
{
    return symb_type;
}

/**
  * Returns the list of attributes of the symbol.
  */
const vector<const Attribute*> &Symbol::get_attrs() const
{
    return symb_attrs;
}

/**
  * Finds in the list of attribute of the symbol and
  * returns the attribute with that name passed as parameter.
  */
const Attribute *Symbol::get_attribute(const string &name_attr) const
{
    for(vector<Attribute*>::size_type i(0); i < symb_attrs.size(); i++)
    {
        if(symb_attrs[i]->get_name().compare(name_attr) == 0)
        {
            return symb_attrs[i];
        }
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
  * Sets the type of the symbol.
  */
void Symbol::set_type(symbol_type type)
{
    symb_type = type;
}

/**
  * Enqueues a attribute in the list of the symbol.
  */
void Symbol::add_attr(const Attribute *attr)
{
    symb_attrs.push_back(attr);
}

/**
  * Returns true if the symbol's type is non-terminal.
  */
const bool Symbol::is_non_terminal() const
{
    return symb_type == k_non_terminal;
}

/**
  * Generates and returns a string reprensentation of a symbol.
  *
  * Result = "symbol" name type ";"
  *
  * where if 'type' is Non Terminal, then list the attributes of the symbol.
  *
  * list = "Attributes:" attr_1 "," ... "," attr_n
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
            for(vector<Attribute*>::size_type i(0); i < symb_attrs.size(); i++)
            {
                symb.append(symb_attrs[i]->get_name());
                if(i+1 < symb_attrs.size())
                {
                    symb.append(",");
                }
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
bool Symbol::equals(const Symbol &other) const
{
    return key().compare(other.key()) == 0;
}

/**
  * Generate and return the string key that identifies a symbol definitely.
  *
  * Result = name
  */
string Symbol::key() const
{
    return symb_name;
}

} /* end genevalmag */
