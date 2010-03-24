/**
 * \file Node.h
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 17/03/2010
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>

using namespace std;

namespace util_ag
{

struct Node
{
	Node *parent;
	vector<Node*> childs;
	unsigned short rule_id;
	unsigned short index_plan_v_seq; //index of vector de visit sequence.
	unsigned short num_v_seq;   // donde quede.
};

}/* end namespace */

#endif /* NODE_H_ */


