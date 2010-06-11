/**
  *  \file      Sort.h
  *  \brief     Class of the sort of the attribute grammar.
  *  \date      28/09/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef SORT_H_
#define SORT_H_

#include <string>

using namespace std;

namespace genevalmag
{

class Sort
{
    private:
		/**
		  * \var s_name
		  * \brief Sort's name.
		  */
        string          s_name;
		/**
		  * \var s_ins
		  * \brief Sort's instance.
		  */
        unsigned int    s_ins;
		/**
		  * \var s_type_basic
		  * \brief Is true iff is a type basic of C++.
		  */
        bool            s_type_basic;

        /**
          * Method of copy the Sort, STL-like C++.
          * @param other
          */
        void copy(const Sort &other);
        /**
          * Method destroy Sort, STL-like C++.
          */
        void destroy();

    public:
        /**
          * Contructor empty of Sort.
          */
        Sort();
        /**
          * Contructor with the name of the Sort.
          * @param name
          * @return
          */
        Sort(const string name);
        /**
          * Contructor copy of Sort.
          * @param other
          * @return
          */
        Sort(const Sort &other);

        /**
          * Destructor of Sort.
          */
        virtual ~Sort();

        /**
          * Operator assign(=) of Sort.
          * @param other
          * @return
          */
        Sort &operator=(const Sort &other);

        /**
          * Returns the name of the Sort.
          * @return
          */
        const string get_name() const;

        /**
          * Sets the name of the Sort.
          * @param name
          */
        void set_name(const string name);
        /**
          * Sets if the Sort is basic.
          * @param type_basic
          */
        void set_type_basic(const bool type_basic);

        /**
          * Generates and returns a string reprensentation of a Sort.\n
          *\n
          * Result = "sort" \<name\> ["(" \<instance\> ")" IF DEBUG IS ON] ";"\n
          * @return
          */
        const string to_string() const;

        /**
          * Compares the Sort with other.
          * @param other
          * @return
          */
        const bool equals(const Sort &other) const;

        /**
          * Returns if the Sort is basic.
          * @return
          */
        const bool is_type_basic() const;

        /**
          * Generates and returns the string key that identifies a Sort definitely.\n
          *\n
          * Result = \<name\>\n
          *
          * @return
          */
        const string key() const;
};

} /* end genevalmag */

#endif /* SORT_H_ */
