/**
  * \file MultiTree.cpp
  *		\brief EXPLICAR ALGO ACA
  *  \date 07/09/2009
  *  \author Kilmurray, Gerardo Luis.
  *	 \author Picco, Gonzalo M.
  */

#include "MultiTree.h"

namespace gen_eval_mag {

template <class T> void MultiTree<T>::addRoot(T root){
	this.root = root;
	this.count_children = 0;
}

template <class T> void MultiTree<T>::addChild(MultiTree <T> chd){
	this.children[this.count_children] = chd;
	this.count_children++;
}

}
