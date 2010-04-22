/**
  *  \file      Function.h
  *  \brief     Class of the function of the grammar parsed.
  *  \date      26/11/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <string>
#include <vector>

#include "Sort.h"

namespace genevalmag
{

/**
  * Enumeration of operation's mode.
  */
enum oper_mode
{
    k_prefix,
    k_infix,
    k_postfix
};

/**
  * Enumeration of operation's associative modes.
  */
enum oper_assoc
{
    k_left,
    k_right,
    k_non_assoc
};

class Function
{
    private:
		/**
		  * \var f_name
		  * \brief Function's name.
		  */
        string                  f_name;
		/**
		  * \var f_domain
		  * \brief Function's sort domain.
		  */
        vector <const Sort*>    f_domain;
		/**
		  * \var f_image
		  * \brief Function's sort image.
		  */
        const Sort              *f_image;
		/**
		  * \var f_mod
		  * \brief Function's notation. Functions are always prefix. Operators can be anyone.
		  */
        oper_mode               f_mod;
		/**
		  * \var f_prec
		  * \brief Function's precedence.
		  */
        unsigned short          f_prec;
		/**
		  * \var f_assoc
		  * \brief Function's associativity.
		  */
        oper_assoc              f_assoc;
        /**
          * \var f_is_operator
          * \brief If that value is TRUE then the object function is a operator.
          *        This can be: prefix, infix or postfix.
          */
        bool                    f_is_operator;

        /**
          * Method of copy the function, STL-like C++.
          * @param other
          */
        void copy(const Function &other);
        /**
          * Method destroy function, STL-like C++.
          */
        void destroy();
        
    public:
        /**
          * Contructor empty of function.
          */
        Function();
        /**
          * Contructor copy of function.
          * @param other
          * @return
          */
        Function(const Function &other);

        /**
          * Destructor of the function.
          */
        virtual ~Function();

        /**
          * Operator assign(=) of function.
          * @param other
          * @return
          */
        Function &operator=(const Function &other);

        /**
          * Returns the name of the Function.
          * @return
          */
        string get_name() const;
        /**
          * Returns the domain of the Function.
          * @return
          */
        const vector<const Sort*> &get_domain() const;
        /**
          * Returns the image of the Function.
          * @return
          */
        const Sort *get_image() const;
        /**
          * Returns the mode of the operator.
          * @return
          */
        const oper_mode get_mode() const;
        /**
          * Returns the precedence of the operator.
          * @return
          */
        const unsigned short get_prec() const;
        /**
          * Returns the associativity of the operator.
          * @return
          */
        const oper_assoc get_oper_assoc() const;
        /**
          * Returns the arity of Function.
          * @return
          */
        const int get_arity() const;

        /**
          * Sets the name of the Function.
          * @param name
          */
        void set_name(const string name);
        /**
          * Sets the sort image of the Function.
          * @param image
          */
        void set_image(const Sort *image);
        /**
          * Sets the mode of the operator.
          * @param mode
          */
        void set_mode(const string mode);
        /**
          * Sets the precedence of the operator.
          * @param prec
          */
        void set_prec(const unsigned short prec);
        /**
          * Sets the associativity of the operator.
          * @param assoc
          */
        void set_oper_assoc(const string assoc);
        /**
          * Sets the boolean attribute with the parameter.
          * @param value
          */
        void set_is_operator(const bool value);

        /**
          * Enqueue a sort in the domain of the Function.
          * @param sort
          */
        void add_domain(const Sort *sort);

        /**
          * Generates and returns a string reprensentation of a Function.
          *
          * Result = "function" \<name\> ":" \<domain\> "->" \<image\> ";"
          *
          * where \<domain\> is= sort_1 ["(" \<instance\> ")" IF DEBUG IS ON] "," ... "," sort_n ["(" \<instance\> ")" IF DEBUG IS ON]
          *
          * @return
          */
        const string to_string() const;

        /**
          * Generates and returns a string with the signature of a Function.
          *
          * Result = \<image\> \<name\> "(" \<domain\> ");"
          *
          * or if is an operator:
          *
          * Result = \<image\> "operator"\<name\> "(" \<domain\> ");"
          *
          * where \<domain\> is = sort_1 P1"," ... "," sort_n Pn
          *
          * @return
          */
        const string signature() const;

        /**
          * Returns true if the Function is a Operator.
          * @return
          */
        const bool is_operator() const;

        /**
          * Compares the Function with other.
          * @param other
          * @return
          */
        const bool equals(const Function &other) const;

        /**
          * Generates and returns the string key that identifies a Function definitely.
          *
          * Result = \<name\> \<domain\> \<image\>
          *
          * where \<domain\> is = sort_1 ... sort_n
          * @return
          */
        const string key() const;
};

} /* end genevalmag */

#endif /* FUNCTION_H_ */
