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
		void copy(const Ast_instance &other);
		/**
		  * Method destroy Ast_instance, STL-like C++.
		  */
		void destroy();

	public:
		/**
		  * Constructor empty of Ast_instance.
		  */
		Ast_instance();
		/**
		  * Constructor copy of Ast_instance.
		  */
		Ast_instance(const Ast_instance &other);

		/**
		  * Destructor of Ast_instance.
		  */
		virtual ~Ast_instance();

		/**
		  * Operator assign(=) of Ast_instance.
		  */
		Ast_instance &operator=(const Ast_instance &other);

		/**
		  * Returns the attribute pointer of the Ast_instance.
		  */
		const Attribute *get_attr() const;

		/**
		  * Returns the number of the Ast_instance.
		  */
		unsigned short get_num() const;

		/**
		  * Returns the symbol pointer of the Ast_instance.
		  */
		const Symbol *get_symb() const;

		/**
		  * Sets the attribute pointer of the Ast_instance.
		  */
		void set_attr(const Attribute *attr);

		/**
		  * Sets the number of the Ast_instance.
		  */
		void set_num(unsigned short num);

		/**
		  * Sets the symbol pointer of the Ast_instance.
		  */
		void set_symb(const Symbol *symb);

		/**
		  * Generate and return a string reprensentation of a Ast_instance.
		  *
		  * Result= \<symbol\>"["\<number\>"]."\<attribute\>
		  *
		  * Ex: E[0].valor
		  */
		string to_string() const;

		/**
		  * Compares the Ast_instance with other.
		  * Respects Symbol, attribute and number.
		  */
		bool equals_with_index(const Ast_instance *other) const;

		/**
		  * Generate and return the string key that identifies an Ast_instance definitely.
		  *
		  * Result= \<symbol\>\<number\>\<attribute\>
		  *
		  * Ex: E0valor
		  */
		string key() const;
};

} /* end genevalmag */

#endif /* AST_INSTANCE_H_ */
