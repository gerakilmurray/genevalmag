/**
  *  \file      Ast_instance.cpp
  *  \brief     Implementation of a instance element of an Attribute Syntax Tree (AST).
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */
  
#include <sstream>
#include <iostream>

#include "Ast_instance.h"

namespace genevalmag
{

#ifdef _DEBUG
    /* Numbers of instances current in the system. */
    static int ast_instances(0);
#endif

/**
  * Constructor empty of Ast_instance.
  */
Ast_instance::Ast_instance()
{
    parent      = NULL;
    conflict    = -1;

    #ifdef _DEBUG
        ast_instances++;
    #endif
}

/**
  * Constructor copy of Ast_instance.
  */
Ast_instance::Ast_instance(const Ast_instance &other)
{
    copy(other);

    #ifdef _DEBUG
        ast_instances++;
    #endif
}

/**
  * Destructor of Ast_instance.
  */
Ast_instance::~Ast_instance()
{
    destroy();

    #ifdef _DEBUG
        ast_instances--;
        if(ast_instances == 0)
        {
            cout << ast_instances << " -> AST Instances" << endl;
        }
    #endif
}

/**
  * Operator assign(=) of Ast_instance.
  */
Ast_instance &Ast_instance::operator=(const Ast_instance &other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

/**
  * Method of copy the Ast_instance, STL-like C++.
  */
void Ast_instance::copy(const Ast_instance &other)
{
    i_symb              = other.get_symb();
    i_num               = other.get_num();
    i_attr              = other.get_attr();
    parent              = other.get_parent();
    conflict            = other.get_conflict();
    type_synthetized    = other.get_type_synthetized();
}

/**
  * Method destroy Ast_instance, STL-like C++.
  */
void Ast_instance::destroy()
{
    i_symb = NULL;
    i_attr = NULL;
}

/**
  * Returns the attribute pointer of the Ast_instance.
  */
const Attribute *Ast_instance::get_attr() const
{
    return i_attr;
}

/**
  * Returns the number of the Ast_instance.
  */
unsigned short Ast_instance::get_num() const
{
    return i_num;
}

/**
  * Returns the symbol pointer of the Ast_instance.
  */
const Symbol *Ast_instance::get_symb() const
{
    return i_symb;
}

/**
  * Sets the attribute pointer of the Ast_instance.
  */
void Ast_instance::set_attr(const Attribute *attr)
{
    i_attr = attr;
}

/**
  * Sets the number of the Ast_instance.
  */
void Ast_instance::set_num(unsigned short num)
{
    i_num = num;
}

/**
  * Sets the symbol pointer of the Ast_instance.
  */
void Ast_instance::set_symb(const Symbol *symb)
{
    i_symb = symb;
}

/**
  * Generate and return a string reprensentation of a Ast_instance.
  *
  * Result= \<symbol\>"["\<number\>"]."\<attribute\>
  *
  * Ex: E[0].valor
  */
string Ast_instance::to_string() const
{
    /* Save symbol's name. */
    string inst(i_symb->get_name());

    /* Save instance number. */
    inst.append("[");
    stringstream ins;
    ins << i_num;
    inst.append(ins.str());
    inst.append("]");
    inst.append(".");

    /* Save attribute's name. */
    inst.append(i_attr->get_name());
    return inst;
}

/**
  * Compares the Ast_instance with other.
  * Respects Symbol, attribute and number.
  */
bool Ast_instance::equals_with_index(const Ast_instance *other) const
{
    return (key().compare(other->key()) == 0);
}

/**
  * Generate and return the string key that identifies an Ast_instance definitely.
  *
  * Result= \<symbol\>\<number\>\<attribute\>
  *
  * Ex: E0valor
  */
string Ast_instance::key() const
{
    /* Save symbol's name. */
    string inst(i_symb->get_name());

    /* Save instance number. */
    stringstream ins;
    ins << i_num;
    inst.append(ins.str());

    /* Save attribute's name. */
    inst.append(i_attr->get_name());
    return inst;
}

} /* end genevalmag */
