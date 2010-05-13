/**
  *  \file      Expr_function.cpp
  *  \brief     Implementation of a function element of an Attribute Syntax Tree (AST).
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */
  
#include <iostream>

#include "../../include/Expression_tree/Expr_function.h"

namespace genevalmag
{

#ifdef _DEBUG
    /* Numbers of functions current in the system. */
    static unsigned short ast_functions(0);
#endif

/**
  * Constructor empty of Expr_function.
  */
Expr_function::Expr_function():Expr_node()
{
    precedence_level    = 0;
    syntax_order        = 0;

    #ifdef _DEBUG
        ast_functions++;
    #endif
}

/**
  * Constructor copy of Expr_function.
  */
Expr_function::Expr_function(const Expr_function &other)
{
    copy(other);

    #ifdef _DEBUG
        ast_functions++;
    #endif
}

/**
  * Destructor of Expr_function.
  */
Expr_function::~Expr_function()
{
    destroy();

    #ifdef _DEBUG
        ast_functions--;
        if(ast_functions == 0)
        {
            cout << ast_functions << " -> AST Functions" << endl;
        }
    #endif
}

/**
  * Operator assign(=) of Expr_function.
  */
Expr_function &Expr_function::operator=(const Expr_function &other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

/**
  * Method of copy the Expr_function, STL-like C++.
  */
void Expr_function::copy(const Expr_function &other)
{
    func                = other.get_function();
    precedence_level    = other.get_precedence_level();
    syntax_order        = other.get_syntax_order();
    childs              = other.get_childs();
    parent              = other.get_parent();
    conflict            = other.get_conflict();
    type_synthetized    = other.get_type_synthetized();
}

/**
  * Method destroy Expr_function, STL-like C++.
  */
void Expr_function::destroy()
{
}

/**
  * Returns the function pointer of the Expr_function.
  */
const Function *Expr_function::get_function() const
{
    return func;
}

/**
  * Returns the precedence level of the Expr_function.
  */
unsigned short Expr_function::get_precedence_level() const
{
    return precedence_level;
}

/**
  * Returns the syntax order of the Expr_function.
  */
unsigned short Expr_function::get_syntax_order() const
{
    return syntax_order;
}

/**
  * Sets the function pointer of the Expr_function.
  */
void Expr_function::set_function(const Function *function)
{
    func = function;
}

/**
  * Sets the precedence level of the Expr_function.
  */
void Expr_function::set_precedence_level(unsigned short p_level)
{
    precedence_level = p_level;
}

/**
  * Sets the syntax order of the Expr_function.
  */
void Expr_function::set_syntax_order(unsigned short s_order)
{
    syntax_order = s_order;
}

/**
  * Returns if the function of Expr_function is prefix.
  */
bool Expr_function::is_prefix() const
{
    return (func->get_mode() == k_prefix);
}

/**
  * Returns if the function of Expr_function is infix.
  */
bool Expr_function::is_infix() const
{
    return (func->get_mode() == k_infix);
}

/**
  * Returns if the function of Expr_function is postfix.
  */
bool Expr_function::is_postfix() const
{
    return (func->get_mode() == k_postfix);
}

/**
  * Returns if both Expr_functions are in the same precedence level.
  */
bool Expr_function::is_comparable(const Expr_function *other) const
{
    return (precedence_level == other->get_precedence_level());
}

/**
  * Return:
  *        = O        when is same precedence
  *        < 0        when other have great precedence
  *        > 0        when other have small precedence
  */
int Expr_function::compare_precedence(const Expr_function *other) const
{
    return (func->get_prec() - other->get_function()->get_prec());
}

/**
  * Return:
  *        = O        when is same order
  *        < 0        when other have great order
  *        > 0        when other have small order
  */
int Expr_function::compare_order(const Expr_function *other) const
{
    return (syntax_order - other->get_syntax_order());
}

/**
  * Generate and return a string reprensentation of a Expr_function.
  *
  * If is a pure function:
  *     Result= \<func_name\> "(" child[0], ... , child[n] ")"
  *
  * If is an infix binary operator:
  *     Result= "(" child[0] \<op_name\> child[1] ")"
  *
  * If is an prefix unary operator:
  *     Result= \<op_name\> "(" child[0] ")"
  *
  * If is an postfix unary operator:
  *     Result= "(" child[0] ")" \<op_name\>
  */
string Expr_function::to_string() const
{
    if(func->is_operator())
    {
        string op;

        switch(func->get_mode())
        {
            case k_infix:
                op.append("(");
                op.append(childs[0]->to_string());
                op.append(" ");
                op.append(func->get_name());
                op.append(" ");
                op.append(childs[1]->to_string());
                op.append(")");
                break;
            case k_prefix:
                op.append(func->get_name());
                op.append("(");
                op.append(childs[0]->to_string());
                op.append(")");
                break;
            case k_postfix:
                op.append("(");
                op.append(childs[0]->to_string());
                op.append(")");
                op.append(func->get_name());
                break;
        }
        return op;
    }
    string fun(func->get_name());
    fun.append("(");
    for (unsigned int i(0); i < childs.size() ;i++)
    {
        fun.append(childs[i]->to_string());
        if (i < childs.size()-1) fun.append(", ");
    }
    fun.append(")");
    return fun;
}

} /* end genevalmag */
