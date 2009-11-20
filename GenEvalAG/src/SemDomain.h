/**
 * \file SemDomain.h
 * 	\brief Represents a semantic block a AST.
 *  \date 28/09/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#ifndef SEMDOMAIN_H_
#define SEMDOMAIN_H_

#include <map>

#include "Sort.h"
#include "Operator.h"
#include "Attribute.h"
#include "Symbol.h"
#include "Rule.h"

using namespace std;
namespace genevalmag {

class SemDomain {
private:
	map<string, Sort>		v_sort;
	map<string, Operator>	v_oper;
	map<string, Attribute> 	v_attr;
	map<string, Symbol>		v_symb;
	map<string, Rule>		v_rule;

	void load_attrs(Symbol& symb);

public:
	SemDomain();
	virtual ~SemDomain();

	bool add_sort (Sort& s);
	bool add_op   (Operator& op);
	bool add_att  (Attribute& att);
	bool add_symb (Symbol& symb);
	bool add_rule (Rule& rule);

	Sort& return_sort (string name_sort);
	Symbol& get_symbol(string name_symbol);
	Operator& get_operation(string name_oper);

	string to_string();
};

}

#endif /* SEMDOMAIN_H_ */
