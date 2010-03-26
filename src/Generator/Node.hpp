/**
  *  \file		Node.h
  *  \brief
  *  \date		17/03/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef NODE_H_
#define NODE_H_

#include <vector>

using namespace std;

namespace util_ag
{

struct Node
{
	struct Node *parent;
	vector<struct Node*> childs;
	unsigned short rule_id;
	unsigned short index_plan_v_seq; //index of vector de visit sequence.
	unsigned short num_v_seq;   // donde quede.

	virtual string to_string() const = 0;
};

}/* end namespace */

#endif /* NODE_H_ */


