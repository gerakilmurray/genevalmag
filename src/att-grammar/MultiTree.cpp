/**
  *  \file MultiTree.cpp
  *      \brief Implement the methods MultiTree.h
  *  \date 07/09/2009
  *  \author Kilmurray, Gerardo Luis.
  *	 \author Picco, Gonzalo Martín.
  */

#include "MultiTree.h"

namespace gen_eval_mag {

template <class T>MultiTree<T> MultiTree<T>::getChild_left()
{
	return this->child_left;
}

template <class T> MultiTree<T> MultiTree<T>::getChild_right()
{
	return this->child_right;
}

template <class T> T MultiTree<T>::getRoot()
{
	return this->root;
}

template <class T> void MultiTree<T>::setChild_left(MultiTree<T> child_left)
{
	this->child_left = child_left;
}

template <class T> void MultiTree<T>::setChild_right(MultiTree<T> child_right)
{
	this->child_right = child_right;
}

template <class T> void MultiTree<T>::setRoot(T root)
{
	this->root = root;
}

}
