/**
 * \file Equation.h
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 05/11/2009
 *  \author    Kilmurray, Gerardo Luis.
 *  \author    Picco, Gonzalo M.
 */

#ifndef EQUATION_H_
#define EQUATION_H_

#include "tree/tree.hh"

#include "Attribute.h"
#include "Symbol.h"

namespace genevalmag {

// node's type.
enum node_type
{
	k_intance,
	k_function,
	k_operator,
	k_int,
	k_float,
	k_char,
	k_string
};

struct instance
{
	Symbol * i_symb;	// Symbol.
	int i_num;			// Index instance.
	Attribute * i_attr;	// Symbol's attribute.
};

struct n_term
{
	void* data;
	node_type type_node;
	string type_syntetized;
};

class Equation {
	private:
		instance l_value;
		tree<n_term> r_value;

	public:
		Equation();
		virtual ~Equation();
		Symbol get_l_value();
		vector <Symbol> get_body();
};

}

#endif /* EQUATION_H_ */
