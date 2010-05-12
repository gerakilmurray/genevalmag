/**
  *  \file		Parser_AG.cpp
  *  \brief		Header of parsing module of Attribute Grammar.
  *  \date		09/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef PARSER_AG_H_
#define PARSER_AG_H_

#include <boost/spirit/include/classic_file_iterator.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>

#include "../Attr_grammar/Attr_grammar.h"

#include "Semantics_checks.h"

using namespace BOOST_SPIRIT_CLASSIC_NS;

namespace genevalmag
{

/**
  * Type definitions to report parsing errors, showing row and column.
  */
typedef char                  		 	char_t;
typedef file_iterator <char_t>   		iterator_f;
typedef position_iterator<iterator_f> 	iterator_t;


class Parser_AG
{
	private:
		/**
		  * \var attr_grammar.
		  * \brief Internal structure of grammar.
		  */
		Attr_grammar attr_grammar;
		/**
		  * \var sem_check.
		  * \brief Semantics control for grammar: Well define grammar.
		  */
		Semantics_checks sem_check;

	public:
		/**
		  * Constructor of Parser_AG.
		  */
		Parser_AG();
		/**
		  * Destructor of Parser_AG.
		  */
		~Parser_AG();
		/**
		  * Returns att_grammar of parser.
		  * @return
		  */
		const Attr_grammar &get_attr_grammar();

		/**
		  * This method invokes the method 'parse' of the library Spirit included in Boost.
		  * Returns true if could parse all the input.
		  * @param path_file_input
		  * @return
		  */
		bool parse_grammar(const string &path_file_input);

		/**
		  * This method saves all parsed string in a file.
		  * The file output is in argument path_output.
		  * @param path_output
		  */
		void save_grammar_file(const string path_output) const;
};

} /* end genevalmag */

#endif /* PARSER_AG_H_ */
