/**
  *  \file		Attr_grammar.cpp
  *  \brief		Implementation of the methods the Attr_grammar.h
  *  \date		28/09/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <boost/tokenizer.hpp>
#include <iostream>

#include "Attr_grammar.h"

using namespace std;

namespace genevalmag
{

/**
  * Contructor empty of attribute grammar.
  */
Attr_grammar::Attr_grammar()
{
	/* Remove garbage. */
	ag_initial_symb = NULL;
}

/**
  * Destructor of the attribute grammar.
  */
Attr_grammar::~Attr_grammar()
{
}

/**
  * Operation template that insert an object type T in the parameter map.
  *
  * Return true if insert succesfully.
  * In other case, return false.
  */
template <class K, class T> bool add(T elem, map< K ,T > &map_elem)
{
	pair< K, T > new_p(elem.key(), elem);
	pair<typename map< K, T  >::iterator, bool > result = map_elem.insert(new_p);
	return result.second;
}

/**
  * Operation template that print each element type T of the parameter map.
  *
  * Return the string representation of all elements of the map.
  */
template <class K, class T> string to_string_map(map< K ,T > &map_elem)
{
	string elem;
	for(typename map< K, T >::iterator it = map_elem.begin(); it != map_elem.end(); it++)
	{
		elem.append("\t");
		elem.append(it->second.to_string());
		elem.append("\n");
	}
	return elem;
}

/**
  * Enqueue a sort in the list of the attribute grammar.
  */
bool Attr_grammar::add_sort(Sort &sort)
{
	return add<string, Sort>(sort, ag_sort);
}

/**
  * Enqueue a function in the list of the attribute grammar.
  */
bool Attr_grammar::add_function(Function &func)
{
	return add<string, Function>(func, ag_func);
}

/**
  * Enqueue a attribute in the list of the attribute grammar.
  */
bool Attr_grammar::add_attribute(Attribute &attr)
{
	return add<string, Attribute>(attr, ag_attr);
}

/**
  * Enqueue a symbol in the list of the attribute grammar.
  */
bool Attr_grammar::add_symbol(Symbol &symb)
{
	map<string, Symbol>	*map_symb;
	if (symb.is_non_terminal())
	{
		map_symb = &ag_symb_non_terminals;
	}
	else
	{
		map_symb = &ag_symb_terminals;
	}

	bool not_repeat = add <string, Symbol>(symb, *map_symb);
	if(not_repeat && symb.is_non_terminal())
	{
		map<string, Symbol>::iterator it = map_symb->find(symb.key());
		load_attributes(it->second);
	}
	return not_repeat;
}

bool Attr_grammar::defined_rule(const Rule &rule) const
{
	for(map<unsigned short, Rule>::const_iterator it = ag_rule.begin(); it != ag_rule.end(); it++)
	{
		if (it->second.equals(rule))
		{
			return true;
		}
	}
	return false;
}

/**
  * Enqueue a rule in the list of the attribute grammar.
  */
bool Attr_grammar::add_rule(Rule &rule)
{
	static unsigned short cant_rules = 1;

	if (defined_rule(rule))
	{
		/* The rule is already defined then it isn't inserted. */
		return false;
	}

	rule.set_id(cant_rules++);

	bool result = add <unsigned short, Rule>(rule, ag_rule);
	if ( result && ag_initial_symb == NULL)
	{
		/* Set initial symbol of grammar. */
		map<unsigned short, Rule>::iterator	init_symb = ag_rule.find(rule.key());
		ag_initial_symb = init_symb->second.get_left_symbol();
	}
	return result;
}

/**
  * Find in the list of sort of the attribute grammar and return the sort with that name.
  */
const Sort &Attr_grammar::return_sort(string name_sort)
{
	Sort sort_new(name_sort);
	/* Becouse is a type basic. if not the sort belong map. the map not have repeat. */
	sort_new.set_type_basic(true);
	add_sort(sort_new);
	map<string,Sort>::iterator it = ag_sort.find(name_sort);
	return it->second;
}
/**
  * Find in the list of function of the attribute grammar and return the function with that name.
  */
