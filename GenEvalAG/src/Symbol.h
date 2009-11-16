/**
 * \file Symbol.h
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 04/11/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <vector>
#include <string>

#include "Attribute.h"

namespace genevalmag {

// Symbol's type.
enum symb_type
{
	k_terminal,
	k_non_terminal
};

class Symbol {
	private:
		string sym_name;
		symb_type sym_type;
		vector<Attribute*> attrs;

		//Methods for STL C++
		void copy(Symbol const& other);
		void destroy();

	public:
		Symbol();
		Symbol(string name, symb_type type);
		Symbol(Symbol const & other);
		virtual ~Symbol();
		Symbol& operator= (Symbol const & other);

		void add_attr(Attribute* attr);
		void remove_attr(const int index);
		string get_name() const;
		void set_name(string name);
		symb_type get_type() const;
		void set_type(symb_type type);
	    bool equals(Symbol symb) const;
	    string to_string() const;
	    vector<Attribute*> get_attrs() const;
	    bool is_non_terminal() const;

	    string key() const;

};
}

#endif /* SYMBOL_H_ */
