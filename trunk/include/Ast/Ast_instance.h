/**
  *  \file      Ast_instance.h
  *  \brief     Instance element of an Attribute Syntax Tree (AST).
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef AST_INSTANCE_H_
#define AST_INSTANCE_H_

#include "Ast_leaf.h"

#include "../Attr_grammar/Symbol.h"
#include "../Attr_grammar/Attribute.h"

namespace genevalmag
{

class Ast_instance: public Ast_leaf
{
    private:
		/**
		  * \var i_symb.
		  * \brief Symbol of Ast_instance.
		  */
        const Symbol			*i_symb;
        /**
		  * \var i_num.
		  * \brief Syntax index of the instance.
		  */
        unsigned short			i_num;
        /**
		  * \var i_attr.
		  * \brief Attribute of Ast_instance.
		  */
        const Attribute			*i_attr;

        /**
          * Method of copy the Ast_instance, STL-like C++.
          * @param other
          */
        void copy(const Ast_instance &other);
        /**
          * Method destroy Ast_instance, STL-like C++.
          */
        void destroy();

    public:
        /**
          * Constructor empty of Ast_instance.
          * @return
          */
        Ast_instance();
        /**
          * Constructor copy of Ast_instance.
          * @param other
          * @return
          */
        Ast_instance(const Ast_instance &other);

        /**
          * Destructor of Ast_instance.
          * @return
          */
        virtual ~Ast_instance();

        /**
          * Operator assign(=) of Ast_instance.
          * @param other
          * @return
          */
        Ast_instance &operator=(const Ast_instance &other);

        /**
          * Returns the attribute pointer of the Ast_instance.
          * @return
          */
        const Attribute *get_attr() const;

        /**
          * Returns the number of the Ast_instance.
          * @return
          */
        unsigned short get_num() const;

        /**
          * Returns the symbol pointer of the Ast_instance.
          * @return
          */
        const Symbol *get_symb() const;

        /**
          * Sets the attribute pointer of the Ast_instance.
          * @param attr
          */
        void set_attr(const Attribute *attr);

        /**
          * Sets the number of the Ast_instance.
          * @param num
          */
        void set_num(unsigned short num);

        /**
          * Sets the symbol pointer of the Ast_instance.
          * @param symb
          */
        void set_symb(const Symbol *symb);

        /**
          * Generates and returns a string reprensentation of a Ast_instance.\n
          *\n
          * Result= \<symbol\>"["\<number\>"]."\<attribute\>\n
          *\n
          * Ex: E[0].valor\n
          * @return
          */
        string to_string() const;

        /**
          * Compares the Ast_instance with other.\n
          * Respects Symbol and attribute.
          * @param other
          * @return
          */
        bool equals_without_index(const Ast_instance *other) const;

        /**
          * Generates and returns the string key that identifies an Ast_instance definitely.\n
          *\n
          * Result= \<symbol\>\<number\>\<attribute\>\n
          *\n
          * Ex: E0valor\n
          * @return
          */
        string key() const;
};

} /* end genevalmag */

#endif /* AST_INSTANCE_H_ */
