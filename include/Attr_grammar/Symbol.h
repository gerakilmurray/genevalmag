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
		/**
		  * \var symb_name
		  * \brief Symbol's name.
		  */
        string                      symb_name;
		/**
		  * \var symb_type
		  * \brief Symbol's type.
		  */
        symbol_type                 symb_type;
		/**
		  * \var symb_attrs
		  * \brief Symbol's vector attribute.
		  */
        vector<const Attribute*>    symb_attrs;
		/**
		  * \var symb_id
		  * \brief Symbol's identifier.
		  */
        unsigned short				symb_id;

        /**
          * Method of copy the symbol, STL-like C++.
          * @param other
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
          * @param name
          * @param type
          * @return
          */
        Symbol(const string &name, const symbol_type &type);
        /**
          * Constructor copy of Symbol.
          * @param other
          * @return
          */
        Symbol(const Symbol &other);

        /**
          * Destructor of Symbol.
          */
        virtual ~Symbol();

        /**
          * Operator assign(=) of Symbol.
          * @param other
          * @return
          */
        Symbol &operator=(const Symbol &other);

        /**
          * Returns the name of the Symbol.
          * @return
          */
        string get_name() const;
        /**
          * Returns the type of the Symbol.
          * @return
          */
        symbol_type get_type() const;
        /**
		  * Returns the id of the Symbol.
		  * @return
          */
		unsigned short get_id() const;
        /**
          * Returns the list of attributes of the Symbol.
          * @return
		  */
        const vector<const Attribute*> &get_attrs() const;
        /**
          * Finds in the list of attribute of the symbol and
          * returns the attribute with that name passed as parameter.
          * @param name_attr
          * @return
          */
        const Attribute *get_attribute(const string &name_attr) const;

        /**
          * Sets the name of the Symbol.
          * @param name
          */
        void set_name(const string name);
        /**
          * Sets the type of the Symbol.
          * @param type
          */
        void set_type(const symbol_type type);
        /**
		  * Sets the id of the Symbol.
		  * @param id
          */
		void set_id(unsigned short id);
        /**
          * Enqueues a attribute in the list of the Symbol.
          * @param attr
		  */
        void add_attr(const Attribute *attr);

        /**
          * Returns true if the Symbol's type is Non Terminal.
          * @return
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
          *
          * @return
          */
        string to_string() const;

        /**
          * Compares the Symbol with other.
          * @param other
          * @return
          */
        bool equals(const Symbol &other) const;

        /**
          * Generates and returns the string key that identifies a Symbol definitely.
          *
          * Result= \<name\>
          *
          * @return
          */
        string key() const;
};

} /* end genevalmag */

#endif /* SYMBOL_H_ */
