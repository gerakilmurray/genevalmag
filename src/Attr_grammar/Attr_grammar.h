/**
  *  \file		Attr_grammar.h
  *  \brief		Class that represent the full attribute grammar parsed.
  *  \date		28/09/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
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

const bool IS_OPERATOR (true);

class Attr_grammar
{
private:
	/*
	 *  Saves each element kind of the grammar's attribute.
	 */
	map<string, Sort>			ag_sort;
	map<string, Function>		ag_func;
	map<string, Attribute> 		ag_attr;
	map<string, Symbol>			ag_symb_terminals;
	map<string, Symbol>			ag_symb_non_terminals;
	map<unsigned short, Rule>	ag_rule;

	/*
	 * Saves the name of the initial symbol of the grammar's attribute.
	 */
	const Symbol					*ag_initial_symb;

	/**
	  * Insert the attributes belong the symbol.
	  */
	void load_attributes(Symbol &symb);

	bool defined_rule(const Rule &rule) const;

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
	bool add_sort(Sort &sort);
	/**
	  * Enqueue a function in the list of the semantic domain.
	  */
	bool add_function(Function &func);
	/**
	  * Enqueue a attribute in the list of the semantic domain.
	  */
	bool add_attribute(Attribute &attr);
	/**
	  * Enqueue a symbol in the list of the semantic domain.
	  */
	bool add_symbol(Symbol &symb);
	/**
	  * Enqueue a rule in the list of the semantic domain.
	  */
	bool add_rule(Rule &rule);

	/**
	  * Find in the list of sort of the semantic domain and return the sort with that name.
	  */
	const Sort &return_sort(string name_sort);
	/**
	  * Find in the list of function of the semantic domain and return the function with that name.
	  */
	const Function *get_function(string name_function);
	/**
	  * Find in the list of symbol of the semantic domain and return the symbol with that name.
	  */
	const Symbol &get_symbol(string name_symbol);
	/**
	  *  Return the map with all rules.
	  */
	const map<unsigned short, Rule>  &get_rules()const;
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
	vector<const Rule*> get_rules_with_left_symbol(const Symbol *symb) const;

	/**
	  *  Set the initial rule.
	  */
	void set_initial_symb(Symbol *init_symbol);

	/**
	  * Generate and return a string reprensentation of a semantic domain.
	  *
	  * Result= "semantic domain"
	  * 			\<sorts\>
	  * 			\<operators\>
	  * 			\<functions\>
	  *
	  * 		"attributes"
	  * 			\<attributes\>
	  *
	  *		[This section is commented so that it can be parsed again.]
	  *		***********************************************************
	  * 		"symbols"
	  * 			\<symbols\>
	  *		***********************************************************
	  * 		"rules"
	  * 			\<rules\>
	  *
	  * where \<sorts\>, \<operators\>, \<functions\>, \<attributes\>, \<symbols\> and \<rules\>, are
	  * full representation of each type.
	  */
	string to_string();
};

} // end genevalmag

#endif /* SEMDOMAIN_H_ */
