/**
  *  \file		Builder_plan.h
  *  \brief		Header of generation plans module of Attribute Grammar.
  *  \date		18/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef BUILDER_PLAN_H_
#define BUILDER_PLAN_H_

#include <map>

#include "../Attr_grammar/Attr_grammar.h"
#include "../Attr_grammar/Rule.h"
#include "Builder_graphs.h"

using namespace std;

namespace genevalmag
{

class Builder_plan
{
	private:

	public:
		/**
		  * Constructor empty of Builder plan.
		  */
		Builder_plan();

		/**
		  * Destructor of Builder plan.
		  */
		~Builder_plan();

		/**
		  * Generates and saves all evaluation's plans for the Attribute Grammar.
		  */
		void build_plans(const Attr_grammar &attr_grammar);
};

} /* end genevalmag */

#endif /* BUILDER_PLAN_H_ */
