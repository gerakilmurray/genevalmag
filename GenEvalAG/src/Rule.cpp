/*
 * Rule.cpp
 *
 *  Created on: 05/11/2009
 *      Author: gera
 */

#include "Rule.h"

namespace genevalmag {

Rule::Rule() {
	// TODO Auto-generated constructor stub

}

Rule::~Rule() {
	// TODO Auto-generated destructor stub
}

void Rule::setLeft_symbol(const Symbol symb)
{
	this->left_symbol = symb;
}

void Rule::addRight_symbol(const Symbol symb)
{
	this->right_side.push_back(symb);
}

Symbol Rule::getLeft_symbol()const
{
	return this->left_symbol;
}

vector<Symbol> Rule::getRight_side() const
{
	return this->right_side;
}

bool Rule::equals(Rule rule) const
{
	bool result = rule.getLeft_symbol().equals(this->left_symbol);
	size_t i = 0;
	while (result && (i < this->right_side.size()))
	{
		result = this->right_side[i].equals(rule.getRight_side()[i]);
		i++;
	}
	return result;
}

string Rule::to_string() const
{
	string rule;
	rule.append("rule\t");
	rule.append((this->getLeft_symbol()).getName());
	rule.append("\t::= ");
	for (vector<Symbol>::size_type i = 0; i < this->right_side.size(); ++i)
	{
		rule.append(this->right_side[i].getName());
		if (i+1<this->right_side.size())
			rule.append(" ");
	}
	rule.append(";");
	return rule;
}


}
