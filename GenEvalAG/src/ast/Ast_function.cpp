/**
  *  \file		Ast_function.cpp
  *  \brief
  *  \date		21/12/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */
  
#include <iostream>
#include "Ast_function.h"

namespace genevalmag
{
#ifdef _DEBUG
	// Numbers of functions current in the system.
	static int ast_functions = 0;
#endif

Ast_function::Ast_function()
{
#ifdef _DEBUG
	ast_functions++;
#endif
}

Ast_function::Ast_function(Ast_function const & other)
{
	copy(other);

	#ifdef _DEBUG
		ast_functions++;
	#endif
}

Ast_function::~Ast_function()
{
	destroy();

	#ifdef _DEBUG
		ast_functions--;
		if(ast_functions == 0)
			cout << ast_functions <<" -> AST Functions" << endl;
	#endif
}

Ast_function& Ast_function::operator=(Ast_function const & other)
{
	if(this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

void Ast_function::copy(Ast_function const & other)
{
	func				= other.get_function();
	childs				= other.get_childs();
	parent				= other.get_parent();
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
	if(func->is_operator())
		return func->get_name();
	else
		return func->get_name().append("(");
}

} // end genevalmag
