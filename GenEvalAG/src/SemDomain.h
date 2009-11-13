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
	vector<Sort>		v_sort; // map<string,Sort>
	vector<Operator>	v_oper;
	vector<Attribute> 	v_attr;
	vector<Symbol>		v_symb;
	vector<Rule>		v_rule;
	//map<int,Rule> 	m_rule;

	void load_attrs(Symbol& symb);

public:
	SemDomain();
	virtual ~SemDomain();

	bool add_sort (Sort& s);
	bool add_op   (Operator& op);
	bool add_att  (Attribute& att);
	bool add_symb (Symbol& symb);
	bool add_rule (Rule& rule);

	bool search_sort (Sort& sort) const;
	bool search_op   (Operator& op) const;
	bool search_att  (Attribute& attr) const;
	bool search_symb (Symbol& symb) const;
	bool search_rule (Rule& rule) const;

	Sort& return_sort (string name);

	string to_string();

	Symbol* get_symbol(string name_symbol);

};

}

#endif /* SEMDOMAIN_H_ */
