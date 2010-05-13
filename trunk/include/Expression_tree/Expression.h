/**
  *  \file      Expression.h
  *  \brief     Abstract expression.
  *  \date      21/12/2009
  *  \author    Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author    Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <string>

#include "../Attr_grammar/Sort.h"

using namespace std;

namespace genevalmag
{

class Expression
{
    protected:
		/**
		  * \var parent.
		  * \brief Father of Expression.
		  */
        const Expression    *parent;
        /**
		  * \var type_synthetized.
		  * \brief Type of node: Obtains of parse.
		  */
        string            type_synthetized;
        /**
		  * \var conflict.
		  * \brief Mark when conflicted node.\n
		  *        This conflict is a conflict in the parse.\n
		  *        Used for define the precedence of function.\n
		  */
        int               conflict;

    public:
        /**
          * Constructor of Expression.
          * @return
          */
        Expression();

        /**
          * Destructor of Expression.
          * @return
          */
        virtual ~Expression();

        /**
          * Returns the parent pointer of the Expression.
          * @return
          */
        const Expression *get_parent() const;

        /**
          * Returns the type synthetized of the Expression.
          * @return
          */
        const string get_type_synthetized() const;

        /**
          * Returns the precendence wath produces the conflict.
          * @return
          */
        int get_conflict() const;

        /**
          * Sets the parent pointer of the Expression.
          * @param new_parent
          */
        void set_parent(const Expression *new_parent);

        /**
          * Returns the type synthetized of the Expression.
          * @param new_type_synthetized
          */
        void set_type_synthetized(string new_type_synthetized);

        /**
          * Sets the parent pointer of the Expression in NULL.
          */
        void delete_parent();

        /**
          * Turn on the conflict flag with the precendence wath produces.
          * @param prec_conflict
          */
        void active_conflict(int prec_conflict);

        /**
          * Turn off the conflict flag with negative precendence.
         */
        void desactive_conflict();

        /**
          * Generate and return a string reprensentation of a Expression.
          * @return
          */
        virtual string to_string() const = 0;
};

} /* end genevalmag */

#endif /* EXPRESSION_H_ */
