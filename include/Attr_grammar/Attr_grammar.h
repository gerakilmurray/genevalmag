/**
  *  \file      Attr_grammar.h
  *  \brief     Class that represent the full attribute grammar.
  *  \date      28/09/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef ATTR_GRAMMAR_H_
#define ATTR_GRAMMAR_H_

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
		  *  \brief Saves each element kind of the grammar's attribute.
		  *  \var ag_sort
		  *  \var ag_func
		  *  \var ag_attr
		  *  \var ag_symb_terminals
		  *  \var ag_symb_non_terminals
		  *  \var ag_rule
		  */
		map<string, Sort>            ag_sort;
		map<string, Function>        ag_func;
		map<string, Attribute>       ag_attr;
		map<string, Symbol>          ag_symb_terminals;
		map<string, Symbol>          ag_symb_non_terminals;
		map<unsigned short, Rule>    ag_rule;

		/**
		  * \brief Store the count of equations in the gramamar.
		  * \var count_eqs
		  */
		unsigned short               count_eqs;

		/**
		  * \brief Saves the name of the initial symbol of the grammar's attribute.
		  * \var ag_initial_symb
		  */
		const Symbol                 *ag_initial_symb;

		/**
		  * Insert the attributes belong the symbol.
 		  * @param symb
		  */
		void load_attributes(Symbol &symb) const;

		/**
		  * Checks that the rule is not already defined in the grammar.
		  * @param rule
		  * @return
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
		  * Enqueues a sort in the list of the semantic domain.
		  * @param sort
		  * @return
		  */
		const bool add_sort(const Sort &sort);
		/**
		  * Enqueues a function in the list of the semantic domain.
		  * @param func
          * @return
          */
		const bool add_function(const Function &func);
		/**
		  * Enqueues a attribute in the list of the semantic domain.
		  * @param attr
		  * @return
		  */
		const bool add_attribute(const Attribute &attr);
		/**
		  * Enqueues a symbol in the list of the semantic domain.
		  * @param symb
		  * @return
		  */
		const bool add_symbol(const Symbol &symb);
		/**
		  * Enqueues a rule in the list of the semantic domain.
		  * @param rule
		  * @return
		  */
		const bool add_rule(Rule &rule);

		/**
		  * Finds in the list of sort of the semantic domain and returns the sort with that name.
		  * @param name_sort
		  * @return
		  */
		const Sort &return_sort(const string name_sort);
		/**
		  * Returns the map with all sorts.
		  * @return
		  */
		const map<string, Sort> &get_sorts() const;
		/**
		  * Finds in the list of function of the semantic domain and returns the function with that name.
		  * @param key_function
		  * @return
		  */
		const Function *get_function(const string key_function) const;
		/**
		  * Returns the map with all functions.
		  * @return
		  */
		const map<string, Function> &get_functions() const;
		/**
		  * Finds in the list of symbol of the semantic domain and returns the symbol with that name.
		  * @param name_symbol
		  * @return
		  */
		const Symbol &get_symbol(const string name_symbol) const;
		/**
		  *  Returns the map with all rules.
		  * @return
		  */
		const map<unsigned short, Rule>  &get_rules() const;
		/**
		  *  Returns the rule on paramenter.
		  * @param index
		  * @return
		  */
		const Rule  &get_rule(const unsigned short index) const;
		/**
		  *  Returns the map with all symbols.
		  * @return
		  */
		const map<string, Symbol> &get_non_terminal_symbols() const;
		/**
		  *  Returns the initial rule.
		  * @return
		  */
		const Symbol *get_initial_symb() const;
		/**
		  * Returns vector with all rules with the left symbol equal that parameter.
		  * @param symb
		  * @return
		  */
		const vector<unsigned short> get_rules_with_left_symbol(const Symbol *symb) const;
		/**
		  * Returns the index of an equation in this range of rules with l_value equals to ins.
		  * @param ins
		  * @param context_rule
		  * @return
		 */
		const unsigned short get_index_eq_with_context(const Expr_instance *ins, const vector<unsigned short> &context_rule) const;
		/**
		  * Returns the equation with this index.
		  * @param index
		  * @return
		  */
		const Equation *get_eq(const unsigned short index) const;
		/**
		  * Returns the l_value of the equation with this index.
		  * @param index
		  * @return
		  */
		const Expr_instance *get_eq_l_value(const unsigned short index) const;
		/**
		  * Returns the count of equations in the grammar.
		  * @return
		  */
		const unsigned short get_count_eqs() const;

		/**
		  * Generates and returns a string reprensentation of a semantic domain.\n
		  *\n
		  * Result = "semantic domain"\n
		  *             \<sorts\>\n
		  *             \<operators\>\n
		  *             \<functions\>\n
		  *\n
		  *          "attributes"\n
		  *             \<attributes\>\n
		  *\n
		  *         [This section is commented so that it can be parsed again.]\n
		  *         ***********************************************************\n
		  *          "symbols"\n
		  *             \<symbols\>\n
		  *         ***********************************************************\n
		  *          "rules"\n
		  *             \<rules\>\n
		  *\n
		  * where \<sorts\>, \<operators\>, \<functions\>, \<attributes\>, \<symbols\> and \<rules\>,\n
		  * are a full representation of each type.\n
		  *
		  * @return
		  */
		const string to_string() const;
};

} /* end genevalmag */

#endif /* ATTR_GRAMMAR_H_ */
