/**
  *  \file		Attribute.h
  *  \brief		Class of the attribute of the grammar parsed.
  *  \date		23/10/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include "Sort.h"

namespace genevalmag
{

/**
  * Enumeration of the attribute's type: Inherit or Synthetize.
  */
enum type_attr
{
	k_inherit,
	k_synthetize
};

class Attribute
{
private:
	string		a_name;
	Sort*		a_sort_type;
	type_attr	a_mod_type;
	string		a_member_symbol;

	/**
	  * Method of copy the attribute, STL-like C++.
	  */
	void copy (Attribute const& other);
	/**
	  * Method destroy attribute, STL-like C++.
	  */
	void destroy ();

public:
	/**
	  * Constructor empty of attribute.
	  */
	Attribute ();
	/**
	  * Constructor copy of attribute.
	  */
	Attribute (Attribute const & other);

	/**
	  * Destructor of attribute.
	  */
	virtual ~Attribute ();

	/**
	  * Operator assign (=) of attribute.
	  */
	Attribute& operator= (Attribute const & other);

	/**
	  * Return the name of the attribute.
	  */
	string get_name () const;
	/**
	  * Return the sort type of the attribute.
	  */
	Sort* get_sort_type () const;
	/**
	  * Return the modifiers of the attribute.
	  */
	type_attr get_mod_type () const;
	/**
	  * Return the membership list of the attribute.
	  */
	string get_member_symbol () const;

	/**
	  * Set the name of the attribute.
	  */
	void set_name (string name);
	/**
	  * Set the sort type of the attribute.
	  */
	void set_sort_type (Sort* sort_type);
	/**
	  * Set the modifiers of the attribute.
	  */
	void set_mod_type (type_attr mod_type);
	/**
	  * Set the membership list of the attribute.
	  */
	void set_member_symbol (string member_symbol);

	/**
	  * Return true if the modifiers of the attribute is synthetize.
	  */
	bool is_synthetize () const;

	/**
	  * Generate and return a string reprensentation of a attribute.
	  *
	  * Result= <name> ":" <modifiers> "<" <sort_type> [" (" <instance> ")" IF DEBUG IS ON] "> of " <membership_list>
	  */
	string to_string ()const;

	/**
	  * Compares the attribute with other.
	  */
	bool equals (Attribute const & other) const;

	/**
	  * Generate and return the string key that identifies a attribute definitely.
	  *
	  * Result= <name><modifiers><sort_type><membership_list>
	  */
	string key () const;
};

} // end genevalmag

#endif /* ATTRIBUTE_H_ */
