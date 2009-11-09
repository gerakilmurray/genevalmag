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

	void load_attrs(Symbol& symb);

public:
	SemDomain();
	virtual ~SemDomain();

	bool add_sort (const Sort& s);
	bool add_op   (const Operator& op);
	bool add_att  (const Attribute& att);
	bool add_symb (Symbol& symb);

	bool search_sort (const Sort& sort) const;
	bool search_op   (const Operator& op) const;
	bool search_att  (const Attribute& attr) const;
	bool search_symb (const Symbol& symb) const;

	Sort return_sort (string name);

	string to_string() const;

};

}

#endif /* SEMDOMAIN_H_ */
