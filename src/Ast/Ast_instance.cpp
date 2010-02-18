/**
  *  \file		Ast_instance.cpp
  *  \brief
  *  \date		21/12/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */
  
#include <sstream>
#include <iostream>

#include "Ast_instance.h"

namespace genevalmag
{
#ifdef _DEBUG
	// Numbers of instances current in the system.
	static int ast_instances = 0;
#endif

Ast_instance::Ast_instance()
{
	parent		= NULL;
	conflict	= -1;

	#ifdef _DEBUG
		ast_instances++;
	#endif
}

Ast_instance::Ast_instance(Ast_instance const &other)
{
	copy(other);

	#ifdef _DEBUG
		ast_instances++;
	#endif
}

Ast_instance::~Ast_instance()
{
	destroy();

	#ifdef _DEBUG
		ast_instances--;
		if(ast_instances == 0)
			cout << ast_instances << " -> AST Instances" << endl;
	#endif
}

Ast_instance &Ast_instance::operator=(Ast_instance const &other)
{
	if(this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

void Ast_instance::destroy()
{
	i_symb = NULL;
	i_attr = NULL;
}

void Ast_instance::copy(Ast_instance const &other)
{
	i_symb				= other.get_symb();
	i_num				= other.get_num();
	i_attr				= other.get_attr();
	parent				= other.get_parent();
	conflict			= other.get_conflict();
	type_synthetized	= other.get_type_synthetized();
}

const Attribute *Ast_instance::get_attr() const
{
	return i_attr;
}

unsigned short Ast_instance::get_num() const
{
	return i_num;
}

const Symbol *Ast_instance::get_symb() const
{
	return i_symb;
}

void Ast_instance::set_attr(const Attribute *attr)
{
	i_attr = attr;
}

void Ast_instance::set_num(unsigned short num)
{
	i_num = num;
}

void Ast_instance::set_symb(const Symbol *symb)
{
	i_symb = symb;
}

/**
  * Generate and return a string reprensentation of a instance.
  *
  * Result= <symbol>[number].<attribute>
  *
  * Ex: E[0].valor
  */
string Ast_instance::to_string() const
{
	string inst;
	// Save symbol's name.
	inst.append(i_symb->get_name());
	// Save instance number.
	inst.append("[");
	stringstream ins;
	ins << i_num;
	inst.append(ins.str());
	inst.append("]");
	inst.append(".");
	// Save attribute's name.
	inst.append(i_attr->get_name());
	return inst;
}

/**
  * Compares the Ast_instance with other.
  */
bool Ast_instance::equals(Ast_instance const &other) const
{
	return	key().compare(other.key()) == 0;
}

string Ast_instance::key() const
{
	string inst;
	// Save symbol's name.
	inst.append(i_symb->get_name());
	// Save instance number.
	stringstream ins;
	ins << i_num;
	inst.append(ins.str());
	// Save attribute's name.
	inst.append(i_attr->get_name());
	return inst;
}

} // end genevalmag
