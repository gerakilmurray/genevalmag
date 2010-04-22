/**
  *  \file      Rule.h
  *  \brief     Class of the rule of the grammar parsed.
  *  \date      05/11/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
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
		/**
		  * \var r_id
		  * \brief Rule's identifier.
		  */
        unsigned short                    r_id;
		/**
		  * \var r_left_symbol
		  * \brief Rule's left symbol.
		  */
        const Symbol                      *r_left_symbol;
		/**
		  * \var r_right_side
		  * \brief Rule's vector of right symbols.
		  */
        vector <const Symbol*>            r_right_side;
		/**
		  * \var r_eqs
		  * \brief Rule's map of equations.
		  */
        map <unsigned short, Equation>    r_eqs;
		/**
		  * \var r_offset
		  * \brief Rule's offset.
		  */
        unsigned short                    r_offset;

        /**
          * Method of copy the rule, STL-like C++.
          * @param other
          */
        void copy(const Rule &other);
        /**
          * Method destroy rule, STL-like C++.
          */
        void destroy();

        /**
          * Checks that the equation is not already defined in the rule.
          * @param eq
          * @return
          */
        const bool defined_equation(const Equation &eq) const;

    public:
        /**
          * Constructor empty of rule.
          */
        Rule();
        /**
          * Constructor copy of rule.
          * @param other
          * @return
          */
        Rule(const Rule &other);

        /**
          * Destructor of rule.
          */
        virtual ~Rule();

        /**
          * Operator assign(=) of rule.
          * @param other
          * @return
          */
        Rule &operator=(const Rule &other);

        /**
          * Returns the left symbol of the rule.
          * @return
          */
        const Symbol *get_left_symbol() const;
        /**
          * Returns the right side of the rule.
          * @return
          */
        const vector<const Symbol*> &get_right_side() const;
        /**
          * Returns the equations of the rule.
          * @return
          */
        const map <unsigned short,Equation> &get_eqs() const;
        /**
          * Returns the number of equations of the rule.
          * @return
          */
        const size_t get_number_eqs() const;
        /**
          * Returns the i-equation of the rule.
          * @param index
          * @return
          */
        const Equation *get_eq(const unsigned short index) const;
        /**
          * Returns the offset of all equation of the rule.
          * @return
          */
        const unsigned short get_offset() const;
        /**
          * Returns the count of ocurrences of these symbol in the rule.
          * @param symb
          * @return
          */
        const int count_non_terminal(const Symbol *symb) const;
        /**
          * Checks that symbol is a non-terminal into the rule.
          * @param non_term
          * @return
          */
        const bool belongs_non_terminal(const Symbol &non_term) const;
        /**
          * Returns the non-terminals symbols the right side of the rule.
          * @return
          */
        const vector<const Symbol*> get_non_terminals_right_side() const;

        /**
          * Sets the identificator of the rule.
          * @param id
          */
        void set_id(const unsigned short id);
        /**
          * Sets the left symbol of the rule.
          * @param left_symb
          */
        void set_left_symbol(const Symbol *left_symb);

        /**
          * Enqueues a symbol in the right side of the rule.
          * @param rigth_symb
          */
        void add_right_symbol(const Symbol *rigth_symb);
        /**
          * Enqueues a equation in the list of the rule.
          * @param eq
          * @return
          */
        const bool add_eq(Equation &eq);

        /**
          * Generates and returns a string reprensentation of a rule.\n
          *\n
          * Result = left_symbol "::=" right_side\n
          *                                     "compute"\n
          *                                             eq_1\n
          *                                             ...\n
          *                                             eq_n\n
          *                                     "end;"\n
          *\n
          * where right_ride is = symbol_1 " " ... " " symbol_n\n
          *
          * @return
          */
        const string to_string() const;

        /**
          * Generates and returns a string reprensentation of a rule.\n
          *\n
          * Result= left_symbol "::=" right_side ";"\n
          *\n
          * where right_ride is = symbol_1 " " ... " " symbol_n\n
          *\n
          * @return
          */
        const string to_string_not_eqs() const;

        /**
          * Compares the rule with other.
          * @param other
          * @return
          */
        const bool equals(const Rule &other) const;

        /**
          * Returns the number key that identifies a rule definitely.\n
          *\n
          * Result = \<id_rule\>\n
          *
          * @return
          */
        const unsigned short key() const;
};

} /* end genevalmag */

#endif /* RULE_H_ */
