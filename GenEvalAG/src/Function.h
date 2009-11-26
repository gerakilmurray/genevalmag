/**
 * \file Function.h
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 26/11/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <string>
#include <vector>
#include "Sort.h"

namespace genevalmag {

class Function {
private:
	string 			f_name;
	vector <Sort*>	f_domain;
	Sort*			f_image;

	//Methods for STL C++
	void copy(const Function& other);
	void destroy();
public:
	Function();
	virtual ~Function();
	Function(string name, vector <Sort*> * vec, Sort * img);
	Function(const Function & other);
	Function& operator= (Function & other);

	vector<Sort*> get_domain() const;

    Sort* get_image() const;

    string get_name() const;

    void add_domain(Sort* sort);

    void set_domain(vector<Sort*> domain);

    void set_image(Sort* image);

    void set_name(string name);


    string to_string();
    bool equals(Function op) const;

    void purge();

    string key() const;
};

}

#endif /* FUNCTION_H_ */
