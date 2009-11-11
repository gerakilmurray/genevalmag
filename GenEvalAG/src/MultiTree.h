/**
 * \file MultiTree.h
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 05/11/2009
 *  \author    Kilmurray, Gerardo Luis.
 *  \author    Picco, Gonzalo M.
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
		T get_root();
		void set_root(T root);
};

}

#endif /* MULTITREE_H_ */
