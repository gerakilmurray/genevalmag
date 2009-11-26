/**
 * \file Function.cpp
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 26/11/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#include "Function.h"
#include <sstream>

namespace genevalmag {

static int funtions = 0;

///////////////////////////////////////////////
// contructors
///////////////////////////////////////////////
Function::Function(string name, vector <Sort*> * vec, Sort * img)
{
	funtions++;
	f_name = name;
	f_domain = *vec;
	f_image = img;
}

Function::Function()
{
	funtions++;
}

Function::Function(const Function & other)
{
	funtions++;
	copy(other);
}

void Function::destroy()
{
}

///////////////////////////////////////////////
// destructors
///////////////////////////////////////////////
Function::~Function()
{
	funtions--;
	//cout << funtions << " opers" << endl;
	destroy();
}

///////////////////////////////////////////////
// Setter and getters.
///////////////////////////////////////////////
vector<Sort*> Function::get_domain() const
{
    return f_domain;
}


Sort* Function::get_image() const
{
    return f_image;
}


string Function::get_name() const
{
    return f_name;
}


void Function::set_domain(vector<Sort*> domain)
{
    f_domain = domain;
}


void Function::set_image(Sort* image)
{
    f_image = image;
}

void Function::set_name(string name)
{
    f_name = name;
}

Function& Function::operator= (Function& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

void Function::copy(const Function& other)
{
	f_name		= other.get_name();
	f_domain	= other.get_domain();
	f_image		= other.get_image();

}


///////////////////////////////////////////////
// Function to string
///////////////////////////////////////////////
string Function::to_string()
{
	string op;
	op.append("function\t");

	op.append(get_name());
	op.append(": ");
	for (vector<Sort>::size_type i = 0; i < f_domain.size(); ++i)
	{
		op.append(f_domain[i]->get_name());
		op.append("(");
		std::stringstream id;
		id << f_domain[i]->get_id();
		op.append(id.str());
		op.append(")");
		if (i+1<f_domain.size())
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
void Function::add_domain(Sort* sort)
{
	f_domain.push_back(sort);
}

///////////////////////////////////////////////
// compares the operation with other.
///////////////////////////////////////////////
bool Function::equals(Function op) const
{
	return	key().compare(op.key()) == 0;
}

void Function::purge()
{
	f_domain.clear();
	f_image = NULL;
}

string Function::key() const
{
	string key;
	key.append(get_name());
	for (vector<Sort>::size_type i = 0; i < f_domain.size(); ++i)
	{
		key.append(f_domain[i]->get_name());
	}
	key.append(get_image()->get_name());

	return key;
}
}
