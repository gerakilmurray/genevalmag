/**
 * \file Rule.cpp
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 05/11/2009
 *  \author    Kilmurray, Gerardo Luis.
 *  \author    Picco, Gonzalo M.
 */

#include "Rule.h"

namespace genevalmag {

Rule::Rule() {
	// TODO Auto-generated constructor stub

}

Rule::Rule(Rule const & other)
{
	copy(other);
}

Rule::~Rule() {
	destroy();
}

void Rule::set_left_symbol(const Symbol symb)
{
	left_symbol = symb;
}

void Rule::add_right_symbol(const Symbol symb)
{
	right_side.push_back(symb);
}

Symbol Rule::get_left_symbol()const
{
	return left_symbol;
}

vector<Symbol> Rule::get_right_side() const
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
	bool result = rule.get_left_symbol().equals(left_symbol);
	size_t i = 0;
	while (result && (i < right_side.size()))
	{
		result = right_side[i].equals(rule.get_right_side()[i]);
		i++;
	}
	return result;
}

string Rule::to_string() const
{
	string rule;
	rule.append("rule\t");
	rule.append((get_left_symbol()).get_name());
	rule.append("\t::= ");
	for (vector<Symbol>::size_type i = 0; i < right_side.size(); ++i)
	{
		rule.append(right_side[i].get_name());
		if (i+1<right_side.size())
			rule.append(" ");
	}
	rule.append(";");
	return rule;
}


}
