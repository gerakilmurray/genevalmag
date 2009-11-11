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
	o_name = name;
	o_domain = *v;
	o_image = *img;
	o_id = id;
}

Operator::Operator()
{
	o_mod = k_prefix;
	o_pred = 1000;
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
vector<Sort> Operator::get_domain() const
{
    return o_domain;
}

int Operator::get_id() const
{
    return o_id;
}

Sort Operator::get_image() const
{
    return o_image;
}

string Operator::get_mod() const
{
    switch (o_mod)
    {
		case k_infix: return "infix";
		case k_prefix: return "prefix";
		case k_suffix: return "suffix";
		default: return "prefix";
    }
}

string Operator::get_name() const
{
    return o_name;
}

int Operator::get_pred() const
{
    return o_pred;
}

void Operator::set_domain(vector<Sort> domain)
{
    o_domain = domain;
}

void Operator::set_id(int id)
{
    o_id = id;
}

void Operator::set_image(Sort image)
// CONVENDRIA TOMAR REFERENCIA EN ESTE PUNTO
{
    o_image = image;
}

void Operator::set_mod(string mod)
{
	if (mod.compare("infix") == 0)
		o_mod = k_infix;
	else if (mod.compare("prefix") == 0)
		o_mod = k_prefix;
	else if (mod.compare("suffix") == 0)
		o_mod = k_suffix;
	else
		// default
		o_mod = k_prefix;
}

void Operator::set_name(string name)
{
    o_name = name;
}

void Operator::set_pred(int pred)
{
    o_pred = pred;
}

///////////////////////////////////////////////
// Operator to string
///////////////////////////////////////////////
string Operator::to_string() const
{
	string op;
	op.append("op\t");
	op.append(get_mod());
	op.append(" (");
	std::stringstream pred;
	pred << get_pred();
	op.append(pred.str());
	op.append(") ");
	op.append(get_name());
	op.append(": ");
	for (vector<Sort>::size_type i = 0; i < o_domain.size(); ++i)
	{
		op.append(o_domain[i].get_name());
		if (i+1<o_domain.size())
			op.append(", ");
	}
	op.append(" :=> ");
	op.append(get_image().get_name());
	op.append(";");
	return op;
}
///////////////////////////////////////////////
// add a sort in the domain of a function
///////////////////////////////////////////////
void Operator::add_domain(Sort sort)
// CONVENDRIA TOMAR REFERENCIA EN ESTE PUNTO
{
	o_domain.push_back(sort);
}

///////////////////////////////////////////////
// compares the operation with other.
///////////////////////////////////////////////
bool Operator::equals(Operator op) const
{
	bool eq(false);
	eq = (o_name.compare(op.get_name())== 0) &&
		 (o_image.equals(op.get_image())) &&
		 (o_mod == op.o_mod) &&     // esta mal esto--> op deberia usarse con get!!!!
		 (o_pred == op.get_pred()) &&
		 (o_domain.size() == op.get_domain().size());

	if (!eq) return false;
	else
	{
		for (vector<Sort>::size_type i = 0; i < o_domain.size(); ++i)
		{
			eq = o_domain.at(i).equals(op.get_domain().at(i));
			if (!eq) return false;
		}
	}
	return eq;// si llega a este punto, obvio es verdadero.
}

}
