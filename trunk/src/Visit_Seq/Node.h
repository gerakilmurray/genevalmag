/**
 * \file Node.h
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 17/03/2010
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#ifndef NODE_H_
#define NODE_H_

using namespace std;
//using namespace genevalmag;

namespace visit_seq
{

class Node {
private:
	unsigned short visit_number; // donde quede;
	unsigned short n_seq;  //index of vector de visit sequence.

public:
	Node();
	virtual ~Node();
};

#endif /* NODE_H_ */

}/* end namespace */
