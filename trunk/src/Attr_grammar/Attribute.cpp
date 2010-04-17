/**
  *  \file      Attribute.cpp
  *  \brief     Implementation of the methods the Attribute.h
  *  \date      23/10/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>
#include <sstream>

#include "../../include/Attr_grammar/Attribute.h"

namespace genevalmag
{

#ifdef _DEBUG
    /* Numbers of attributes current in the system. */
    static int attrs(0);
#endif

/**
  * Constructor empty of attribute.
  */
Attribute::Attribute()
{
    #ifdef _DEBUG
        attrs++;
    #endif
}

/**
  * Constructor copy of attribute.
  */
Attribute::Attribute(const Attribute &other)
{
    copy(other);

    #ifdef _DEBUG
        attrs++;
    #endif
}

/**
  * Destructor of attribute.
  */
Attribute::~Attribute()
{
    destroy();

    #ifdef _DEBUG
        attrs--;
        if(attrs == 0)
        {
            cout << attrs << " -> Attributes" << endl;
        }
    #endif
}

/**
  * Operator assign(=) of attribute.
  */
Attribute &Attribute::operator=(const Attribute &other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

/**
  * Method of copy the attribute, STL-like.
  */
void Attribute::copy(const Attribute &other)
{
    a_name             = other.get_name();
    a_sort_type        = other.get_sort_type();
    a_mod_type         = other.get_mod_type();
    a_member_symbol    = other.get_member_symbol();
}

/**
  * Method destroy the attribute, STL-like.
  */
void Attribute::destroy()
{
}

/**
  * Return the name of the attribute.
  */
const string Attribute::get_name() const
{
    return a_name;
}

/**
  * Return the sort type of the attribute.
  */
const Sort *Attribute::get_sort_type() const
{
    return a_sort_type;
}

/**
  * Return the modifiers of the attribute.
  */
const type_attr Attribute::get_mod_type() const
{
    return a_mod_type;
}

/**
  * Return the membership list of the attribute.
  */
const string Attribute::get_member_symbol() const
{
    return a_member_symbol;
}

/**
  * Set the name of the attribute.
  */
void Attribute::set_name(const string name)
{
    a_name = name;
}

/**
  * Set the sort type of the attribute.
  */
void Attribute::set_sort_type(const Sort *sort_type)
{
    a_sort_type = sort_type;
}

/**
  * Set the modifiers of the attribute.
  */
void Attribute::set_mod_type(const type_attr mod_type)
{
    a_mod_type = mod_type;
}

/**
  * Set the membership list of the attribute.
  */
void Attribute::set_member_symbol(const string member_symbol)
{
    a_member_symbol = member_symbol;
}

/**
  * Return true if the modifiers of the attribute is synthetized.
  */
const bool Attribute::is_synthetize() const
{
    return a_mod_type == k_synthetize;
}
/**
  * Return true if the modifiers of the attribute is inherit.
  */
const bool Attribute::is_inherit() const
{
    return a_mod_type == k_inherit;
}
/**
  * Generate and return a string reprensentation of a attribute.
  *
  * Result= name ":" modifiers "<" sort_type ["(" instance ")" IF DEBUG IS ON] "> of " membership_list
  */
const string Attribute::to_string() const
{
    string attr;
    attr.append(a_name);
    attr.append("\t:\t");
    if(is_synthetize())
    {
        attr.append("syn");
    }
    else
    {
        attr.append("inh");
    }
    attr.append(" <");
    attr.append(a_sort_type->get_name());

    #ifdef _DEBUG
        attr.append("(");
        stringstream ins;
        ins << a_sort_type->get_ins();
        attr.append(ins.str());
        attr.append(")");
    #endif

    attr.append("> \tof ");
    attr.append(a_member_symbol);
    attr.append(";");
    return attr;
}

/**
  * Compares the attribute with other.
  */
const bool Attribute::equals(const Attribute &other) const
{
    return key().compare(other.key()) == 0;
}

/**
  * Generate and return the string key that identifies a attribute definitely.
  *
  * Result= name modifiers sort_type membership_list
  */
const string Attribute::key() const
{
    string key;
    key.append(a_name);
    key.append(a_sort_type->get_name());
    key.append(a_member_symbol);
    return key;
}

} /* end genevalmag */
