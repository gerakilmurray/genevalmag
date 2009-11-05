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

enum TipeAttr
{
	kInherit,
	kSyntetize
};

class Attribute {
private:
	string a_name;
	string a_type;
	TipeAttr a_mod_type;
	string a_member_symbol;

public:
	Attribute();
	Attribute(string name, string type, TipeAttr mod, string merberships);
	virtual ~Attribute();

	string getName() const;
	string getType() const;
	TipeAttr getMod_type() const;
	string getMember_symbol() const;

	void setName(string a_name);
	void setType(string a_type);
	void setMod_type(TipeAttr a_mod_type);
	void setMember_symbol(string a_member_symbol);

	string to_string ()const;
	bool equals(Attribute attr) const;
};
}
#endif /* ATTRIBUTE_H_ */
