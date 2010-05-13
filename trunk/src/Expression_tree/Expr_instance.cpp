/**
  *  \file      Expr_instance.cpp
  *  \brief     Implementation of a instance element of an Attribute Syntax Tree (AST).
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */
  
#include <sstream>
#include <iostream>

#include "../../include/Expression_tree/Expr_instance.h"

namespace genevalmag
{

#ifdef _DEBUG
    /* Numbers of instances current in the system. */
    static unsigned short ast_instances(0);
#endif

/**
  * Constructor empty of Expr_instance.
  */
Expr_instance::Expr_instance():Expr_leaf()
{
    #ifdef _DEBUG
        ast_instances++;
    #endif
}

/**
  * Constructor copy of Expr_instance.
  */
Expr_instance::Expr_instance(const Expr_instance &other)
{
    copy(other);

    #ifdef _DEBUG
        ast_instances++;
    #endif
}

/**
  * Destructor of Expr_instance.
  */
Expr_instance::~Expr_instance()
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
  * Operator assign(=) of Expr_instance.
  */
Expr_instance &Expr_instance::operator=(const Expr_instance &other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

/**
  * Method of copy the Expr_instance, STL-like C++.
  */
void Expr_instance::copy(const Expr_instance &other)
{
    i_symb              = other.get_symb();
    i_num               = other.get_num();
    i_attr              = other.get_attr();
    parent              = other.get_parent();
    conflict            = other.get_conflict();
    type_synthetized    = other.get_type_synthetized();
}

/**
  * Method destroy Expr_instance, STL-like C++.
  */
void Expr_instance::destroy()
{
    i_symb = NULL;
    i_attr = NULL;
}

/**
  * Returns the attribute pointer of the Expr_instance.
  */
const Attribute *Expr_instance::get_attr() const
{
    return i_attr;
}

/**
  * Returns the number of the Expr_instance.
  */
unsigned short Expr_instance::get_num() const
{
    return i_num;
}

/**
  * Returns the symbol pointer of the Expr_instance.
  */
const Symbol *Expr_instance::get_symb() const
{
    return i_symb;
}

/**
  * Sets the attribute pointer of the Expr_instance.
  */
void Expr_instance::set_attr(const Attribute *attr)
{
    i_attr = attr;
}

/**
  * Sets the number of the Expr_instance.
  */
void Expr_instance::set_num(unsigned short num)
{
    i_num = num;
}

/**
  * Sets the symbol pointer of the Expr_instance.
  */
void Expr_instance::set_symb(const Symbol *symb)
{
    i_symb = symb;
}

/**
  * Generate and return a string reprensentation of a Expr_instance.
  *
  * Result= \<symbol\>"["\<number\>"]."\<attribute\>
  *
  * Ex: E[0].valor
  */
string Expr_instance::to_string() const
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
  * Compares the Expr_instance with other.
  * Respects Symbol and attribute.
  */
bool Expr_instance::equals_without_index(const Expr_instance *other) const
{
    /* Save ins 1 */
    string inst1(i_symb->get_name());
    inst1.append(i_attr->get_name());

    /* Save ins 2 */
    string inst2(other->get_symb()->get_name());
    inst2.append(other->get_attr()->get_name());

    return inst1.compare(inst2) == 0;
}

/**
  * Generate and return the string key that identifies an Expr_instance definitely.
  *
  * Result= \<symbol\>\<number\>\<attribute\>
  *
  * Ex: E0valor
  */
string Expr_instance::key() const
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
