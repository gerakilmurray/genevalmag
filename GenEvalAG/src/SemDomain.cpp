/**
  *  \file		SemDomain.cpp
  *  \brief		Implementation of the methods the SemDomain.h
  *  \date		28/09/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <boost/tokenizer.hpp>
#include <iostream>

#include "SemDomain.h"

using namespace std;

namespace genevalmag
{

/**
  * Contructor empty of semantic domain.
  */
SemDomain::SemDomain()
{
	initial_symbol.clear();
}

/**
  * Destructor of the semantic domain.
  */
SemDomain::~SemDomain()
{
}

/**
  * Operation template that insert an object type T in the parameter map.
  *
  * Return true if insert succesfully.
  * In other case, return false.
  */
template <class T> bool add(T elem, map<string,T > &map_elem)
{
	pair<string,T > new_p(elem.key(), elem);
	pair<typename map<string,T >::iterator, bool > result = map_elem.insert(new_p);
	return result.second;
}

/**
  * Operation template that print each element type T of the parameter map.
  *
  * Return the string representation of all elements of the map.
  */
template <class T> string to_string_map(map<string,T > &map_elem)
{
	string elem;
	for(typename map<string,T >::iterator it = map_elem.begin(); it != map_elem.end(); it++)
	{
		elem.append("\t");
		elem.append(it->second.to_string());
		elem.append("\n");
	}
	return elem;
}

/**
  * Enqueue a sort in the list of the semantic domain.
  */
bool SemDomain::add_sort(Sort &sort)
{
	return add<Sort>(sort, sd_sort);
}

/**
  * Enqueue a function in the list of the semantic domain.
  */
bool SemDomain::add_function(Function &func)
{
	return add<Function>(func, sd_func);
}

/**
  * Enqueue a attribute in the list of the semantic domain.
  */
bool SemDomain::add_attribute(Attribute &attr)
{
	return add<Attribute>(attr, sd_attr);
}

/**
  * Enqueue a symbol in the list of the semantic domain.
  */
bool SemDomain::add_symbol(Symbol &symb)
{
	bool not_repeat = add <Symbol>(symb, sd_symb);
	if(not_repeat &&symb.is_non_terminal())
	{
		map<string, Symbol>::iterator it = sd_symb.find(symb.key());
		load_attributes(it->second);
	}
	return not_repeat;
}

/**
  * Enqueue a rule in the list of the semantic domain.
  */
bool SemDomain::add_rule(Rule &rule)
{
	if (initial_symbol.empty())
		// Set initial symbol of grammar.
		initial_symbol = rule.key();

	return add <Rule>(rule, sd_rule);
}

/**
  * Find in the list of sort of the semantic domain and return the sort with that name.
  */
Sort &SemDomain::return_sort(string name_sort)
{
	Sort sort_new(name_sort);
	// becouse is a type basic. if not the sort belong map. the map not have repeat.
	sort_new.set_type_basic(true);
	add_sort(sort_new);
	map<string,Sort>::iterator it = sd_sort.find(name_sort);
	return it->second;
}
/**
  * Find in the list of function of the semantic domain and return the function with that name.
  */
Function *SemDomain::get_function(string key_function)
{
	map<string,Function>::iterator it = sd_func.find(key_function);
	if (it == sd_func.end())
		return NULL;
	return &(it->second);
}
/**
  * Find in the list of operator of the semantic domain and return the operator with that name.
  */
Symbol &SemDomain::get_symbol(string name_symbol)
{
	map<string,Symbol>::iterator it = sd_symb.find(name_symbol);
	return it->second;
}

/**
  *  Return the map with all rules.
  */
map<string, Rule> SemDomain::get_rules() const
{
	return sd_rule;
}

/**
  *  Return the map with all Symbols.
  */
map<string, Symbol> SemDomain::get_symbols() const
{
	return sd_symb;
}

string SemDomain::get_initial_symbol() const
{
    return initial_symbol;
}

void  SemDomain::set_initial_symbol(string init_symbol)
{
    initial_symbol = init_symbol;
}


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
  * 		"symbols"
  * 			<symbols>
  *
  * 		"rules"
  * 			<rules>
  *
  * where <sorts>, <operators>, <functions>, <attributes>, <symbols> and <rules>, are
  * full representation of each type.
  */
string SemDomain::to_string()
{
	#ifdef _DEBUG
//		map<string,Sort>::iterator		it1 = sd_sort.find("pepe");
//		it1->second.set_name("Pupi_Zanetti");
//
//		map<string,Attribute>::iterator	it2 = sd_attr.find("valorintall");
//		it2->second.set_name("valores");
//
//		map<string,Symbol>::iterator	it3 = sd_symb.find("id");
//		it3->second.set_name("ident");
	#endif

	string semdomain("\nsemantic domain\n");
	semdomain.append(to_string_map <Sort	 >(sd_sort));
	semdomain.append("\n");
	semdomain.append(to_string_map <Function >(sd_func));
	semdomain.append("\nattributes\n");
	semdomain.append(to_string_map <Attribute>(sd_attr));
	semdomain.append("\n/***********************************************************");
	semdomain.append("\nsymbols\n");
	semdomain.append(to_string_map <Symbol   >(sd_symb));
	semdomain.append("***********************************************************/\n");
	semdomain.append("\nrules\n");
	semdomain.append(to_string_map <Rule	 >(sd_rule));
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
void SemDomain::load_attributes(Symbol &symb)
{
	for(map<string,Attribute>::iterator it = sd_attr.begin(); it != sd_attr.end(); it++)
	{
		if(belong(symb, it->second.get_member_symbol()))
		{
			symb.add_attr(&(it->second));
		}
	}
}

} // end genevalmag
