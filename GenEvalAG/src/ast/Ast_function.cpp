/**
  *  \file		Ast_function.cpp
  *  \brief
  *  \date		21/12/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include "Ast_function.h"

namespace genevalmag
{

Ast_function::Ast_function()
{
}

Ast_function::Ast_function(Ast_function const & other)
{
	copy(other);
}

Ast_function::~Ast_function()
{
}

Ast_function& Ast_function::operator= (Ast_function const & other)
{
	if (this != &other)
	{
		destroy ();
		copy (other);
	}
	return *this;
}

void Ast_function::copy(Ast_function const & other)
{
	func				= other.get_function();
	childs				= other.get_childs();
	parent				= other.get_parent();
	type_node			= other.get_node_type();
	type_synthetized	= other.get_type_synthetized();
}

void Ast_function::destroy()
{
}

Function* Ast_function::get_function() const
{
    return func;
}

void Ast_function::set_function(Function* function)
{
    func = function;
}

string Ast_function::to_string() const
{
	return func->get_name();
}

} // end genevalmag
