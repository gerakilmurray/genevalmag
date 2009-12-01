/**
  *  \file		Symbol.h
  *  \brief		Class of the symbol of the grammar parsed.
  *  \date		04/11/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <vector>
#include <string>

#include "Attribute.h"

namespace genevalmag
{

/**
  * Enumeration of symbol's type.
  */
enum symbol_type
{
	k_terminal,
	k_non_terminal
};

class Symbol
{
	private:
		string				symb_name;
		symbol_type			symb_type;
		vector<Attribute*>	symb_attrs;

		/**
		  * Method of copy the symbol, STL-like C++.
		  */
		void copy (Symbol const& other);
		/**
		  * Method destroy symbol, STL-like C++.
		  */
		void destroy ();

	public:
		/**
		  * Constructor empty of symbol.
		  */
		Symbol ();
		/**
		  * Constructor with name and type of symbol.
		  */
		Symbol (string name, symbol_type type);
		/**
		  * Constructor copy of symbol.
		  */
		Symbol (Symbol const & other);

		/**
		  * Destructor of symbol.
		  */
		virtual ~Symbol ();

		/**
		  * Operator assign (=) of symbol.
		  */
		Symbol& operator= (Symbol const & other);

		/**
		  * Return the name of the symbol.
		  */
		string get_name () const;
		/**
		  * Return the type of the symbol.
		  */
		symbol_type get_type () const;
		/**
		  * Return the list of attributes of the symbol.
		  */
		vector<Attribute*> get_attrs () const;

	    /**
	      * Set the name of the symbol.
	      */
		void set_name (string name);
		/**
		  * Set the type of the symbol.
		  */
		void set_type (symbol_type type);

		/**
		  * Enqueue a attribute in the list of the symbol.
		  */
		void add_attr (Attribute* attr);

		/**
		  * Return true if the symbol's type is Non Terminal.
		  */
	    bool is_non_terminal () const;

	    /**
	      * Generate and return a string reprensentation of a symbol.
	      *
	      * Result= "symbol" <name> <type> ";"
	      *
	      * where if <type> is Non Terminal, then list the attributes of the symbol.
	      *
	      * <list>= "Attributes:" <attr_1> "," ... "," <attr_n>
	      */
	    string to_string () const;

	    /**
	      * Compares the symbol with other.
	      */
		bool equals (Symbol const & other) const;

		/**
	      * Generate and return the string key that identifies a symbol definitely.
	      *
	      * Result= <name>
	      */
	    string key () const;

};

} // end genevalmag

#endif /* SYMBOL_H_ */
