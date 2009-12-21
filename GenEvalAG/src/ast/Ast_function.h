/**
  *  \file		Ast_function.h
  *  \brief
  *  \date		21/12/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef AST_FUNCTION_H_
#define AST_FUNCTION_H_

#include "Ast_inner_node.h"
#include "../Function.h"

namespace genevalmag
{

class Ast_function: public Ast_inner_node
{
private:
	Function* func;

	/**
	  * Method of copy the Ast_function, STL-like C++.
	  */
	void copy (Ast_function const& other);
	/**
	  * Method destroy Ast_function, STL-like C++.
	  */
	void destroy ();

public:
	Ast_function();
	Ast_function (Ast_function const & other);
	virtual ~Ast_function();

	Ast_function& operator= (Ast_function const & other);

    Function *get_function() const;

    void set_function(Function *func);

    string to_string() const;
};

} // end genevalmag

#endif /* AST_FUNCTION_H_ */
