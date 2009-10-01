/**
 * \file SemDomain.h
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 28/09/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#ifndef SEMDOMAIN_H_
#define SEMDOMAIN_H_

#include "Operator.h"
#include "Sort.h"
#include <vector>

using namespace std;
namespace genevalmag {

class SemDomain {
private:
	vector<Sort> v_sort;
	vector<Operator> v_op;

public:
	SemDomain();
	virtual ~SemDomain();

	void add_sort(Sort s);
	bool add_op(Operator op);

	Operator * get_last_op();
	Sort get_sort (string name);
	bool search_sort (Sort sort);
	bool search_op (Operator op);

	string to_string_sorts();
	string to_string_ops();
	string to_string();
};

}

#endif /* SEMDOMAIN_H_ */