const Function *Attr_grammar::get_function(string key_function)
{
	map<string,Function>::iterator it = ag_func.find(key_function);
	if (it == ag_func.end())
		return NULL;
	return &(it->second);
}
/**
  * Find in the list of operator of the attribute grammar and return the operator with that name.
  */
const Symbol &Attr_grammar::get_symbol(string name_symbol)
{
	map<string,Symbol>::iterator it = ag_symb_non_terminals.find(name_symbol);
	if (it == ag_symb_non_terminals.end())
		it = ag_symb_terminals.find(name_symbol);
	return it->second;
}

/**
  *  Return the map with all rules.
  */
const map<unsigned short, Rule> &Attr_grammar::get_rules() const
{
	return ag_rule;
}
/**
  *  Return the rule on paramenter.
  */
const Rule  &Attr_grammar::get_rule(unsigned short index)const
{
	return ag_rule.find(index)->second;
}
/**
  *  Return the map with all symbols.
  */
const map<string, Symbol> &Attr_grammar::get_non_terminal_symbols() const
{
	return ag_symb_non_terminals;
}
/**
  *  Return the initial rule.
  */
const Symbol *Attr_grammar::get_initial_symb() const
{
    return ag_initial_symb;
}

/**
  * Return vector with all rules with the left symbol equal that parameter.
  */
vector<unsigned short> Attr_grammar::get_rules_with_left_symbol(const Symbol *symb) const
{
	vector<unsigned short> result;

	for(map<unsigned short, Rule>::const_iterator it = ag_rule.begin(); it != ag_rule.end(); it++)
	{
		if(it->second.get_left_symbol()->equals(*symb))
		{
			result.push_back(it->second.key());
		}
	}
	return result;
}

/**
  *  Set the initial rule.
  */
void  Attr_grammar::set_initial_symb(Symbol *init_symb)
{
	ag_initial_symb = init_symb;
}

/**
  * Generate and return a string reprensentation of a attribute grammar.
  * where sorts, operators, functions, attributes, symbols and rules, are
  * full representation of each type.
  */
string Attr_grammar::to_string()
{
	string semdomain("\nsemantic domain\n");
	semdomain.append(to_string_map<string, Sort>(ag_sort));
	semdomain.append("\n");
	semdomain.append(to_string_map<string, Function>(ag_func));
	semdomain.append("\nattributes\n");
	semdomain.append(to_string_map<string, Attribute>(ag_attr));
	semdomain.append("\n/***********************************************************");
	semdomain.append("\nsymbols\n");
	semdomain.append(to_string_map<string, Symbol>(ag_symb_non_terminals));
	semdomain.append(to_string_map<string, Symbol>(ag_symb_terminals));
	semdomain.append("\n***********************************************************/\n");
	semdomain.append("/*  >>>>>>>>>> Initial Symbol of Grammar is ");
	semdomain.append(ag_initial_symb->get_name());
	semdomain.append(" <<<<<<<<<<  */\n");
	semdomain.append("/**********************************************************/\n");
	semdomain.append("\nrules\n");
	semdomain.append(to_string_map<unsigned short, Rule>(ag_rule));
	semdomain.append("\n");
	return semdomain;
}

/**
  * Interpret the expression of sets and returns true
  * if the symbol belongs to that set.
  */
bool belong(Symbol symb, string expr_attrs)
{
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep("{},-");
	tokenizer tokens(expr_attrs, sep);
	tokenizer::iterator tok_iter = tokens.begin();

	if((*tok_iter).compare("all") == 0)
	{
		for(tok_iter++; tok_iter != tokens.end(); tok_iter++)
		{
			if(symb.get_name().compare(*tok_iter) == 0)
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		for(; tok_iter != tokens.end(); tok_iter++)
		{
			if(symb.get_name().compare(*tok_iter) == 0)
			{
				return true;
			}
		}
		return false;
	}
}

/**
  * Insert the attributes belong the symbol.
  */
void Attr_grammar::load_attributes(Symbol &symb)
{
	for(map<string,Attribute>::iterator it = ag_attr.begin(); it != ag_attr.end(); it++)
	{
		if(belong(symb, it->second.get_member_symbol()))
		{
			symb.add_attr(&(it->second));
		}
	}
}

} /* end genevalmag */
