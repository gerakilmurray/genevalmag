/**
  *  \file		Rule.h
  *  \brief		EXPLICAR QUE ES ESTO
  *  \date		05/11/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef RULE_H_
#define RULE_H_

#include <map>

#include "Symbol.h"
#include "Equation.h"

namespace genevalmag
{

class Rule
{
	private:
		Symbol*				r_left_symbol;
		vector <Symbol*>	r_right_side;
		map <int,Equation*>	r_eqs;

		/**
		  * Method of copy the rule, STL-like C++.
		  */
		void copy (Rule const & other);
		/**
		  * Method destroy rule, STL-like C++.
		  */
		void destroy ();

	    /**
	      * Generate and return a string reprensentation of a rule.
	      *
	      * Result= <left_symbol> "::=" <right_side> ";"
	      *
	      * where <right_ride> is= <symbol_1> " " ... " " <symbol_n>
	      */
		string to_string_not_eqs () const;

	public:
		/**
		  * Constructor empty of rule.
		  */
		Rule ();
		/**
		  * Constructor copy of rule.
		  */
		Rule (Rule const & other);

		/**
		  * Destructor of rule.
		  */
		virtual ~Rule ();

		/**
		  * Operator assign (=) of rule.
		  */
		Rule& operator= (Rule const & other);

		/**
		  * Return the left symbol of the rule.
		  */
		Symbol* get_left_symbol () const;
		/**
		  * Return the right side of the rule.
		  */
		vector<Symbol*> get_right_side ()const;
		/**
		  * Return the equations of the rule.
		  */
		map <int,Equation*> get_eqs () const;
		/**
		  * Return the i-equation of the rule.
		  */
		Equation* get_eq (int index);

	    /**
	      * Set the left symbol of the rule.
	      */
		void set_left_symbol (Symbol* left_symb);

		/**
		  * Enqueue a symbol in the right side of the rule.
		  */
		void add_right_symbol (Symbol* rigth_symb);
		/**
		  * Enqueue a equation in the list of the rule.
		  */
		bool add_eq (Equation* eq);

	    /**
	      * Generate and return a string reprensentation of a rule.
	      *
		  * Result= <left_symbol> "::=" <right_side>
		  * 									"compute"
		  *												<eq_1>
		  * 											...
		  * 											<eq_n>
		  * 									"end;"
	      *
	      * where <right_ride> is= <symbol_1> " " ... " " <symbol_n>
	      */
		string to_string () const;

	    /**
	      * Compares the rule with other.
	      */
		bool equals (Rule const & other) const;

		/**
	      * Generate and return the string key that identifies a rule definitely.
	      *
	      * Result= <left_symbol> <right_side>
	      *
	      * where <right_ride> is= <symbol_1> ... <symbol_n>
	      */
		string key () const;
};

} // end genevalmag

#endif /* RULE_H_ */
