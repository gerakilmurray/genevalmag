/**
  *  \file		Rule.cpp
  *  \brief		Implementation of the methods the Rule.h
  *  \date		05/11/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>
#include <sstream>

#include "Rule.h"

namespace genevalmag
{

vector<Equation*> index_access_eq;

#ifdef _DEBUG
	// Numbers of symbols current in the system.
	static int rules = 0;
#endif

/**
  * Constructor empty of rule.
  */
Rule::Rule()
{
	#ifdef _DEBUG
		rules++;
	#endif
}

/**
  * Constructor copy of rule.
  */
Rule::Rule(Rule const &other)
{
	copy(other);

	#ifdef _DEBUG
		rules++;
	#endif
}

/**
  * Destructor of rule.
  */
Rule::~Rule()
{
	destroy();

	#ifdef _DEBUG
		rules--;
		if(rules == 0)
			cout << rules << " -> Rules" << endl;
	#endif
}

/**
  * Operator assign(=) of rule.
  */
Rule &Rule::operator=(Rule const &other)
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
void Rule::copy(Rule const &other)
{
	r_id			= other.key();
	r_left_symbol	= other.get_left_symbol();
	r_right_side	= other.get_right_side();
	r_eqs			= other.get_eqs();
}

/**
  * Method destroy rule, STL-like C++.
  */
void Rule::destroy()
{
}

/**
  * Return the left symbol of the rule.
  */
const Symbol *Rule::get_left_symbol() const
{
	return r_left_symbol;
}

/**
  * Return the right side of the rule.
  */
const vector<const Symbol*> &Rule::get_right_side() const
{
	return r_right_side;
}

/**
  * Return the equations of the rule.
  */
const map<unsigned short,Equation> &Rule::get_eqs() const
{
	return r_eqs;
}

/**
  * Return the i-equation of the rule.
  */
const Equation *Rule::get_eq(unsigned short index) const
{
	return &(r_eqs.find(index)->second);
}

/**
  * Sets the identificator of the rule.
  */
void Rule::set_id(unsigned short id)
{
    r_id = id;
}

/**
  * Set the left symbol of the rule.
  */
void Rule::set_left_symbol(const Symbol *left_symb)
{
	r_left_symbol = left_symb;
}

/**
  * Enqueue a symbol in the right side of the rule.
  */
void Rule::add_right_symbol(const Symbol *right_symb)
{
	r_right_side.push_back(right_symb);
}

bool Rule::defined_equation(const Equation &eq) const
{
	for(map<unsigned short,Equation>::const_iterator it = r_eqs.begin(); it != r_eqs.end(); it++)
	{
		if (it->second.get_l_value()->equals_with_index(eq.get_l_value()))
			return true;
	}
	return false;
}

bool Rule::belongs_non_terminal(const Symbol &non_term) const
{
	if(non_term.equals(*r_left_symbol))
	{
		return true;
	}
	for(vector<const Symbol*>::size_type i = 0; i < r_right_side.size(); i++)
	{
		if (non_term.equals(*r_right_side.at(i)))
		{
			return true;
		}
	}
	return false;
}

/**
  * Enqueue a equation in the list of the rule.
  */
bool Rule::add_eq(Equation &eq)
{
	static unsigned short cant_eq = 1;

	if (defined_equation(eq))
	{
		// The equation is already defined then it isn't inserted.
		// The map does not accept the overhead of the equations.
		return false;
	}

	eq.set_id(cant_eq++);

	pair<unsigned short,Equation> new_eq(eq.get_id(), eq);
	pair<map<unsigned short, Equation>::iterator, bool > result = r_eqs.insert(new_eq);
	return result.second;
}

/**
  * Generate and return a string reprensentation of a rule.
  *
  * Result= left_symbol "::=" right_side
  * 									"compute"
  *												eq_1
  * 											...
  * 											eq_n
  * 									"end;"
  *
  * where right_ride is= symbol_1 " " ... " " symbol_n
  */
string Rule::to_string() const
{
	string rule(to_string_not_eqs());
	if(!r_eqs.empty())
	// if r_eqs is empty not show it the compute's block.
	{
		rule.append("\n\t\t\tcompute\n");
		for(map<unsigned short,Equation>::const_iterator it = r_eqs.begin(); it != r_eqs.end(); it++)
		{
			rule.append("\t\t\t\t");
			rule.append(it->second.to_string());
			rule.append("\n");
		}
		rule.append("\t\t\tend");
	}
	rule.append(";\n");
	return rule;
}

/**
  * Generate and return a string reprensentation of a rule.
  *
  * Result= left_symbol "::=" right_side ";"
  *
  * where right_ride is= symbol_1 " " ... " " symbol_n
  */
string Rule::to_string_not_eqs() const
{
	string rule("R");

	stringstream key_rule;
	key_rule << r_id;
	rule.append(key_rule.str());

	rule.append(": ");

	rule.append(r_left_symbol->get_name());
	rule.append("\t::=\t");
	for(vector<const Symbol*>::size_type i = 0; i < r_right_side.size(); i++)
	{
		rule.append(r_right_side[i]->get_name());
		if(i+1 < r_right_side.size())
			rule.append(" ");
	}
	return rule;
}

/**
  * Compares the rule with other.
  */
bool Rule::equals(Rule const &other) const
{
	if(r_left_symbol->equals(*(other.get_left_symbol())))
	{
		for(vector<const Symbol*>::size_type i = 0; i < r_right_side.size(); i++)
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
  * Generate and return the string key that identifies a rule definitely.
  *
  * Result= left_symbol right_side
  *
  * where right_ride is= symbol_1> ... symbol_n
  */
unsigned short Rule::key() const
{
	return r_id;
}

int Rule::count_non_terminal(const Symbol *symb) const
{
	int count = 0;
	if(symb->equals(*r_left_symbol))
	{
		count++;
	}
	for(vector<const Symbol*>::size_type i = 0; i < r_right_side.size(); i++)
	{
		if (r_right_side[i]->is_non_terminal() && symb->equals(*r_right_side[i]))
		{
			count++;
		}
	}
	return count;
}

/**
  * Return the non-terminals symbols the right side of the rule.
  */
vector<const Symbol*> Rule::get_non_terminals_right_side() const
{
	vector<const Symbol*> result;
	for(vector<const Symbol*>::size_type i = 0; i < r_right_side.size(); i++)
	{
		if (r_right_side[i]->is_non_terminal())
		{
			result.push_back(r_right_side[i]);
		}
	}
	return result;
}

} // end genevalmag
