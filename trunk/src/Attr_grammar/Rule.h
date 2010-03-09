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
		unsigned short					r_id;
		const Symbol					*r_left_symbol;
		vector <const Symbol*>			r_right_side;
		map <unsigned short,Equation>	r_eqs;

		/**
		  * Method of copy the rule, STL-like C++.
		  */
		void copy(const Rule &other);
		/**
		  * Method destroy rule, STL-like C++.
		  */
		void destroy();

		bool defined_equation(const Equation &eq) const;

	public:
		/**
		  * Constructor empty of rule.
		  */
		Rule();
		/**
		  * Constructor copy of rule.
		  */
		Rule(const Rule &other);

		/**
		  * Destructor of rule.
		  */
		virtual ~Rule();

		/**
		  * Operator assign(=) of rule.
		  */
		Rule &operator=(const Rule &other);

		/**
		  * Returns the left symbol of the rule.
		  */
		const Symbol *get_left_symbol() const;
		/**
		  * Returns the right side of the rule.
		  */
		const vector<const Symbol*> &get_right_side()const;
		/**
		  * Returns the equations of the rule.
		  */
		const map <unsigned short,Equation> &get_eqs() const;
		/**
		  * Returns the i-equation of the rule.
		  */
		const Equation *get_eq(unsigned short index) const;

		/**
		  * Sets the identificator of the rule.
		  */
	    void set_id(unsigned short id);
		/**
		  * Sets the left symbol of the rule.
		  */
		void set_left_symbol(const Symbol *left_symb);

		/**
		  * Enqueue a symbol in the right side of the rule.
		  */
		void add_right_symbol(const Symbol *rigth_symb);
		/**
		  * Enqueue a equation in the list of the rule.
		  */
		bool add_eq(Equation &eq);

		/**
		  * Generate and return a string reprensentation of a rule.
		  *
		  * Result= left_symbol "::=" right_side
		  * 									"compute"
		  *												eq_1
		  * 											...
		  * 											eq_n
		  * 									"end;"
		  *
		  * where right_ride is= symbol_1 " " ... " " symbol_n
		  */
		string to_string() const;

		/**
		  * Generate and return a string reprensentation of a rule.
		  *
		  * Result= left_symbol "::=" right_side ";"
		  *
		  * where right_ride is= symbol_1 " " ... " " symbol_n
		  */
		string to_string_not_eqs() const;

		/**
		  * Compares the rule with other.
		  */
		bool equals(const Rule &other) const;

		/**
		  * Generate and return the string key that identifies a rule definitely.
		  *
		  * Result= left_symbol right_side
		  *
		  * where right_ride is= symbol_1 ... symbol_n
		  */
		unsigned short key() const;

		int count_non_terminal(const Symbol *symb) const;

		bool belongs_non_terminal(const Symbol &non_term) const;
		/**
		  * Return the non-terminals symbols the right side of the rule.
		  */
		vector<const Symbol*> get_non_terminals_right_side() const;

		unsigned short get_index_eq(const Ast_instance *ins) const;

		const Ast_instance *get_eq_l_value(unsigned short index)const;
};

} /* end genevalmag */

#endif /* RULE_H_ */
