/**
  *  \file		SemDomain.h
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

#define IS_OPERATOR true

class SemDomain
{
private:
	map<string, Sort>		sd_sort;
	map<string, Function>	sd_func;
	map<string, Attribute> 	sd_attr;
	map<string, Symbol>		sd_symb;
	map<string, Rule>		sd_rule;

	/**
	  * Insert the attributes belong the symbol.
	  */
	void load_attributes(Symbol &symb);

public:
	/**
	  * Contructor empty of semantic domain.
	  */
	SemDomain();

	/**
	  * Destructor of the semantic domain.
	  */
	virtual ~SemDomain();

	/**
	  * Enqueue a sort in the list of the semantic domain.
	  */
	bool add_sort(Sort &sort);
	/**
	  * Enqueue a operator in the list of the semantic domain.
	  */
//	bool add_operator(Function &oper);
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
	Sort &return_sort(string name_sort);
	/**
	  * Find in the list of function of the semantic domain and return the function with that name.
	  */
	Function *get_function(string name_function);
	/**
	  * Find in the list of symbol of the semantic domain and return the symbol with that name.
	  */
	Symbol &get_symbol(string name_symbol);

	/**
	  * Generate and return a string reprensentation of a semantic domain.
	  *
	  * Result= "semantic domain"
	  * 			<sorts>
	  * 			<operators>
	  * 			<functions>
	  *
	  * 		"attributes"
	  * 			<attributes>
	  *
	  *		[This section is commented so that it can be parsed again.]
	  *		***********************************************************
	  * 		"symbols"
	  * 			<symbols>
	  *		***********************************************************
	  * 		"rules"
	  * 			<rules>
	  *
	  * where <sorts>, <operators>, <functions>, <attributes>, <symbols> and <rules>, are
	  * full representation of each type.
	  */
	string to_string();
};

} // end genevalmag

#endif /* SEMDOMAIN_H_ */
