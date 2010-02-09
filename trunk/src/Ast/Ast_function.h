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
#include "../Attr_grammar/Function.h"

namespace genevalmag
{

class Ast_function: public Ast_inner_node
{
private:
	Function *func;
	unsigned short precedence_level;
	unsigned short syntax_order;

	/**
	  * Method of copy the Ast_function, STL-like C++.
	  */
	void copy(Ast_function const &other);
	/**
	  * Method destroy Ast_function, STL-like C++.
	  */
	void destroy();

public:
	Ast_function();
	Ast_function(Ast_function const &other);
	virtual ~Ast_function();

	Ast_function &operator=(Ast_function const &other);

	Function *get_function() const;
	unsigned short get_precedence_level() const;
	unsigned short get_syntax_order() const;

	void set_function(Function *func);
	void set_precedence_level(unsigned short p_level);
	void set_syntax_order(unsigned short s_order);

	bool is_prefix() const;
	bool is_infix() const;
	bool is_postfix() const;

	bool is_comparable(Ast_function * other) const;
	int compare_precedence(Ast_function * other) const;
	int compare_order(Ast_function * other) const;


	string to_string() const;
};

} // end genevalmag

#endif /* AST_FUNCTION_H_ */
