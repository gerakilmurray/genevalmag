/**
 * \file Sort.h
 * 	\brief Represents a sort.
 *  \date 28/09/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#ifndef SORT_H_
#define SORT_H_

#include <string>

using namespace std;
namespace genevalmag {

class Sort {
private:
	string s_name;
	int s_id;
public:
	Sort();
	Sort(string name);
	virtual ~Sort();
    int get_id() const;
    string get_name() const;
    void set_id(int id);
    void set_name(string name);
    bool equals(Sort s) const;
    string to_string() const;
};

}

#endif /* SORT_H_ */
