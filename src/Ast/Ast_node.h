/**
  *  \file		Ast_node.h
  *  \brief
  *  \date		21/12/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef AST_NODE_H_
#define AST_NODE_H_

#include <string>

#include "../Attr_grammar/Sort.h"

using namespace std;

namespace genevalmag
{

class Ast_node
{
protected:
	Ast_node    *parent;
	string		type_synthetized;
	int			conflict;

public:
	virtual ~Ast_node(){};

	Ast_node *get_parent() const
	{
		return parent;
	}

	string get_type_synthetized() const
	{
		return type_synthetized;
	}

	void set_parent(Ast_node *new_parent)
	{
		parent = new_parent;
	}

	void active_conflict(int prec_conflict)
	{
		conflict = prec_conflict;
	}

	void desactive_conflict()
	{
		conflict = -1;
	}

	int get_conflict() const
	{
		return conflict;
	}

	void delete_parent()
	{
		parent = NULL;
	}

	void set_type_synthetized(string new_type_synthetized)
	{
		type_synthetized = new_type_synthetized;
	}

	virtual string to_string() const = 0;

	virtual bool equals( const Ast_node * node) const
	{
		return to_string().compare(node->to_string()) == 0;
	}
};

} // end genevalmag

#endif /* AST_NODE_H_ */
