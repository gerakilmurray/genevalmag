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
	parent				= NULL;
	conflict			= -1;
	precedence_level	= 0;
	syntax_order		= 0;

	#ifdef _DEBUG
		ast_functions++;
	#endif
}

Ast_function::Ast_function(Ast_function const &other)
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
			cout << ast_functions << " -> AST Functions" << endl;
	#endif
}

Ast_function &Ast_function::operator=(Ast_function const &other)
{
	if(this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

void Ast_function::copy(Ast_function const &other)
{
	func				= other.get_function();
	precedence_level	= other.get_precedence_level();
	syntax_order		= other.get_syntax_order();
	childs				= other.get_childs();
	parent				= other.get_parent();
	conflict			= other.get_conflict();
	type_synthetized	= other.get_type_synthetized();
}

void Ast_function::destroy()
{
}

Function *Ast_function::get_function() const
{
	return func;
}

unsigned short Ast_function::get_precedence_level() const
{
	return precedence_level;
}

unsigned short Ast_function::get_syntax_order() const
{
	return syntax_order;
}

void Ast_function::set_function(Function *function)
{
	func = function;
}

void Ast_function::set_precedence_level(unsigned short p_level)
{
	precedence_level = p_level;
}

void Ast_function::set_syntax_order(unsigned short s_order)
{
	syntax_order = s_order;
}

bool Ast_function::is_prefix() const
{
	return (func->get_mode() == k_prefix);
}

bool Ast_function::is_infix() const
{
	return (func->get_mode() == k_infix);
}

bool Ast_function::is_postfix() const
{
	return (func->get_mode() == k_postfix);
}

bool Ast_function::is_comparable(Ast_function * other) const
{
	return (precedence_level == other->get_precedence_level());
}

/**
  * Return:
  * 	= O		when is same precedence
  *		< 0		when other have great precedence
  *		> 0		when other have small precedence
  */
int Ast_function::compare_precedence(Ast_function * other) const
{
	return (func->get_prec() - other->get_function()->get_prec());
}

/**
  * Return:
  * 	= O		when is same order
  *		< 0		when other have great order
  *		> 0		when other have small order
  */
int Ast_function::compare_order(Ast_function * other) const
{
	return (syntax_order - other->get_syntax_order());
}

string Ast_function::to_string() const
{
	if(func->is_operator())
	{
		string op;

		switch(func->get_mode())
		{
			case k_infix:
				op.append("(");
				op.append(childs[0]->to_string());
				op.append(" ");
				op.append(func->get_name());
				op.append(" ");
				op.append(childs[1]->to_string());
				op.append(")");
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
