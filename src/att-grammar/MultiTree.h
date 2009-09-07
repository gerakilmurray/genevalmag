/**
  * \file MultiTree.h
  *		\brief EXPLICAR ALGO ACA
  *  \date 07/09/2009
  *  \author Kilmurray, Gerardo Luis.
  *	 \author Picco, Gonzalo M.
  */

#ifndef MULTITREE_H_
#define MULTITREE_H_

namespace gen_eval_mag {

template <class T>
class MultiTree{
private:
	T root;
	MultiTree <T> children[];
	int count_children;
public:
	MultiTree();
	~MultiTree();
	void addRoot (T root);
	void addChild (MultiTree <T> chd);

};

}

#endif /* MULTITREE_H_ */
