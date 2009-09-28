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
	vector<Sort>  v_sort;
	vector<Operator> v_op;

public:
	SemDomain();
	virtual ~SemDomain();

	void add_sort(Sort s);
	void add_op(Operator op);
    void print_sort();
};

}

#endif /* SEMDOMAIN_H_ */
