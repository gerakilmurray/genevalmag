/*
 * MultiTree.h
 *
 *  Created on: 05/11/2009
 *      Author: gera
 */

#ifndef MULTITREE_H_
#define MULTITREE_H_

#include <vector>

namespace genevalmag {

template <class T> class MultiTree{
	private:
		T root;
//		typedef MultiTree <T> child;
//		vector<child> children;

	public:
		MultiTree();
		~MultiTree();
		T getRoot();
		void setRoot(T root);
};

}

#endif /* MULTITREE_H_ */
