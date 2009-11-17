/**
 * \file MultiTree.cpp
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 05/11/2009
 *  \author    Kilmurray, Gerardo Luis.
 *  \author    Picco, Gonzalo M.
 */

#include "MultiTree.h"

namespace genevalmag {

MultiTree::MultiTree()
{

}

MultiTree::~MultiTree()
{

}

n_term MultiTree::get_root()
{
	return elem.head->data;
}

void MultiTree::set_root(n_term new_root)
{
	elem.set_head(new_root);
}

}
