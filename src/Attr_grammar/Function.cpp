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
	/* Numbers of Functions current in the system. */
	static int funtions(0);
#endif

/**
  * Contructor empty of Function.
  */
Function::Function()
{
	f_mod			= k_prefix;
	f_prec			= USHRT_MAX;
	f_assoc			= k_left;
	f_is_operator	= false;

	#ifdef _DEBUG
		funtions++;
	#endif
}

/**
  * Contructor copy of Function.
  */
Function::Function(const Function &other)
{
	copy(other);

	#ifdef _DEBUG
		funtions++;
	#endif
}

/**
  * Destructor of the Function.
  */
Function::~Function()
{
	destroy();

	#ifdef _DEBUG
		funtions--;
		if(funtions == 0)
		{
			cout << funtions << " -> Funtions" << endl;
		}
	#endif
}

/**
  * Operator assign(=) of Function.
  */
Function &Function::operator=(const Function &other)
{
	if(this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

/**
  * Method of copy the Function, STL-like C++.
  */
void Function::copy(const Function &other)
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
  * Method destroy Function, STL-like C++.
  */
void Function::destroy()
{
}

/**
  * Returns the name of the Function.
  */
string Function::get_name() const
{
	return f_name;
}

/**
  * Returns the domain of the Function.
  */
const vector<const Sort*> &Function::get_domain() const
{
	return f_domain;
}

/**
  * Returns the image of the Function.
  */
const Sort *Function::get_image() const
{
	return f_image;
}

/**
  * Returns the mode of the operator.
  */
oper_mode Function::get_mode() const
{
	return f_mod;
}

/**
  * Returns the precedence of the operator.
  */
unsigned short Function::get_prec() const
{
	return f_prec;
}

/**
  * Returns the associativity of the operator.
  */
oper_assoc Function::get_oper_assoc() const
{
	return f_assoc;
}
/**
  * Returns the arity of Function.
  */
int Function::get_arity() const
{
	return f_domain.size();
}

/**
  * Sets the name of the Function.
  */
void Function::set_name(string name)
{
	f_name = name;
}

/**
  * Sets the sort image of the Function.
  */
void Function::set_image(const Sort *image)
{
	f_image = image;
}

/**
  * Sets the mode of the operator.
  * @param mode: string
  */
void Function::set_mode(string mode)
{
	if(mode.compare("infix") == 0)
	{
		f_mod = k_infix;
	}
	else
	{
		if(mode.compare("prefix") == 0)
		{
			f_mod = k_prefix;
		}
		else
		{
			if(mode.compare("postfix") == 0)
			{
				f_mod = k_postfix;
			}
			else
			{
				/* Default value. */
				f_mod = k_prefix;
			}
		}
	}
}

/**
  * Sets the precedence of the operator.
  */
void Function::set_prec(unsigned short prec)
{
	f_prec = prec;
}

/**
  * Sets the associativity of the operator.
  */
void Function::set_oper_assoc(string mod)
{
	if(mod.compare("left") == 0)
	{
		f_assoc = k_left;
	}
	else
	{
		if(mod.compare("right") == 0)
		{
			f_assoc = k_right;
		}
		else
		{
			if(mod.compare("non-assoc") == 0)
			{
				f_assoc = k_non_assoc;
			}
			else
			{
				/* Default value. */
				f_assoc = k_left;
			}
		}
	}
}

/**
  * Sets the boolean attribute with the parameter.
  */
void Function::set_is_operator(bool value)
{
	f_is_operator = value;
}
/**
  * Enqueue a sort in the domain of the Function.
  */
void Function::add_domain(const Sort *sort)
{
	f_domain.push_back(sort);
}

/**
  * Generates and returns a string reprensentation of a Function.
  *
  * Result= "function" \<name\> ":" \<domain\> "->" \<image\> ";"
  *
  * where \<domain\> is= sort_1 ["(" \<instance\> ")" IF DEBUG IS ON] "," ... "," sort_n ["(" \<instance\> ")" IF DEBUG IS ON]
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
			/* Default precedence. */
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
			case k_non_assoc: func.append("non-assoc"); break;
		}
		func.append(") ");
	}
	else
	{
		func.append("function\t");
	}
	func.append(f_name);
	func.append(": ");
	for(vector<Sort>::size_type i(0); i < f_domain.size(); i++)
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
		{
			func.append(", ");
		}
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
  * Returns true if the Function is a Operator.
  */
bool Function::is_operator() const
{
	return f_is_operator;
}

/**
  * Compares the Function with other.
  */
bool Function::equals(const Function &other) const
{
	return (key().compare(other.key()) == 0);
}

/**
  * Generates and returns the string key that identifies a Function definitely.
  *
  * Result= \<name\> \<domain\> \<image\>
  *
  * where \<domain\> is = sort_1 ... sort_n
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
	for(vector<Sort>::size_type i(0); i < f_domain.size(); i++)
	{
		key.append(f_domain[i]->get_name());
	}
	return key;
}

} /* end genevalmag */
