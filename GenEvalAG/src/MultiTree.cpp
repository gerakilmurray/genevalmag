/*
 * MultiTree.cpp
 *
 *  Created on: 05/11/2009
 *      Author: gera
 */

#include "MultiTree.h"

namespace genevalmag {

template <class T> MultiTree<T>::MultiTree()
{
	// TODO Auto-generated constructor stub
}

template <class T> MultiTree<T>::~MultiTree()
{
	// TODO Auto-generated destructor stub
}

template <class T> T MultiTree<T>::getRoot()
{
	return this->root;
}

template <class T> void MultiTree<T>::setRoot(T root)
{
	this->root = root;
}

}
