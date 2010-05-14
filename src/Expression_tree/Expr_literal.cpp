/**
  *  \file      Expr_literal.cpp
  *  \brief     Implementation of a literal element of an Expression.
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */
  
#include <iostream>
#include "../../include/Expression_tree/Expr_literal.h"

namespace genevalmag
{

#ifdef _DEBUG
    /* Numbers of literals current in the system. */
    static unsigned short literals(0);
#endif

/**
  * Constructor empty of Expr_literal.
  */
Expr_literal::Expr_literal():Expr_leaf()
{
    #ifdef _DEBUG
        literals++;
    #endif
}

/**
  * Constructor copy of Expr_literal.
  */
Expr_literal::Expr_literal(const Expr_literal &other)
{
    copy(other);

    #ifdef _DEBUG
        literals++;
    #endif
}

/**
  * Destructor of Expr_literal.
  */
Expr_literal::~Expr_literal()
{
    destroy();

    #ifdef _DEBUG
        literals--;
        if(literals == 0)
        {
            cout << literals << " -> Literals" << endl;
        }
    #endif
}

/**
  * Operator assign(=) of Expr_literal.
  */
Expr_literal &Expr_literal::operator=(const Expr_literal &other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

/**
  * Method of copy the Expr_literal, STL-like C++.
  */
void Expr_literal::copy(const Expr_literal &other)
{
    value               = other.get_value();
    type                = other.get_type();
    parent              = other.get_parent();
    conflict            = other.get_conflict();
    type_synthetized    = other.get_type_synthetized();
}

/**
  * Method destroy Expr_literal, STL-like C++.
  */
void Expr_literal::destroy()
{
}

/**
  * Returns the type of the Expr_literal.
  */
literal_type Expr_literal::get_type() const
{
    return type;
}

/**
  * Returns the value of the Expr_literal.
  */
string Expr_literal::get_value() const
{
    return value;
}

/**
  * Sets the type of the Expr_literal.
  */
void Expr_literal::set_type(literal_type new_type)
{
    type = new_type;
}

/**
  * Sets the value of the Expr_literal.
  */
void Expr_literal::set_value(string new_value)
{
    value = new_value;
}

/**
  * Generate and return a string reprensentation of a Expr_literal.
  *
  * Result= literal
  *
  * Ex: 1      -> int
  *     1.0    -> float
  *     '1'    -> char
  *     "1"    -> string
  */
string Expr_literal::to_string() const
{
    string lit;

    switch(type)
    {
        case k_int:
        case k_float:
        {
            lit.append(value);
            break;
        }
        case k_char:
        {
            lit.append("'");
            lit.append(value);
            lit.append("'");
            break;
        }
        case k_string:
        {
            lit.append("\"");
            lit.append(value);
            lit.append("\"");
            break;
        }
        case k_bool:
        {
        	lit.append(value);
			break;
        }
    }
    return lit;
}

} /* end genevalmag */
