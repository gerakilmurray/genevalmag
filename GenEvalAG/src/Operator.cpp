/**
 * \file Operator.cpp
 * 	\brief Implements Operator.h
 *  \date 28/09/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#include "Operator.h"
#include <iostream>
#include <sstream>

using namespace std;

namespace genevalmag {

///////////////////////////////////////////////
// contructors
///////////////////////////////////////////////
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
///////////////////////////////////////////////
// destructors
///////////////////////////////////////////////
Operator::~Operator()
{
	// TODO Auto-generated destructor stub
}

///////////////////////////////////////////////
// Setter and getters.
///////////////////////////////////////////////
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
		case k_suffix: return "suffix";
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
	else if (o_mod.compare("suffix") == 0)
		this->o_mod = k_suffix;
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

///////////////////////////////////////////////
// Operator to string
///////////////////////////////////////////////
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
///////////////////////////////////////////////
// add a sort in the domain of a function
///////////////////////////////////////////////
void Operator::add_domain(Sort s)
{
	this->o_domain.push_back(s);

}

///////////////////////////////////////////////
// compares the operation with other.
///////////////////////////////////////////////
bool Operator::equals(Operator op)
{
	bool eq(false);
	eq = (this->o_name.compare(op.getName())== 0) &&
		 (this->o_image.equals(op.getImage())) &&
		 (this->o_mod == op.o_mod) &&     // esta mal esto--> op deberia usarse con get!!!!
		 (this->o_pred == op.getPred()) &&
		 (this->o_domain.size() == op.getDomain().size());

	if (!eq) return false;
	else
	{
		for (vector<Sort>::size_type i = 0; i < this->o_domain.size(); ++i)
		{
			eq = this->o_domain.at(i).equals(op.getDomain().at(i));
			if (!eq) return false;
		}
	}
	return eq;// si llega a este punto, obvio es verdadero.
}

}
