/**
  *  \file      Ast_literal.cpp
  *  \brief     Implementation of a literal element of an Attribute Syntax Tree (AST).
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */
  
#include <iostream>
#include "Ast_literal.h"

namespace genevalmag
{

#ifdef _DEBUG
    /* Numbers of literals current in the system. */
    static int ast_literals(0);
#endif

/**
  * Constructor empty of Ast_literal.
  */
Ast_literal::Ast_literal()
{
    parent      = NULL;
    conflict    = -1;

    #ifdef _DEBUG
        ast_literals++;
    #endif
}

/**
  * Constructor copy of Ast_literal.
  */
Ast_literal::Ast_literal(const Ast_literal &other)
{
    copy(other);

    #ifdef _DEBUG
        ast_literals++;
    #endif
}

/**
  * Destructor of Ast_literal.
  */
Ast_literal::~Ast_literal()
{
    destroy();

    #ifdef _DEBUG
        ast_literals--;
        if(ast_literals == 0)
        {
            cout << ast_literals << " -> AST Literals" << endl;
        }
    #endif
}

/**
  * Operator assign(=) of Ast_literal.
  */
Ast_literal &Ast_literal::operator=(const Ast_literal &other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

/**
  * Method of copy the Ast_literal, STL-like C++.
  */
void Ast_literal::copy(const Ast_literal &other)
{
    value               = other.get_value();
    type                = other.get_type();
    parent              = other.get_parent();
    conflict            = other.get_conflict();
    type_synthetized    = other.get_type_synthetized();
}

/**
  * Method destroy Ast_literal, STL-like C++.
  */
void Ast_literal::destroy()
{
}

/**
  * Returns the type of the Ast_literal.
  */
literal_type Ast_literal::get_type() const
{
    return type;
}

/**
  * Returns the value of the Ast_literal.
  */
string Ast_literal::get_value() const
{
    return value;
}

/**
  * Sets the type of the Ast_literal.
  */
void Ast_literal::set_type(literal_type new_type)
{
    type = new_type;
}

/**
  * Sets the value of the Ast_literal.
  */
void Ast_literal::set_value(string new_value)
{
    value = new_value;
}

/**
  * Generate and return a string reprensentation of a Ast_literal.
  *
  * Result= literal
  *
  * Ex: 1      -> int
  *     1.0    -> float
  *     '1'    -> char
  *     "1"    -> string
  */
string Ast_literal::to_string() const
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
    }
    return lit;
}

} /* end genevalmag */
