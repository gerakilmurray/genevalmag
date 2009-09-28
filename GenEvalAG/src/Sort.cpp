/**
 * \file Sort.cpp
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 28/09/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#include "Sort.h"

namespace genevalmag {

Sort::Sort(string name) {
	this->s_id = 0;
	this->s_name = name;
}
Sort::Sort() {}

Sort::~Sort() {
	// TODO Auto-generated destructor stub
}
int Sort::getId() const
{
    return this->s_id;
}

string Sort::getName() const
{
    return this->s_name;
}

void Sort::setId(int s_id)
{
    this->s_id = s_id;
}

void Sort::setName(string s_name)
{
    this->s_name = s_name;
}

}
