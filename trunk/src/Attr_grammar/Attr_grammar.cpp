/**
  *  \file      Attr_grammar.cpp
  *  \brief     Implementation of the methods the Attr_grammar.h
  *  \date      28/09/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <boost/tokenizer.hpp>
#include <iostream>

#include "../../include/Attr_grammar/Attr_grammar.h"

using namespace std;

namespace genevalmag
{

/**
  * Contructor empty of attribute grammar.
  */
Attr_grammar::Attr_grammar()
{
    /** Initialice values. */
    ag_initial_symb = NULL;
    count_eqs       = 0;
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
  * Returns true if insert succesfully.
  * In other case, return false.
  */
template <class K, class T> const bool add(const T &elem, map< K ,T > &map_elem)
{
    pair< K, T > new_p(elem.key(), elem);
    pair<typename map< K, T  >::const_iterator, bool > result(map_elem.insert(new_p));
    return result.second;
}

/**
  * Operation template that print each element type T of the parameter map.
  *
  * Returns the string representation of all elements of the map.
  */
template <class K, class T> const string to_string_map(const map< K ,T > &map_elem)
{
    string elem;
    for(typename map< K, T >::const_iterator it(map_elem.begin()); it != map_elem.end(); it++)
    {
        elem.append("    ");
        elem.append(it->second.to_string());
        elem.append("\n");
    }
    return elem;
}

/**
  * Enqueues a sort in the list of the attribute grammar.
  */
const bool Attr_grammar::add_sort(const Sort &sort)
{
    return add<string, Sort>(sort, ag_sort);
}

/**
  * Enqueues a function in the list of the attribute grammar.
  */
const bool Attr_grammar::add_function(const Function &func)
{
    return add<string, Function>(func, ag_func);
}

/**
  * Enqueues a attribute in the list of the attribute grammar.
  */
const bool Attr_grammar::add_attribute(const Attribute &attr)
{
    return add<string, Attribute>(attr, ag_attr);
}

/**
  * Interprets the expression of sets and returns true
  * if the symbol belongs to that set.
  */
const bool belong(const Symbol &symb, const string &expr_attrs)
{
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep("{},-");
    tokenizer tokens(expr_attrs, sep);
    tokenizer::iterator tok_iter(tokens.begin());

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
  * Inserts the attributes belong the symbol.
  */
void Attr_grammar::load_attributes(Symbol &symb) const
{
    for(map<string,Attribute>::const_iterator it(ag_attr.begin()); it != ag_attr.end(); it++)
    {
        if(belong(symb, it->second.get_member_symbol()))
        {
            symb.add_attr(&(it->second));
        }
    }
}

/**
  * Enqueues a symbol in the list of the attribute grammar.
  */
const bool Attr_grammar::add_symbol(const Symbol &symb)
{
    map<string, Symbol> *map_symb;
    static unsigned short id_symbol(1);
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
        map<string, Symbol>::iterator it(map_symb->find(symb.key()));
        load_attributes(it->second);
        it->second.set_id(id_symbol++);
    }

    return not_repeat;
}

/**
  * Checks that the rule is not already defined in the grammar.
  */
const bool Attr_grammar::defined_rule(const Rule &rule) const
{
    for(map<unsigned short, Rule>::const_iterator it(ag_rule.begin()); it != ag_rule.end(); it++)
    {
        if (it->second.equals(rule))
        {
            return true;
        }
    }
    return false;
}

/**
  * Enqueues a rule in the list of the attribute grammar.
  */
const bool Attr_grammar::add_rule(Rule &rule)
{
    static unsigned short id_rules(1);

    if (defined_rule(rule))
    {
        /* The rule is already defined then it isn't inserted. */
        return false;
    }
    rule.set_id(id_rules++);

    if (ag_initial_symb != NULL && rule.belongs_non_terminal(*ag_initial_symb))
    /* Check if the rule respet the extended grammar. */
    {
    	cerr << "ERROR: The grammar isn't extended grammar." << endl;
    	exit(-1);
    }
    bool result(add <unsigned short, Rule>(rule, ag_rule));
    if (result)
    {
        if(ag_initial_symb == NULL)
        {
            /* Set initial symbol of grammar. */
//            map<unsigned short, Rule>::const_iterator init_rule(ag_rule.find(rule.key()));
//            ag_initial_symb = init_rule->second.get_left_symbol();
        	ag_initial_symb = rule.get_left_symbol();
        }
        if(rule.get_eqs().size() > 0)
        {
			map<unsigned short,Rule>::const_iterator last_rule(ag_rule.end());
			last_rule--;
			map<unsigned short,Equation>::const_iterator last_eq(last_rule->second.get_eqs().end());
			last_eq--;
			count_eqs = last_eq->second.get_id();
        }
    }
    return result;
}

/**
  * Finds in the list of sort of the attribute grammar and returns the sort with that name.
  */
const Sort &Attr_grammar::return_sort(const string name_sort)
{
    Sort sort_new(name_sort);
    /* It must be a basic type. Since it became an explicit add_sort above. */
    sort_new.set_type_basic(true);
    add_sort(sort_new);
    map<string,Sort>::const_iterator it(ag_sort.find(name_sort));
    return it->second;
}

/**
  * Returns the map with all sorts.
  */
const map<string, Sort> &Attr_grammar::get_sorts() const
{
    return ag_sort;
}

/**
  * Finds in the list of function of the attribute grammar and returns the function with that name.
  */
const Function *Attr_grammar::get_function(const string key_function) const
{
    map<string,Function>::const_iterator it(ag_func.find(key_function));
    if (it == ag_func.end())
    {
        return NULL;
    }
    return &(it->second);
}

/**
  * Returns the map with all functions.
  */
const map<string, Function> &Attr_grammar::get_functions() const
{
    return ag_func;
}

/**
  * Finds in the list of operator of the attribute grammar and returns the operator with that name.
  */
const Symbol &Attr_grammar::get_symbol(const string name_symbol) const
{
    map<string,Symbol>::const_iterator it(ag_symb_non_terminals.find(name_symbol));
    if (it == ag_symb_non_terminals.end())
    {
        it = ag_symb_terminals.find(name_symbol);
    }
    return it->second;
}

/**
  *  Returns the map with all rules.
  */
const map<unsigned short, Rule> &Attr_grammar::get_rules() const
{
    return ag_rule;
}

/**
  *  Returns the rule on paramenter.
  */
const Rule &Attr_grammar::get_rule(const unsigned short index) const
{
    return ag_rule.find(index)->second;
}

/**
  *  Returns the map with all symbols.
  */
const map<string, Symbol> &Attr_grammar::get_non_terminal_symbols() const
{
    return ag_symb_non_terminals;
}

/**
  *  Returns the initial symbol.
  */
const Symbol *Attr_grammar::get_initial_symb() const
{
    return ag_initial_symb;
}

/**
  * Returns vector with all rules with the left symbol equal that parameter.
  */
const vector<unsigned short> Attr_grammar::get_rules_with_left_symbol(const Symbol *symb) const
{
    vector<unsigned short> result;

    for(map<unsigned short, Rule>::const_iterator it(ag_rule.begin()); it != ag_rule.end(); it++)
    {
        if(it->second.get_left_symbol()->equals(*symb))
        {
            result.push_back(it->second.key());
        }
    }
    return result;
}

/**
  * Returns the index of an equation in this range of rules with l_value equals to ins.
  */
const unsigned short Attr_grammar::get_index_eq_with_context(const Expr_instance *ins, const vector<unsigned short> &context_rule) const
{
    short index_ins(ins->get_num());

	for(size_t i(0); i < context_rule.size(); i++)
    {
        const Rule &rule(ag_rule.find(context_rule[i])->second);

        for(map<unsigned short,Equation>::const_iterator it(rule.get_eqs().begin()); it != rule.get_eqs().end(); it++)
        {
            if (ins->get_attr()->is_synthetize())
            {
            	/* Only interesting compare symbol and attribute because left_symbol always has index 0. */
				if (it->second.get_l_value()->equals_without_index(ins))
				{
					if (index_ins == 0)
					{
						return it->first;
					}
					index_ins--;
				}
            }
            else
            {
            	/* The instance has a attrubute inherit, so must be compare with all information instance.  */
            	if (it->second.get_l_value()->equals(ins))
				{
					return it->first;
				}
            }
        }
    }
    return 0;
}

/**
  * Returns the equation with this index.
  */
const Equation *Attr_grammar::get_eq(const unsigned short index) const
{
    assert(index >= 1);
    assert(index <= count_eqs);
    /* The index is valid. */

    for(map<unsigned short,Rule>::const_reverse_iterator it_r(ag_rule.rbegin()); it_r != ag_rule.rend(); it_r++)
    {
        if(it_r->second.get_offset() <= index)
        /* The equation must belong to this rule. */
        {
            return it_r->second.get_eq(index);
        }
    }
    return NULL;
}

/**
  * Returns the l_value of the equation with this index.
  */
const Expr_instance *Attr_grammar::get_eq_l_value(const unsigned short index) const
{
    const Equation *eq(get_eq(index));
    assert(eq != NULL);
    return eq->get_l_value();
}

/**
  * Returns the count of equations in the grammar.
  */
const unsigned short Attr_grammar::get_count_eqs() const
{
    return count_eqs;
}

/**
  * Generates and returns a string reprensentation of a attribute grammar.
  * where sorts, operators, functions, attributes, symbols and rules, are
  * full representation of each type.
  */
const string Attr_grammar::to_string() const
{
    string semdomain("\nsemantic domain\n");
    semdomain.append(to_string_map<string, Sort>(ag_sort));
    semdomain.append("\n");
    semdomain.append(to_string_map<string, Function>(ag_func));
    semdomain.append("\nattributes\n");
    semdomain.append(to_string_map<string, Attribute>(ag_attr));
    semdomain.append("\n/*");
    semdomain.append("\nsymbols\n");
    semdomain.append(to_string_map<string, Symbol>(ag_symb_non_terminals));
    semdomain.append(to_string_map<string, Symbol>(ag_symb_terminals));
    semdomain.append("*/\n");
    semdomain.append("/*  >>>>>>>>>> Initial Symbol of Grammar is ");
    semdomain.append(ag_initial_symb->get_name());
    semdomain.append(" <<<<<<<<<<  */\n");
    semdomain.append("\nrules\n");
    semdomain.append(to_string_map<unsigned short, Rule>(ag_rule));
    semdomain.append("\n");
    return semdomain;
}

} /* end genevalmag */
