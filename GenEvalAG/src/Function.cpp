/**
  *  \file		Function.cpp
  *  \brief		Implementation of the methods the Function.h
  *  \date		26/11/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>
#include <climits>
#include <sstream>
#include "Function.h"

namespace genevalmag
{

#ifdef _DEBUG
	// Numbers of functions current in the system.
	static int funtions = 0;
#endif

/**
  * Contructor empty of function.
  */
Function::Function()
{
	f_mod			= k_prefix;
	f_prec			= UINT_MAX;
	f_assoc			= k_left;
	f_is_operator	= false;

	#ifdef _DEBUG
		funtions++;
	#endif
}

/**
  * Contructor copy of function.
  */
Function::Function(Function const &other)
{
	copy(other);

	#ifdef _DEBUG
		funtions++;
	#endif
}

/**
  * Destructor of the function.
  */
Function::~Function()
{
	destroy();

	#ifdef _DEBUG
		funtions--;
		if(funtions == 0)
		cout << funtions << " -> Funtions" << endl;
	#endif
}

/**
  * Operator assign(=) of function.
  */
Function &Function::operator=(Function const &other)
{
	if(this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

/**
  * Method of copy the function, STL-like C++.
  */
void Function::copy(Function const &other)
{
	f_name			= other.get_name();
	f_domain		= other.get_domain();
	f_image			= other.get_image();
	f_mod			= other.get_mode();
	f_prec			= other.get_prec();
	f_assoc			= other.get_oper_assoc();
	f_is_operator	= other.is_operator();
}

/**
  * Method destroy function, STL-like C++.
  */
void Function::destroy()
{
}

/**
  * Return the name of the function.
  */
string Function::get_name() const
{
	return f_name;
}

/**
  * Return the domain of the function.
  */
vector<Sort*> Function::get_domain() const
{
	return f_domain;
}

/**
  * Return the image of the function.
  */
Sort *Function::get_image() const
{
	return f_image;
}

/**
  * Return the mode of the operator.
  */
oper_mode Function::get_mode() const
{
	return f_mod;
}

/**
  * Return the precedence of the operator.
  */
unsigned int Function::get_prec() const
{
	return f_prec;
}

/**
  * Return the associativity of the operator.
  */
oper_assoc Function::get_oper_assoc() const
{
	return f_assoc;
}
/**
  * Return the arity of function.
  */
int Function::get_arity() const
{
	return f_domain.size();
}

/**
  * Set the name of the function.
  */
void Function::set_name(string name)
{
	f_name = name;
}

/**
  * Set the full sort domain of the function.
  */
void Function::set_domain(vector<Sort*> domain)
{
	f_domain = domain;
}

/**
  * Set the sort image of the function.
  */
void Function::set_image(Sort *image)
{
	f_image = image;
}

/**
  * Set the mode of the operator.
  * @param mode: string
  */
void Function::set_mode(string mode)
{
	if(mode.compare("infix") == 0)
		f_mod = k_infix;
	else if(mode.compare("prefix") == 0)
		f_mod = k_prefix;
	else if(mode.compare("postfix") == 0)
		f_mod = k_postfix;
	else
		// Default value.
		f_mod = k_prefix;
}

/**
  * Set the precedence of the operator.
  */
void Function::set_prec(int prec)
{
	f_prec = prec;
}

/**
  * Set the associativity of the operator.
  */
void Function::set_oper_assoc(string mod)
{
	if(mod.compare("left") == 0)
		f_assoc = k_left;
	else if(mod.compare("right") == 0)
		f_assoc = k_right;
	else if(mod.compare("non-assoc") == 0)
		f_assoc = k_nonassoc;
	else
		// Default value.
		f_assoc = k_left;
}

/**
  * Set the boolean attribute with the parameter.
  */
void Function::set_is_operator(bool value)
{
	f_is_operator = value;
}
/**
  * Enqueue a sort in the domain of the function.
  */
void Function::add_domain(Sort *sort)
{
	f_domain.push_back(sort);
}

/**
  * Generate and return a string reprensentation of a function.
  *
  * Result= "function" <name> ":" <domain> "->" <image> ";"
  *
  * where <domain> is= <sort_1> ["(" <instance> ")" IF DEBUG IS ON] "," ... "," <sort_n> ["(" <instance> ")" IF DEBUG IS ON]
  */
string Function::to_string() const
{
	string func;

	if(is_operator())
	{
		func.append("op ");
		switch(f_mod)
		{
			case k_infix:   func.append("infix");   break;
			case k_prefix:  func.append("prefix");  break;
			case k_postfix: func.append("postfix"); break;
		}
		func.append("\t(");
		if(f_prec == UINT_MAX)
		{
			// Default precedence.
			func.append("_");
		}
		else
		{
			stringstream prec;
			prec << f_prec;
			func.append(prec.str());
		}
		func.append(", ");
		switch(f_assoc)
		{
			case k_left:	 func.append("left");	  break;
			case k_right:	 func.append("right");	 break;
			case k_nonassoc: func.append("non-assoc"); break;
		}
		func.append(") ");
	}
	else
	{
		func.append("function\t");
	}

	func.append(f_name);
	func.append(": ");
	for(vector<Sort>::size_type i = 0; i < f_domain.size(); i++)
	{
		func.append(f_domain[i]->get_name());

		#ifdef _DEBUG
			func.append("(");
			stringstream ins;
			ins << f_domain[i]->get_ins();
			func.append(ins.str());
			func.append(")");
		#endif

		if(i+1 < f_domain.size())
			func.append(", ");
	}
	func.append(" -> ");
	func.append(f_image->get_name());

	#ifdef _DEBUG
		func.append("(");
		stringstream ins;
		ins << f_image->get_ins();
		func.append(ins.str());
		func.append(")");
	#endif

	func.append(";");
	return func;
}

/**
  * Return true if the function is a Operator.
  */
bool Function::is_operator() const
{
	return f_is_operator;
}

/**
  * Compares the function with other.
  */
bool Function::equals(Function const &other) const
{
	return	key().compare(other.key()) == 0;
}

/**
  * Generate and return the string key that identifies a function definitely.
  *
  * Result= <name> <domain> <image>
  *
  * where <domain> is= <sort_1> ... <sort_n>
  */
string Function::key() const
{
	string key;

	if(is_operator())
	{
	   switch(f_mod)
		{
			case k_infix:   key.append("infix");   break;
			case k_prefix:  key.append("prefix");  break;
			case k_postfix: key.append("postfix"); break;
		}
	}

	key.append(f_name);
	for(vector<Sort>::size_type i = 0; i < f_domain.size(); i++)
	{
		key.append(f_domain[i]->get_name());
	}

	// ALERTA: HACE FALTA? A MISMO NOMBRE MODO Y ARIDA (DOMINIO), LA IMAGEN DISTINTA NO TE SOLUCIONA CUAL FUNCION USAR.
	//key.append(f_image->get_name());
	return key;
}

//void Function::purge()
//{
//	f_domain.clear();
//	f_image = NULL;
//}

} // end genevalmag
