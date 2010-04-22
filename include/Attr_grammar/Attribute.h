/**
  *  \file      Attribute.h
  *  \brief     Class of the attribute of the grammar parsed.
  *  \date      23/10/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include "Sort.h"

namespace genevalmag
{

/**
  * Enumeration of the attribute's type: Inherit or Synthetize.
  */
enum type_attr
{
    k_inherit,  //!< k_inherit
    k_synthetize//!< k_synthetize
};

class Attribute
{
    private:
		/**
		 * \var a_name
		 * \brief Attribute's name.
		 */
        string         a_name;
		/**
		 * \var a_sort_type
		 * \brief Attribute's type sort.
		 */
        const Sort     *a_sort_type;
		/**
		 * \var a_mod_type
		 * \brief Attribute's type.
		 */
        type_attr      a_mod_type;
		/**
		 * \var a_member_symbol
		 * \brief Attribute's member list.
		 */
        string         a_member_symbol;

        /**
          * Method of copy the attribute, STL-like C++.
          * @param other
          */
        void copy(const Attribute &other);
        /**
          * Method destroy attribute, STL-like C++.
          */
        void destroy();

    public:
        /**
          * Constructor empty of attribute.
          */
        Attribute();
        /**
          * Constructor copy of attribute.
          * @param other
          * @return
          */
        Attribute(const Attribute &other);

        /**
          * Destructor of attribute.
          */
        virtual ~Attribute();

        /**
          * Operator assign(=) of attribute.
          * @param other
          * @return
          */
        Attribute &operator=(const Attribute &other);

        /**
          * Returns the name of the attribute.
          * @return
          */
        const string get_name() const;
        /**
          * Returns the sort type of the attribute.
          * @return
          */
        const Sort *get_sort_type() const;
        /**
          * Returns the modifiers of the attribute.
          * @return
          */
        const type_attr get_mod_type() const;
        /**
          * Returns the membership list of the attribute.
          * @return
          */
        const string get_member_symbol() const;

        /**
          * Sets the name of the attribute.
          * @param name
          */
        void set_name(const string name);
        /**
          * Sets the sort type of the attribute.
          * @param sort_type
          */
        void set_sort_type(const Sort *sort_type);
        /**
          * Sets the modifiers of the attribute.
          * @param mod_type
          */
        void set_mod_type(const type_attr mod_type);
        /**
          * Sets the membership list of the attribute.
          * @param member_symbol
          */
        void set_member_symbol(const string member_symbol);

        /**
          * Returns true if the modifiers of the attribute is synthetize.
          * @return
          */
        const bool is_synthetize() const;
        /**
          * Returns true if the modifiers of the attribute is inherit.
          * @return
          */
        const bool is_inherit() const;

        /**
          * Generates and returns a string reprensentation of a attribute.
          *
          * Result = name ":" modifiers "<" sort_type ["(" instance ")" IF DEBUG IS ON] "> of " membership_list
          *
          * @return
          */
        const string to_string() const;

        /**
          * Compares the attribute with other.
          * @param other
          * @return
          */
        const bool equals(const Attribute &other) const;

        /**
          * Generates and returns the string key that identifies a attribute definitely.
          *
          * Result = name modifiers sort_type membership_list
          *
          * @return
         */
        const string key() const;
};

} /* end genevalmag */

#endif /* ATTRIBUTE_H_ */
