/**
  *  \file      Sort.h
  *  \brief     Class of the sort of the grammar parsed.
  *  \date      28/09/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef SORT_H_
#define SORT_H_

/**
  * Enable/disable all output debuger in all class
  */
#define _DEBUG

#include <string>

using namespace std;

namespace genevalmag
{

class Sort
{
    private:
        string          s_name;
        unsigned int    s_ins;
        bool            s_type_basic;

        /**
          * Method of copy the Sort, STL-like C++.
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
          */
        Sort(string name);
        /**
          * Contructor copy of Sort.
          */
        Sort(const Sort &other);

        /**
          * Destructor of Sort.
          */
        virtual ~Sort();

        /**
          * Operator assign(=) of Sort.
          */
        Sort &operator=(const Sort &other);

        /**
          * Returns the name of the Sort.
          */
        string get_name() const;
        /**
          * Returns the instance of the Sort.
          */
        int get_ins() const;

        /**
          * Sets the name of the Sort.
          */
        void set_name(string name);
        /**
          * Sets if the Sort is basic.
          */
        void set_type_basic(bool type_basic);

        /**
          * Generates and returns a string reprensentation of a Sort.
          *
          * Result = "sort" \<name\> ["(" \<instance\> ")" IF DEBUG IS ON] ";"
          */
        string to_string() const;

        /**
          * Compares the Sort with other.
          */
        bool equals(const Sort &other) const;

        /**
          * Returns if the Sort is basic.
          */
        bool is_type_basic() const;

        /**
          * Generates and returns the string key that identifies a Sort definitely.
          *
          * Result = \<name\>
          */
        string key() const;
};

} /* end genevalmag */

#endif /* SORT_H_ */
