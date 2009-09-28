/**
 * \file SemDomain.cpp
 * 	\brief EXPLICAR QUE ES ESTO
 *  \date 28/09/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#include "SemDomain.h"
#include <iostream>

using namespace std;
namespace genevalmag {

SemDomain::SemDomain() {

}

SemDomain::~SemDomain() {
	// TODO Auto-generated destructor stub
}

void SemDomain::add_sort(Sort s)
{
this->v_sort.push_back(s);
	}
void SemDomain::add_op(Operator op)
{
	this->v_op.push_back(op);
	}
void SemDomain::print_sort()
{
cout << "Sort:\n";
for (vector<Sort>::size_type i = 0; i < this->v_sort.size(); ++i)
   cout << i+1 << ": " << this->v_sort[i].getName() << endl;
}

}
