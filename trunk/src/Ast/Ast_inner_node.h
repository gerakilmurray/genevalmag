/**
  *  \file		Ast_iner_node.h
  *  \brief
  *  \date		21/12/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef AST_INNER_NODE_H_
#define AST_INNER_NODE_H_

#include <vector>

#include "Ast_node.h"

namespace genevalmag
{

class Ast_inner_node: public Ast_node
{
protected:
	vector <Ast_node*> childs;

public:
	virtual ~Ast_inner_node()
	{
		for (unsigned int i=0; i < childs.size() ;i++)
		{
			delete(childs[i]);
		}
	};

	vector<Ast_node*> get_childs() const
	{
		return childs;
	}

	Ast_node* get_child(int index) const
	{
		return childs[index];
	}

	void set_childs(vector<Ast_node*> new_childs)
	{
		childs = new_childs;
	}

	void replace_child(int index,Ast_node * new_child)
	{
		childs[index] = new_child;
		new_child->set_parent(this);
	}

	void add_child(Ast_node *new_child)
	{
		childs.insert(childs.begin(),new_child);
		new_child->set_parent(this);
	}

	virtual string to_string() const = 0;

};

} // end genevalmag

#endif /* AST_INNER_NODE_H_ */
