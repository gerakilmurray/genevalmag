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
	void add_op(Operator op);

	Operator * get_last_op();
	Sort  get_sort (string name);
	bool search_sort (Sort sort);


	void print_sorts();
	void print_ops();
	void print_sem_dom();
};

}

#endif /* SEMDOMAIN_H_ */
