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
	vector<Operator> v_oper;
	vector<Attribute> v_attr;
	vector<Symbol> v_symb;
	//vector<rule> v_rule

public:
	SemDomain();
	virtual ~SemDomain();

	bool add_sort (Sort s);
	bool add_op   (Operator op);
	bool add_att  (Attribute att);
	bool add_symb (Symbol symb);

	bool search_sort (Sort sort);
	bool search_op   (Operator op);
	bool search_att  (Attribute attr);
	bool search_symb (Symbol symb);

	Sort get_sort (string name);
	void load_atts(Symbol s);

	string to_string();
};

}

#endif /* SEMDOMAIN_H_ */
