/**
 * \file MultiTree.h
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 05/11/2009
 *  \author    Kilmurray, Gerardo Luis.
 *  \author    Picco, Gonzalo M.
 */

#ifndef MULTITREE_H_
#define MULTITREE_H_

#include "tree/tree.hh"

#include "Attribute.h"
#include "Symbol.h"

namespace genevalmag {

struct n_term
{
	Symbol * t_symb;	// Symbol.
	int t_ins;			// Index instance.
	Attribute * t_attr;	// Symbol's attribute.
};

class MultiTree{
	private:
		tree<n_term> elem;

	public:
		MultiTree();
		~MultiTree();
		n_term get_root();
		void set_root(n_term new_root);
		void addchild(n_term termino);
};

}

#endif /* MULTITREE_H_ */
