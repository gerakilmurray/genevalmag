/**
 * \file Operator.cpp
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 28/09/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#include "Operator.h"
#include <iostream>
#include <sstream>

using namespace std;

namespace genevalmag {

Operator::Operator(string name, vector <Sort> * v, Sort * img, int id)
{
	this->o_name = name;
	this->o_domain = *v;
	this->o_image = *img;
	this->o_id = id;
}

Operator::Operator()
{
	this->o_mod = k_prefix;
	this->o_pred = 1000;

}

Operator::~Operator()
{
	// TODO Auto-generated destructor stub
}

vector<Sort> Operator::getDomain() const
{
    return this->o_domain;
}

int Operator::getId() const
{
    return this->o_id;
}

Sort Operator::getImage() const
{
    return this->o_image;
}

string Operator::getMod() const
{
    switch (o_mod)
    {
		case k_infix: return "infix";
		case k_prefix: return "prefix";
		case k_sufix: return "sufix";
		default: return "prefix";
    }
}

string Operator::getName() const
{
    return this->o_name;
}

int Operator::getPred() const
{
    return this->o_pred;
}

void Operator::setDomain(vector<Sort> o_domain)
{
    this->o_domain = o_domain;
}

void Operator::setId(int o_id)
{
    this->o_id = o_id;
}

void Operator::setImage(Sort o_image)
{
    this->o_image = o_image;
}

void Operator::setMod(string o_mod)
{
	if (o_mod.compare("infix") == 0)
		this->o_mod = k_infix;
	else if (o_mod.compare("prefix") == 0)
		this->o_mod = k_prefix;
	else if (o_mod.compare("sufix") == 0)
		this->o_mod = k_sufix;
	else
		// default
		this->o_mod = k_prefix;
}

void Operator::setName(string o_name)
{
    this->o_name = o_name;
}

void Operator::setPred(int o_pred)
{
    this->o_pred = o_pred;
}
string Operator::to_string()
{
	string op;
	op.append("op ");
	op.append(this->getMod());
	op.append(" (");
	std::stringstream pred;
	pred << this->getPred();
	op.append(pred.str());
	op.append(") ");
	op.append(this->getName());
	op.append(": ");
	for (vector<Sort>::size_type i = 0; i < this->o_domain.size(); ++i)
	{
		op.append(this->o_domain[i].getName());
		if (i+1<this->o_domain.size())
			op.append(", ");
	}
	op.append(" :=> ");
	op.append(this->getImage().getName());
	op.append(";");
	return op;
}
void Operator::add_domain(Sort s)
{
	this->o_domain.push_back(s);

}
}
