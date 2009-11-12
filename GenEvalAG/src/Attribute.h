/**
 * \file Attribute.h
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 23/10/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include "Sort.h"

namespace genevalmag{

enum type_attr
{
	k_inherit,
	k_syntetize
};

class Attribute {
private:
	string a_name;
	string a_type;
	type_attr a_mod_type;
	string a_member_symbol;

	//Methods for STL C++
	void copy(Attribute const& other);
	void destroy();

public:
	Attribute();
	Attribute(string name, string type, type_attr mod, string merberships);
	Attribute(Attribute const & other);
	virtual ~Attribute();

	Attribute& operator= (Attribute const & other);

	string get_name() const;
	string get_type() const;
	type_attr get_mod_type() const;
	string get_member_symbol() const;

	void set_name(string a_name);
	void set_type(string a_type);
	void set_mod_type(type_attr a_mod_type);
	void set_member_symbol(string a_member_symbol);

	string to_string ()const;
	bool equals(Attribute attr) const;
	bool is_syntetize() const;
};
}
#endif /* ATTRIBUTE_H_ */
