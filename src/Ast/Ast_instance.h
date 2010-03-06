/**
  *  \file		Ast_instance.h
  *  \brief		Instance element of an Attribute Syntax Tree (AST).
  *  \date		21/12/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef AST_INSTANCE_H_
#define AST_INSTANCE_H_

#include "Ast_leaf.h"

#include "../Attr_grammar/Symbol.h"
#include "../Attr_grammar/Attribute.h"

namespace genevalmag
{

class Ast_instance: public Ast_leaf
{
private:
	const Symbol      	*i_symb;
	unsigned short		i_num;
	const Attribute   	*i_attr;

	/**
	  * Method of copy the Ast_instance, STL-like C++.
	  */
	void copy(Ast_instance const &other);
	/**
	  * Method destroy Ast_instance, STL-like C++.
	  */
	void destroy();

public:
	Ast_instance();
	Ast_instance(Ast_instance const &other);
	virtual ~Ast_instance();

	Ast_instance &operator =(const Ast_instance &other);

	const Attribute *get_attr() const;

	unsigned short get_num() const;

	const Symbol *get_symb() const;

	void set_attr(const Attribute *attr);

	void set_num(unsigned short num);

	void set_symb(const Symbol *symb);

	string to_string() const;

	bool equals_with_index(const Ast_instance * other) const;

	string key() const;
};

} // end genevalmag

#endif /* AST_INSTANCE_H_ */
