/**
 * \file Operator.h
 * 	\brief Represents a operation.
 *  \date 28/09/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#ifndef OPERATOR_H_
#define OPERATOR_H_

#include <string>
#include "Sort.h"
#include <vector>

namespace genevalmag {

// operation's mode.
enum mod_op
{
	k_infix,
	k_suffix,
	k_prefix
};

class Operator
{
private:
	string 			o_name;
	vector <Sort*>	o_domain;
	Sort*			o_image;
	mod_op			o_mod;
	int				o_pred;
	int				o_id;

	//Methods for STL C++
	void copy(const Operator& other);
	void destroy();

public:
	Operator();
	Operator(string name, vector <Sort*> * v, Sort * img, int id);
	Operator(const Operator & other);
	virtual ~Operator();
	Operator& operator= (Operator & other);

	vector<Sort*> get_domain() const;
    int get_id() const;
    Sort* get_image() const;
    mod_op get_mod() const;
    string get_name() const;
    int get_pred() const;
    void add_domain(Sort* sort);

    void set_domain(vector<Sort*> domain);
    void set_id(int id);
    void set_image(Sort* image);
    void set_mod(string mod);
    void set_name(string name);
    void set_pred(int pred);
    string to_string();
    bool equals(Operator op) const;

    void clear();

};

}

#endif /* OPERADOR_H_ */
