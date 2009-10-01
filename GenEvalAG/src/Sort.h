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
    int getId() const;
    string getName() const;
    void setId(int s_id);
    void setName(string s_name);
    bool equals(Sort s);
    string to_string();
};

}

#endif /* SORT_H_ */
