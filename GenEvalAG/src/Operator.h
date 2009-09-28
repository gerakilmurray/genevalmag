/**
 * \file Operator.h
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 28/09/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#ifndef OPERATOR_H_
#define OPERATOR_H_

#include <string>
#include "Sort.h"
#include <vector>

namespace genevalmag {

class Operator {
private:
	string o_name;
	vector<Sort> o_domain;
	Sort o_image;
	int o_id;
public:
	Operator();
	Operator(string name, vector <Sort> * v, Sort * img, int id);
	virtual ~Operator();
};

}

#endif /* OPERADOR_H_ */
