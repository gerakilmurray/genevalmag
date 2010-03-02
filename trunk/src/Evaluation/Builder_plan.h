/**
  *  \file		Builder_plan.h
  *  \brief		Header of generation plans module of Attribute Grammar.
  *  \date		18/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef BUILDER_PLAN_H_
#define BUILDER_PLAN_H_

#include "../Attr_grammar/Attr_grammar.h"

namespace genevalmag
{

class Builder_plan
{
	private:
	//	map <int,plam> plans;
	public:
		Builder_plan();
		~Builder_plan();
		void build_plans(const Attr_grammar &attr_grammar);

};
} // end genevalmag

#endif /* BUILDER_PLAN_H_ */
