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
	virtual ~Ast_inner_node(){};

	vector<Ast_node*> get_childs() const
	{
		return childs;
	}

	void set_childs(vector<Ast_node*> new_childs)
	{
		childs = new_childs;
	}

	void add_child(Ast_node* new_child)
	{
		childs.push_back(new_child);
	}

	virtual string to_string() const = 0;
};

} // end genevalmag

#endif /* AST_INNER_NODE_H_ */
