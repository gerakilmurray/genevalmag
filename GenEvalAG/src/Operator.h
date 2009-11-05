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
enum ModOp
{
	k_infix,
	k_suffix,
	k_prefix
};

class Operator
{
private:
	string 			o_name;
	vector <Sort>	o_domain;
	Sort			o_image;
	ModOp			o_mod;
	int				o_pred;
	int				o_id;

public:
	Operator();
	Operator(string name, vector <Sort> * v, Sort * img, int id);
	virtual ~Operator();

	vector<Sort> getDomain() const;
    int getId() const;
    Sort getImage() const;
    string getMod() const;
    string getName() const;
    int getPred() const;
    void add_domain(Sort s);

    void setDomain(vector<Sort> o_domain);
    void setId(int o_id);
    void setImage(Sort o_image);
    void setMod(string o_mod);
    void setName(string o_name);
    void setPred(int o_pred);
    string to_string() const;
    bool equals(Operator op) const;

};

}

#endif /* OPERADOR_H_ */
