/**
  * \file Attribute.h
  *		\brief Define a attribute of a symbol of a attribute grammar.
  *  \date 31/08/2009
  *  \author Kilmurray, Gerardo Luis.
  *	 \author Picco, Gonzalo M.
 */

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

namespace gen_eval_mag {

/**
  * Define type of the attribute
  * inherit: his value depend of the father's values.
  * sintetize: his value depend of the children's values.
  */
enum TipeAttr
{
	kInherit,
	kSintetize
};

class Attribute{
private:
	TipeAttr tipo;
public:
	Attribute();
	virtual ~Attribute();
};

}

#endif /* ATTRIBUTE_H_ */
