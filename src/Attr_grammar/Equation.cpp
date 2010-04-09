/**
  *  \file      Equation.cpp
  *  \brief     Implementation of the methods the Equation.h
  *  \date      05/11/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <sstream>
#include <iostream>

#include "Equation.h"
#include "../Ast/Ast_literal.h"

namespace genevalmag
{

#ifdef _DEBUG
    /* Numbers of operators current in the system. */
    static int eqs(0);
#endif

/**
  * Constructor empty of equation.
  */
Equation::Equation()
{
    /* Initialize the counter. */
    count_ref = new unsigned int(1);

    #ifdef _DEBUG
        eqs++;
    #endif
}

/**
  * Contructor copy of Equation.
  */
Equation::Equation(const Equation &other)
{
    copy(other);

    #ifdef _DEBUG
        eqs++;
    #endif
}

/**
  * Destructor of equation.
  */
Equation::~Equation()
{
    /* Decrement the counter. */
    (*count_ref)--;

    destroy();

    #ifdef _DEBUG
        eqs--;
        if(eqs == 0)
        {
            cout << eqs << " -> Equations" << endl;
        }
    #endif
}

/**
  * Operator assign(=) of Equation.
  */
Equation &Equation::operator=(const Equation &other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

/**
  * Method of copy the equation, STL-like C++.
  */
void Equation::copy(const Equation &other)
{
    eq_id        = other.get_id();
    l_value      = *other.get_l_value();
    r_value      = other.get_r_value();
    count_ref    = other._get_count_ref();

    /* Increment the counter. */
    (*count_ref)++;
}

/**
  * Method destroy equation, STL-like C++.
  */
void Equation::destroy()
{
    /* Check if is the last reference. */
    if(*count_ref == 0)
    {
        /* Free all memory of the equation. */
        delete(count_ref);

        delete(r_value);
    }
}

/**
  * Return the count reference.
  */
unsigned int *Equation::_get_count_ref() const
{
    return count_ref;
}

/**
  * Return the l_value of the equation.
  */
const Ast_instance *Equation::get_l_value() const
{
    return &l_value;
}

/**
  * Return the r_value of the equation.
  */
const Ast_node *Equation::get_r_value() const
{
    return r_value;
}

/**
  * Returns the id of the equation.
  */
unsigned short Equation::get_id() const
{
    return eq_id;
}

/**
  * Sets the id of the equation.
  */
void Equation::set_id(unsigned short id)
{
    eq_id = id;
}

/**
  * Set the left value of the equation.
  */
void Equation::set_l_value(const Ast_instance &lvalue)
{
    l_value = lvalue;
}

/**
  * Set the left value of the equation.
  */
void Equation::set_r_value(Ast_node *rvalue)
{
    r_value = rvalue;
}

/**
  * Traverse the equation tree while saves only the Ast_leaf nodes in the vector result.
  */
void Equation::inorder_only_leaf(const Ast_node* head, vector<const Ast_leaf*> &result) const
{
    const Ast_inner_node* root(dynamic_cast<const Ast_inner_node*>(head));

    if(root)
    {
        for(size_t i(0); i < root->get_childs().size(); i++)
        {
            Ast_inner_node *child(dynamic_cast<Ast_inner_node*>(root->get_child(i)));

            if (child)
            {
                inorder_only_leaf(child,result);
            }
            else
            {
                Ast_leaf *child_leaf((Ast_leaf*)root->get_child(i));
                result.push_back(child_leaf);
            }
        }
    }
    else
    {
        Ast_leaf *root_leaf((Ast_leaf*)head);
        result.push_back(root_leaf);
    }
}

/**
  * Traverse the equation tree while saves only the Ast_instace nodes in the vector result.
  */
void Equation::inorder_only_instance(const Ast_node *head, vector<const Ast_instance*> &result) const
{
    const Ast_inner_node *root(dynamic_cast<const Ast_inner_node*>(head));

    if(root)
    {
        for(size_t i(0); i < root->get_childs().size(); i++)
        {
            Ast_inner_node *child(dynamic_cast<Ast_inner_node*>(root->get_child(i)));

            if (child)
            {
                inorder_only_instance(child, result);
            }
            else
            {
                Ast_instance *child_instace(dynamic_cast<Ast_instance*>(root->get_child(i)));
                if (child_instace)
                {
                    result.push_back(child_instace);
                }
            }
        }
    }
    else
    {
        Ast_instance *child_instace(dynamic_cast<Ast_instance*>((Ast_leaf*)head));
        if (child_instace)
        {
            result.push_back(child_instace);
        }
    }
}

/**
  * Returns the Ast_instance nodes of the right side of Ast tree.
  */
const vector<const Ast_instance*> Equation::get_instance_right_side() const
{
	vector<const Ast_instance*> result;
	inorder_only_instance(r_value, result);
	return result;
}

/**
  * Generate and return a string reprensentation of an Equation.
  *
  * Result= \<l_value\> "=" \<r_value\> ";"
  *
  * where \<l_value\> = "instance_attr" and \<r_value\> is= "list of node_ast"
  */
string Equation::to_string() const
{
    string eq("(");
    stringstream id_eq;
    id_eq << eq_id;
    eq.append(id_eq.str());
    eq.append(") ");

    eq.append(l_value.to_string());
    eq.append("\t=\t");
    eq.append(r_value->to_string());
    eq.append(";");
    return eq;
}

/**
  * Compares the equation with other.
  */
bool Equation::equals(const Equation &other) const
{
    return key().compare(other.key()) == 0;
}

/**
  * Generate and return the string key that identifies an Equation definitely.
  *
  * Result = \<l_value\>\<r_value\>
  *
  * where \<l_value\> = "instance_attr" and \<r_value\> is= "list of node_ast"
  */
string Equation::key() const
{
    string key(l_value.to_string());
    key.append(r_value->to_string());
    return key;
}

} /* end genevalmag */
