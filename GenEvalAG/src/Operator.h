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
#include <vector>


#include "Sort.h"

namespace genevalmag {

// operation's mode.
enum mod_op
{
	k_prefix,
	k_infix,
	k_postfix

};

// operation associative's mode.
enum mod_assoc
{
	k_left,
	k_right,
	k_nonassoc
};

class Operator
{
private:
	string 			o_name;
	vector <Sort*>	o_domain;
	Sort*			o_image;
	mod_op			o_mod;
	unsigned int	o_pred;
	unsigned int	o_id;
	mod_assoc 		o_assoc;

	//Methods for STL C++
	void copy(const Operator& other);
	void destroy();

public:
	Operator();
	Operator(string name, vector <Sort*> * vec, Sort * img, int id);
	Operator(const Operator & other);
	virtual ~Operator();
	Operator& operator= (Operator & other);

	vector<Sort*> get_domain() const;
    int get_id() const;
    Sort* get_image() const;
    mod_op get_mod() const;

    mod_assoc get_mod_assoc() const;
    string get_name() const;
    int get_pred() const;
    void add_domain(Sort* sort);

    void set_domain(vector<Sort*> domain);
    void set_id(int id);
    void set_image(Sort* image);
    void set_mod(string mod);

    void set_mod_assoc(string mod);
    void set_name(string name);
    void set_pred(int pred);

    string to_string();
    bool equals(Operator op) const;

    void purge();

    string key() const;

};

}

#endif /* OPERADOR_H_ */
