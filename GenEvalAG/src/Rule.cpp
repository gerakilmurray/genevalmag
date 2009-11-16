/**
 * \file Rule.cpp
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 05/11/2009
 *  \author    Kilmurray, Gerardo Luis.
 *  \author    Picco, Gonzalo M.
 */

#include <iostream>

#include "Rule.h"

namespace genevalmag {

static int rls = 0;

Rule::Rule() {
	rls++;
	// TODO Auto-generated constructor stub

}

Rule::Rule(Rule const & other)
{
	rls++;
	copy(other);
}

Rule::~Rule() {
	rls--;
	//cout <<  "rules " << rls << endl;
	destroy();
}

void Rule::set_left_symbol( Symbol* symb)
{
	left_symbol = symb;
}

void Rule::add_right_symbol( Symbol* symb)
{
	right_side.push_back(symb);
}

Symbol* Rule::get_left_symbol()const
{
	return left_symbol;
}

vector<Symbol*> Rule::get_right_side() const
{
	return right_side;
}

vector <Equation> Rule::get_eqs() const
{
	return eqs;
}

Rule& Rule::operator= (Rule const& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

void Rule::copy(Rule const& other)
{
	left_symbol = other.get_left_symbol();
	right_side = other.get_right_side();
	eqs = other.get_eqs();
}

void Rule::destroy()
{
}

bool Rule::equals(Rule rule) const
{
	return	key().compare(rule.key()) == 0;
}

string Rule::to_string_not_eq() const
{
	string rule;
	rule.append("rule\t");
	rule.append((get_left_symbol())->get_name());
	rule.append("\t::= ");
	for (vector<Symbol>::size_type i = 0; i < right_side.size(); ++i)
	{
		rule.append(right_side[i]->get_name());
		if (i+1<right_side.size())
			rule.append(" ");
	}
	rule.append(";");
	return rule;
}

string Rule::to_string() const
{
	string rule = to_string_not_eq();
	// for para las eqs. obvio que cada eq se sabe imprimir.
	//rule.append(";");
	return rule;
}




string Rule::key() const
{
	string key;
	key.append((get_left_symbol())->get_name());
	for (vector<Symbol>::size_type i = 0; i < right_side.size(); ++i)
	{
		key.append(right_side[i]->get_name());
	}
	return key;
}
}
