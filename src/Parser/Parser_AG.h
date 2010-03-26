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
#include "Semantic_check.h"

using namespace BOOST_SPIRIT_CLASSIC_NS;

namespace genevalmag
{

typedef char                  		 	char_t;
typedef file_iterator <char_t>   		iterator_f;
typedef position_iterator<iterator_f> 	iterator_t;


class Parser_AG
{
	private:
		Attr_grammar attr_grammar;

		Semantic_check sem_check;

	public:
		Parser_AG();
		~Parser_AG();

		const Attr_grammar &get_attr_grammar();

	/**
	  * This method invokes the method 'parse' of the library Spirit included in Boost.
	  * Returns true if could parse all the input.
	  */
	bool parse_grammar(const string path_file_input);
};

} /* end genevalmag */

#endif /* PARSER_AG_H_ */
