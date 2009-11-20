/**
 * \file Operator.cpp
 * 	\brief Implements Operator.h
 *  \date 28/09/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#include <iostream>
#include <sstream>

#include "Operator.h"

using namespace std;

namespace genevalmag {

static int ops = 0;

///////////////////////////////////////////////
// contructors
///////////////////////////////////////////////
Operator::Operator(string name, vector <Sort*> * v, Sort * img, int id)
{
	ops++;
	o_name = name;
	o_domain = *v;
	o_image = img;
	o_id = id;
}

Operator::Operator()
{
	ops++;
	o_mod = k_prefix;
	o_pred = 1000;
}

Operator::Operator(const Operator & other)
{
	ops++;
	copy(other);
}

void Operator::destroy()
{
}

///////////////////////////////////////////////
// destructors
///////////////////////////////////////////////
Operator::~Operator()
{
	ops--;
	//cout << ops << " opers" << endl;
	destroy();
}

///////////////////////////////////////////////
// Setter and getters.
///////////////////////////////////////////////
vector<Sort*> Operator::get_domain() const
{
    return o_domain;
}

int Operator::get_id() const
{
    return o_id;
}

Sort* Operator::get_image() const
{
    return o_image;
}

mod_op Operator::get_mod() const
{
	return o_mod;
}

string Operator::get_name() const
{
    return o_name;
}

int Operator::get_pred() const
{
    return o_pred;
}

void Operator::set_domain(vector<Sort*> domain)
{
    o_domain = domain;
}

void Operator::set_id(int id)
{
    o_id = id;
}

void Operator::set_image(Sort* image)
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
	else if (mod.compare("postfix") == 0)
		o_mod = k_postfix;
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


Operator& Operator::operator= (Operator& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

void Operator::copy(const Operator& other)
{
	o_name		= other.get_name();
	o_id		= other.get_id();
	o_domain	= other.get_domain();
	o_pred		= other.get_pred();
	o_image		= other.get_image();
	o_mod		= other.get_mod();
}


///////////////////////////////////////////////
// Operator to string
///////////////////////////////////////////////
string Operator::to_string()
{
	string op;
	op.append("op\t");
    switch (o_mod)
    {
		case k_infix:   op.append("infix");break;
		case k_prefix:  op.append("prefix");break;
		case k_postfix:  op.append("postfix");break;
		default: op.append("prefix");
    }

	op.append(" (");
	std::stringstream pred;
	pred << get_pred();
	op.append(pred.str());
	op.append(") ");
	op.append(get_name());
	op.append(": ");
	for (vector<Sort>::size_type i = 0; i < o_domain.size(); ++i)
	{
		op.append(o_domain[i]->get_name());
		op.append("(");
		std::stringstream id;
		id << o_domain[i]->get_id();
		op.append(id.str());
		op.append(")");
		if (i+1<o_domain.size())
			op.append(", ");
	}
	op.append(" :=> ");
	op.append(get_image()->get_name());
	op.append("(");
	std::stringstream id;
	id << get_image()->get_id();
	op.append(id.str());
	op.append(")");
	op.append(";");
	return op;
}
///////////////////////////////////////////////
// add a sort in the domain of a function
///////////////////////////////////////////////
void Operator::add_domain(Sort* sort)
// CONVENDRIA TOMAR REFERENCIA EN ESTE PUNTO
{
	o_domain.push_back(sort);
}

///////////////////////////////////////////////
// compares the operation with other.
///////////////////////////////////////////////
bool Operator::equals(Operator op) const
{
	return	key().compare(op.key()) == 0;
}

void Operator::purge()
{
	o_domain.clear();
	o_image = NULL;
	o_pred = 1000;
	o_mod = k_prefix;
}

string Operator::key() const
{
	string key;
    switch (o_mod)
	    {
			case k_infix:   key.append("infix");break;
			case k_prefix:  key.append("prefix");break;
			case k_postfix:  key.append("postfix");break;
			default: key.append("prefix");
	    }

//	std::stringstream pred;
//	pred << get_pred();
//	key.append(pred.str());
	key.append(get_name());
	for (vector<Sort>::size_type i = 0; i < o_domain.size(); ++i)
	{
		key.append(o_domain[i]->get_name());
	}
	key.append(get_image()->get_name());

	return key;
}
}
