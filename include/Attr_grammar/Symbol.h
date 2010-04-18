/**
  *  \file      Symbol.h
  *  \brief     Class of the symbol of the grammar parsed.
  *  \date      04/11/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <vector>
#include <string>

#include "Attribute.h"

namespace genevalmag
{

/**
  * Enumeration of symbol's type.
  */
enum symbol_type
{
    k_terminal,
    k_non_terminal
};

class Symbol
{
    private:
        string                      symb_name;
        symbol_type                 symb_type;
        vector<const Attribute*>    symb_attrs;

        /**
          * Method of copy the symbol, STL-like C++.
          */
        void copy(const Symbol &other);
        /**
          * Method destroy symbol, STL-like C++.
          */
        void destroy();

    public:
        /**
          * Constructor empty of Symbol.
          */
        Symbol();
        /**
          * Constructor with name and type of Symbol.
          */
        Symbol(string &name, symbol_type type);
        /**
          * Constructor copy of Symbol.
          */
        Symbol(const Symbol &other);

        /**
          * Destructor of Symbol.
          */
        virtual ~Symbol();

        /**
          * Operator assign(=) of Symbol.
          */
        Symbol &operator=(const Symbol &other);

        /**
          * Returns the name of the Symbol.
          */
        string get_name() const;
        /**
          * Returns the type of the Symbol.
          */
        symbol_type get_type() const;
        /**
          * Returns the list of attributes of the Symbol.
          */
        const vector<const Attribute*> &get_attrs() const;
        /**
         * Finds in the list of attribute of the symbol and
         * returns the attribute with that name passed as parameter.
         */
        const Attribute *get_attribute(const string &name_attr) const;

        /**
          * Sets the name of the Symbol.
          */
        void set_name(string name);
        /**
          * Sets the type of the Symbol.
          */
        void set_type(symbol_type type);

        /**
          * Enqueues a attribute in the list of the Symbol.
          */
        void add_attr(const Attribute *attr);

        /**
          * Returns true if the Symbol's type is Non Terminal.
          */
        const bool is_non_terminal() const;

        /**
          * Generates and returns a string reprensentation of a Symbol.
          *
          * Result= "symbol" \<name\> \<type\> ";"
          *
          * where if \<type\> is Non Terminal, then list the attributes of the symbol.
          *
          * list = "Attributes:" attr_1 "," ... "," attr_n
          */
        string to_string() const;

        /**
          * Compares the Symbol with other.
          */
        bool equals(const Symbol &other) const;

        /**
          * Generates and returns the string key that identifies a Symbol definitely.
          *
          * Result= \<name\>
          */
        string key() const;
};

} /* end genevalmag */

#endif /* SYMBOL_H_ */
