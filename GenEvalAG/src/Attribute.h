/**
 * \file Attribute.h
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 23/10/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

enum TipeAttr
{
	kInherit,
	kSyntetize
};

class Attribute {
private:
	string a_name;
	Sort a_type;
	TipeAttr mod_type;
	string member_symbol;

public:
	Attribute();
	virtual ~Attribute();
};

#endif /* ATTRIBUTE_H_ */
