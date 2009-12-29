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
	parent = NULL;

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
	{
		string op;
		switch(func->get_mode())
		{
			case k_infix:
				op.append(childs[0]->to_string());
				op.append(" ");
				op.append(func->get_name());
				op.append(" ");
				op.append(childs[1]->to_string());
				break;
			case k_prefix:
				op.append(func->get_name());
				op.append("(");
				op.append(childs[0]->to_string());
				op.append(")");
				break;
			case k_postfix:
				op.append("(");
				op.append(childs[0]->to_string());
				op.append(")");
				op.append(func->get_name());
				break;
		}
		return op;
	}
	string fun(func->get_name());
	fun.append("(");
	for (unsigned int i=0; i < childs.size() ;i++)
	{
		fun.append(childs[i]->to_string());
		if (i < childs.size()-1) fun.append(", ");
	}
	fun.append(")");
	return fun;
}

} // end genevalmag
