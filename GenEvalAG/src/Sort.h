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

	//Methods for STL C++
	void copy(Sort const& other);
	void destroy();
public:
	Sort();
	Sort(string name);
	virtual ~Sort();
	Sort(Sort const & other);
	Sort& operator= (Sort const & other);

    int get_id() const;
    string get_name() const;
    void set_id(int id);
    void set_name(string name);
    bool equals(Sort s) const;
    string to_string() const;

    string key() const;
};

}

#endif /* SORT_H_ */
