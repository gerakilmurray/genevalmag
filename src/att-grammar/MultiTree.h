/**
  *  \file MultiTree.h
  *      \brief Define the MultiTree object.
  *  \date 07/09/2009
  *  \author Kilmurray, Gerardo Luis.
  *	 \author Picco, Gonzalo Martín.
  */

#ifndef MULTITREE_H_
#define MULTITREE_H_

namespace gen_eval_mag {

template <class T> class MultiTree{
	private:
		T root;
		MultiTree<T> *child_left;
		MultiTree<T> *child_right;

	public:
		MultiTree();
		~MultiTree();
		MultiTree<T> getChild_left();
		MultiTree<T> getChild_right();
		T getRoot();
		void setChild_left(MultiTree<T> child_left);
		void setChild_right(MultiTree<T> child_right);
		void setRoot(T root);
};

}

#endif /* MULTITREE_H_ */
