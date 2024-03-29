/**
  *  \file      Rule.cpp
  *  \brief     Implementation of the methods the Rule.h
  *  \date      05/11/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>
#include <sstream>
#include <assert.h>

#include "../../include/Attr_grammar/Rule.h"

using namespace std;

namespace genevalmag
{

vector<Equation*> index_access_eq;

/**
  * Constructor empty of rule.
  */
Rule::Rule()
{
    r_offset = 0;
}

/**
  * Constructor copy of rule.
  */
Rule::Rule(const Rule &other)
{
    copy(other);
}

/**
  * Destructor of rule.
  */
Rule::~Rule()
{
    destroy();
}

/**
  * Operator assign(=) of rule.
  */
Rule &Rule::operator=(const Rule &other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

/**
  * Method of copy the rule, STL-like C++.
  */
void Rule::copy(const Rule &other)
{
    r_id             = other.key();
    r_left_symbol    = other.get_left_symbol();
    r_right_side     = other.get_right_side();
    r_eqs            = other.get_eqs();
    r_offset         = other.get_offset();
}

/**
  * Method destroy rule, STL-like C++.
  */
void Rule::destroy()
{
}

/**
  * Returns the left symbol of the rule.
  */
const Symbol *Rule::get_left_symbol() const
{
    return r_left_symbol;
}

/**
  * Returns the right side of the rule.
  */
const vector<const Symbol*> &Rule::get_right_side() const
{
    return r_right_side;
}

/**
  * Returns the equations of the rule.
  */
const map<unsigned short, Equation> &Rule::get_eqs() const
{
    return r_eqs;
}

/**
  * Returns the number of equations of the rule.
  */
const size_t Rule::get_number_eqs() const
{
    return r_eqs.size();
}

/**
  * Returns the offset of all equation of the rule.
  */
const unsigned short Rule::get_offset() const
{
    return r_offset;
}

/**
  * Returns the i-equation of the rule.
  */
const Equation *Rule::get_eq(const unsigned short index) const
{
    map<unsigned short, Equation>::const_iterator it(r_eqs.find(index));
    if(it == r_eqs.end())
    {
        return NULL;
    }
    else
    {
        return &(it->second);
    }
}

/**
  * Sets the identificator of the rule.
  */
void Rule::set_id(const unsigned short id)
{
    r_id = id;
}

/**
  * Sets the left symbol of the rule.
  */
void Rule::set_left_symbol(const Symbol *left_symb)
{
    r_left_symbol = left_symb;
}

/**
  * Enqueues a symbol in the right side of the rule.
  */
void Rule::add_right_symbol(const Symbol *right_symb)
{
    r_right_side.push_back(right_symb);
}

/**
  * Checks that the equation is not already defined in the rule.
  */
const bool Rule::defined_equation(const Equation &eq) const
{
    for(map<unsigned short,Equation>::const_iterator it(r_eqs.begin()); it != r_eqs.end(); it++)
    {
        if (it->second.get_l_value()->equals(eq.get_l_value()))
        {
            return true;
        }
    }
    return false;
}

/**
  * Checks that symbol is a non-terminal into the rule.
  */
const bool Rule::belongs_non_terminal(const Symbol &non_term) const
{
    if(non_term.equals(*r_left_symbol))
    {
        return true;
    }
    for(vector<const Symbol*>::size_type i(0); i < r_right_side.size(); i++)
    {
        if (non_term.equals(*r_right_side.at(i)))
        {
            return true;
        }
    }
    return false;
}

/**
  * Enqueues a equation in the list of the rule.
  */
const bool Rule::add_eq(Equation &eq)
{
    static unsigned short id_eq(1);

    if (defined_equation(eq))
    {
        /* The equation is already defined then it isn't inserted.
         * The map does not accept the overhead of the equations.
         */
        return false;
    }
    eq.set_id(id_eq);

    pair<unsigned short,Equation> new_eq(id_eq++, eq);
    pair<map<unsigned short, Equation>::iterator, bool > result(r_eqs.insert(new_eq));

    /* Update de offset of the rule */
    r_offset = id_eq - get_number_eqs();
    assert(result.second);
    return true;
}

/**
  * Generates and returns a string reprensentation of a Rule.\n
  *\n
  * Result = \<left_symbol\> "::=" \<right_side\>\n
  *                                     "compute"\n
  *                                             eq_1\n
  *                                             ...\n
  *                                             eq_n\n
  *                                     "end;"\n
  *\n
  * where \<right_ride\> is s= symbol_1 " " ... " " symbol_n\n
  */
const string Rule::to_string() const
{
    string rule(to_string_not_eqs());
    if(!r_eqs.empty())
    /* If r_eqs is empty not show it the compute's block. */
    {
        rule.append("\n            compute\n");
        for(map<unsigned short,Equation>::const_iterator it(r_eqs.begin()); it != r_eqs.end(); it++)
        {
            rule.append("                ");
            rule.append(it->second.to_string());
            rule.append("\n");
        }
        rule.append("            end");
    }
    rule.append(";\n");
    return rule;
}

/**
  * Generates and returns a string reprensentation of a rule.
  *
  * Result = left_symbol "::=" right_side ";"
  *
  * where right_ride is= symbol_1 " " ... " " symbol_n
  */
const string Rule::to_string_not_eqs() const
{
    string rule("/*R");

    stringstream key_rule;
    key_rule << r_id;
    rule.append(key_rule.str());

    rule.append("*/ ");

    rule.append(r_left_symbol->get_name());
    rule.append(" ::= ");
    for(vector<const Symbol*>::size_type i(0); i < r_right_side.size(); i++)
    {
        rule.append(r_right_side[i]->get_name());
        if(i+1 < r_right_side.size())
        {
            rule.append(" ");
        }
    }
    return rule;
}

/**
  * Compares the rule with other.
  */
const bool Rule::equals(const Rule &other) const
{
    if(r_left_symbol->equals(*(other.get_left_symbol())))
    {
    	if (r_right_side.size() != other.get_right_side().size())
    	{
    		return false;
    	}

        for(size_t i(0); i < r_right_side.size(); i++)
        {
            if (!r_right_side[i]->equals(*(other.get_right_side()[i])))
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

/**
  * Returns the number key that identifies a rule definitely.
  *
  * Result = \<id_rule\>
  */
const unsigned short Rule::key() const
{
    return r_id;
}

/**
  * Returns the count of ocurrences of these symbol in the rule.
  */
const int Rule::count_non_terminal(const Symbol *symb) const
{
    int count(0);
    if(symb->equals(*r_left_symbol))
    {
        count++;
    }
    for(vector<const Symbol*>::size_type i(0); i < r_right_side.size(); i++)
    {
        if (r_right_side[i]->is_non_terminal() && symb->equals(*r_right_side[i]))
        {
            count++;
        }
    }
    return count;
}

/**
  * Returns the non-terminals symbols the right side of the rule.
  */
const vector<const Symbol*> Rule::get_non_terminals_right_side() const
{
    vector<const Symbol*> result;
    for(size_t i(0); i < r_right_side.size(); i++)
    {
        if (r_right_side[i]->is_non_terminal())
        {
            result.push_back(r_right_side[i]);
        }
    }
    return result;
}

} /* end genevalmag */
