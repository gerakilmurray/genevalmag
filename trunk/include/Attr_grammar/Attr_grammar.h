/**
  *  \file      Attr_grammar.h
  *  \brief     Class that represent the full attribute grammar parsed.
  *  \date      28/09/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef SEMDOMAIN_H_
#define SEMDOMAIN_H_

#include <map>

#include "Sort.h"
#include "Function.h"
#include "Attribute.h"
#include "Symbol.h"
#include "Rule.h"

using namespace std;

namespace genevalmag
{

class Attr_grammar
{

	private:
		/**
		  *  Saves each element kind of the grammar's attribute.
		  */
		map<string, Sort>            ag_sort;
		map<string, Function>        ag_func;
		map<string, Attribute>       ag_attr;
		map<string, Symbol>          ag_symb_terminals;
		map<string, Symbol>          ag_symb_non_terminals;
		map<unsigned short, Rule>    ag_rule;

		/** Store the count of equations in the gramamar. */
		unsigned short               count_eqs;

		/**
		  * Saves the name of the initial symbol of the grammar's attribute.
		  */
		const Symbol                 *ag_initial_symb;

		/**
		  * Insert the attributes belong the symbol.
		  */
		void load_attributes(Symbol &symb) const;

		/**
		  * Checks that the rule is not already defined in the grammar.
		  */
		const bool defined_rule(const Rule &rule) const;

	public:
		/**
		  * Contructor empty of semantic domain.
		  */
		Attr_grammar();

		/**
		  * Destructor of the semantic domain.
		  */
		virtual ~Attr_grammar();

		/**
		  * Enqueue a sort in the list of the semantic domain.
		  */
		const bool add_sort(const Sort &sort);
		/**
		  * Enqueue a function in the list of the semantic domain.
		  */
		const bool add_function(const Function &func);
		/**
		  * Enqueue a attribute in the list of the semantic domain.
		  */
		const bool add_attribute(const Attribute &attr);
		/**
		  * Enqueue a symbol in the list of the semantic domain.
		  */
		const bool add_symbol(const Symbol &symb);
		/**
		  * Enqueue a rule in the list of the semantic domain.
		  */
		const bool add_rule(Rule &rule);

		/**
		  * Find in the list of sort of the semantic domain and return the sort with that name.
		  */
		const Sort &return_sort(const string name_sort);
		/**
		  * Return the map with all sorts.
		  */
		const map<string, Sort> &get_sorts() const;
		/**
		  * Find in the list of function of the semantic domain and return the function with that name.
		  */
		const Function *get_function(const string name_function) const;
		/**
		  * Return the map with all functions.
		  */
		const map<string, Function> &get_functions() const;
		/**
		  * Find in the list of symbol of the semantic domain and return the symbol with that name.
		  */
		const Symbol &get_symbol(const string name_symbol) const;
		/**
		  *  Return the map with all rules.
		  */
		const map<unsigned short, Rule>  &get_rules() const;
		/**
		  *  Return the rule on paramenter.
		  */
		const Rule  &get_rule(const unsigned short index) const;
		/**
		  *  Return the map with all symbols.
		  */
		const map<string, Symbol> &get_non_terminal_symbols() const;
		/**
		  *  Return the initial rule.
		  */
		const Symbol *get_initial_symb() const;
		/**
		  * Return vector with all rules with the left symbol equal that parameter.
		  */
		const vector<unsigned short> get_rules_with_left_symbol(const Symbol *symb) const;
		/**
		  * Returns the index of an equation in this range of rules with l_value equals to ins.
		  */
		const unsigned short get_index_eq_with_context(const Ast_instance *ins, const vector<unsigned short> &context_rule) const;
		/**
		  *    Returns the equation with this index.
		  */
		const Equation *get_eq(const unsigned short index) const;
		/**
		  * Returns the l_value of the equation with this index.
		  */
		const Ast_instance *get_eq_l_value(const unsigned short index) const;
		/**
		  * Returns the count of equations in the grammar.
		  */
		const unsigned short get_count_eqs() const;

		/**
		  * Generate and return a string reprensentation of a semantic domain.
		  *
		  * Result = "semantic domain"
		  *             \<sorts\>
		  *             \<operators\>
		  *             \<functions\>
		  *
		  *          "attributes"
		  *             \<attributes\>
		  *
		  *         [This section is commented so that it can be parsed again.]
		  *         ***********************************************************
		  *          "symbols"
		  *             \<symbols\>
		  *         ***********************************************************
		  *          "rules"
		  *             \<rules\>
		  *
		  * where \<sorts\>, \<operators\>, \<functions\>, \<attributes\>, \<symbols\> and \<rules\>, are
		  * full representation of each type.
		  */
		const string to_string() const;
};

} /* end genevalmag */

#endif /* SEMDOMAIN_H_ */
