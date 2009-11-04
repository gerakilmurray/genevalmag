/**
 * \file SemDomain.h
 * 	\brief Represents a semantic block a AST.
 *  \date 28/09/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#ifndef SEMDOMAIN_H_
#define SEMDOMAIN_H_

#include <vector>

#include "Sort.h"
#include "Operator.h"
#include "Attribute.h"
#include "Symbol.h"

using namespace std;
namespace genevalmag {

class SemDomain {
private:
	vector<Sort> v_sort;
	vector<Operator> v_op;
	vector<Attribute> v_attr;
	vector<Symbol> v_sym;
	//vector<rule> v_rul

public:
	SemDomain();
	virtual ~SemDomain();

	bool add_sort(Sort s);
	bool add_op(Operator op);
	bool add_att(Attribute att);

	Operator * get_last_op();
	Sort get_sort (string name);
	bool search_sort (Sort sort);
	bool search_op (Operator op);
	bool search_att (Attribute attr);

	string to_string_sorts();
	string to_string_ops();
	string to_string_atts();
	string to_string();

	void add_atts(Symbol s);
};

}

#endif /* SEMDOMAIN_H_ */
