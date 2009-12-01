/**
  *  \file		Operator.cpp
  *  \brief		Implementation of the methods the Operator.h
  *  \date		28/09/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>
#include <sstream>
#include <climits>

#include "Operator.h"

using namespace std;

namespace genevalmag
{

#ifdef _DEBUG
	// Numbers of operators current in the system.
	static int opers = 0;
#endif

/**
  * Contructor empty of operator.
  */
Operator::Operator ()
{
	o_mod	= k_prefix;
	o_prec	= UINT_MAX;
	o_assoc	= k_left;

	#ifdef _DEBUG
		opers++;
	#endif
}

/**
  * Contructor copy of operator.
  */
Operator::Operator (Operator const & other)
{
	copy (other);

	#ifdef _DEBUG
		opers++;
	#endif
}

/**
  * Destructor of the operator.
  */
Operator::~Operator ()
{
	destroy ();

	#ifdef _DEBUG
		opers--;
		cout << "Operators: " << opers << endl;
	#endif
}

/**
  * Operator assign (=) of operator.
  */
Operator& Operator::operator= (Operator const & other)
{
	if (this != &other)
	{
		destroy ();
		copy (other);
	}
	return *this;
}

/**
  * Method of copy the operator, STL-like C++.
  */
void Operator::copy (const Operator& other)
{
	o_name		= other.get_name ();
	o_mod		= other.get_mode ();
	o_prec		= other.get_prec ();
	o_assoc		= other.get_oper_assoc ();
	o_domain	= other.get_domain ();
	o_image		= other.get_image ();
}

/**
  * Method destroy operator, STL-like C++.
  */
void Operator::destroy ()
{
}

/**
  * Return the name of the operator.
  */
string Operator::get_name () const
{
    return o_name;
}

/**
  * Return the name of the operator.
  */
oper_mode Operator::get_mode () const
{
	return o_mod;
}

/**
  * Return the precedence of the operator.
  */
int Operator::get_prec () const
{
    return o_prec;
}

/**
  * Return the associativity of the operator.
  */
oper_assoc Operator::get_oper_assoc () const
{
	return o_assoc;
}

/**
  * Return the domain of the operator.
  */
vector<Sort*> Operator::get_domain () const
{
    return o_domain;
}

/**
  * Return the image of the operator.
  */
Sort* Operator::get_image () const
{
    return o_image;
}

/**
  * Set the name of the operator.
  */
void Operator::set_name (string name)
{
    o_name = name;
}

/**
  * Set the mode of the operator.
  * @param mode: string
  */
void Operator::set_mode (string mode)
{
	if (mode.compare ("infix") == 0)
		o_mod = k_infix;
	else if (mode.compare ("prefix") == 0)
		o_mod = k_prefix;
	else if (mode.compare ("postfix") == 0)
		o_mod = k_postfix;
	else
		// Default value.
		o_mod = k_prefix;
}

/**
  * Set the precedence of the operator.
  */
void Operator::set_prec (int prec)
{
    o_prec = prec;
}

/**
  * Set the associativity of the operator.
  */
void Operator::set_oper_assoc (string mod)
{
	if (mod.compare ("left") == 0)
		o_assoc = k_left;
	else if (mod.compare ("right") == 0)
		o_assoc = k_right;
	else if (mod.compare ("non-assoc") == 0)
		o_assoc = k_nonassoc;
	else
		// Default value.
		o_assoc = k_left;
}

/**
  * Set the full sort domain of the operator.
  */
void Operator::set_domain (vector<Sort*> domain)
{
    o_domain = domain;
}

/**
  * Set the sort image of the operator.
  */
void Operator::set_image (Sort* image)
{
    o_image = image;
}

/**
  * Enqueue a sort in the domain of the operator.
  */
void Operator::add_domain (Sort* sort)
{
	o_domain.push_back (sort);
}

/**
  * Generate and return a string reprensentation of a operator.
  *
  * Result= "op" <oper_mode> " (" <precedence> "," <associativity> ")" <name> ":" <domain> "->" <image> ";"
  *
  * where <domain> is= <sort_1> [" (" <instance> ")" IF DEBUG IS ON] "," ... "," <sort_n> [" (" <instance> ")" IF DEBUG IS ON]
  */
string Operator::to_string () const
{
    string op;
    op.append ("op ");
    switch (o_mod)
	{
		case k_infix:   op.append ("infix");   break;
		case k_prefix:  op.append ("prefix");  break;
		case k_postfix: op.append ("postfix"); break;
    }
	op.append ("\t(");
	if (o_prec == UINT_MAX)
	{
		// Default precedence.
		op.append ("_");
	}
	else
	{
		std::stringstream prec;
		prec << o_prec;
		op.append (prec.str ());
	}
	op.append (", ");
    switch (o_assoc)
	{
		case k_left:	 op.append ("left");      break;
		case k_right:	 op.append ("right");     break;
		case k_nonassoc: op.append ("non-assoc"); break;
    }
	op.append (") ");
	op.append (o_name);
	op.append (": ");
	for (vector<Sort>::size_type i = 0; i < o_domain.size (); i++)
	{
		op.append (o_domain[i]->get_name ());

		#ifdef _DEBUG
			op.append (" (");
			std::stringstream ins;
			ins << o_domain[i]->get_ins ();
			op.append (ins.str ());
			op.append (")");
		#endif

		if (i+1 < o_domain.size ())
			op.append (", ");
	}
	op.append (" -> ");
	op.append (o_image->get_name ());

	#ifdef _DEBUG
		op.append (" (");
		std::stringstream ins;
		ins << o_image->get_ins ();
		op.append (ins.str ());
		op.append (")");
	#endif

	op.append (";");
	return op;
}

/**
  * Compares the operator with other.
  */
bool Operator::equals (Operator const & other) const
{
	return	key ().compare (other.key ()) == 0;
}

/**
  * Generate and return the string key that identifies a operator definitely.
  *
  * Result= <mode> <name> <domain> <image>
  *
  * where <domain> is= <sort_1> ... <sort_n>
  */
string Operator::key () const
{
	string key;
    switch (o_mod)
	{
		case k_infix:   key.append ("infix");   break;
		case k_prefix:  key.append ("prefix");  break;
		case k_postfix: key.append ("postfix"); break;
	}
	key.append (o_name);
	for (vector<Sort>::size_type i = 0; i < o_domain.size (); i++)
	{
		key.append (o_domain[i]->get_name ());
	}
	key.append (o_image->get_name ());
	return key;
}

//void Operator::purge ()
//{
//	o_domain.clear ();
//	o_image = NULL;
//	o_prec = 1000;
//	o_mod = k_prefix;
//}

} // end genevalmag
