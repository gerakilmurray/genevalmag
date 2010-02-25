/**
  *  \file		Ast_literal.h
  *  \brief
  *  \date		21/12/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef AST_LITERAL_H_
#define AST_LITERAL_H_

#include "Ast_leaf.h"

namespace genevalmag
{

/**
  * Type of basics literals.
  */
enum literal_type
{
	k_int,
	k_float,
	k_char,
	k_string
};

class Ast_literal: public Ast_leaf
{
private:
	/**
	  *	This represent a literal.
	  */
	string			value;
	literal_type	type;

	/**
	  * Method of copy the Ast_literal, STL-like C++.
	  */
	void copy(Ast_literal const &other);
	/**
	  * Method destroy Ast_literal, STL-like C++.
	  */
	void destroy();

public:
	Ast_literal();
	Ast_literal(Ast_literal const &other);
	virtual ~Ast_literal();

	Ast_literal &operator=(Ast_literal const &other);

	literal_type get_type() const;

	string get_value() const;

	void set_type(literal_type new_type);

	void set_value(string new_value);

	string to_string() const;

	string value_s() const;

	bool equals(const Ast_leaf * other) const;
};

} // end genevalmag

#endif /* AST_LITERAL_H_ */
