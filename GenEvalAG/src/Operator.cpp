/**
 * \file Operator.cpp
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 28/09/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#include "Operator.h"

namespace genevalmag {

Operator::Operator(string name, vector <Sort> * v, Sort * img, int id)
{
	this->o_name = name;
	this->o_domain = *v;
	this->o_image = *img;
	this->o_id = id;
}

Operator::Operator()
{
	// TODO Auto-generated constructor stub
}

Operator::~Operator()
{
	// TODO Auto-generated destructor stub
}

}
