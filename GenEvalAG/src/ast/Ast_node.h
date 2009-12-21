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

using namespace std;

namespace genevalmag
{

/**
  * Node's type.
  */
enum node_type
{
	k_intance,
	k_function,
	k_literal
};

class Ast_node
{
protected:
	Ast_node* 	parent;
	node_type	type_node;
	string		type_synthetized;

public:
	Ast_node* get_parent() const
    {
        return parent;
    }

	node_type get_node_type() const
	{
		return type_node;
	}

	string get_type_synthetized() const
    {
        return type_synthetized;
    }

    void set_parent(Ast_node* new_parent)
    {
        parent = new_parent;
    }

    void set_node_type(node_type new_type_node)
    {
    	type_node = new_type_node;
    }


    void set_type_synthetized(string new_type_synthetized)
    {
        type_synthetized = new_type_synthetized;
    }

    virtual string to_string () const
    {
    	return "AST Node\n";
    }
};

} // end genevalmag

#endif /* AST_NODE_H_ */
