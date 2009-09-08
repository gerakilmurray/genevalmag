/**
 * \file AttrGrammar.h
 * 	\brief Define a attribute grammar.
 *  \date 03/09/2009
 *  \author    Kilmurray, Gerardo Luis. 
 *  \author    Picco, Gonzalo M. 
 */

#ifndef ATTRGRAMMAR_H_
#define ATTRGRAMMAR_H_

#include "Rule.h"

namespace gen_eval_mag {

class AttrGrammar {
private:
	/**
	  * the first rule define the initial rule and
	  * the symbol of left side is the initial symbol of the grammar.
	  */
	Rule * rules[];


public:
	AttrGrammar();
	AttrGrammar(Rule init_rule);
	void add_rule(Rule rule);
	void remove_rule(int index);
	virtual ~AttrGrammar();
	Rule get_rule(int index);


};
}
#endif /* ATTRGRAMMAR_H_ */
