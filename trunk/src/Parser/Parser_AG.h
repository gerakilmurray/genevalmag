/**
  *  \file		Parser_AG.cpp
  *  \brief		Header of parsing module of Attribute Grammar.
  *  \date		09/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef PARSER_AG_H_
#define PARSER_AG_H_

/**
  * This method invokes the method 'parse' of the library Spirit included in Boost.
  * Returns true if could parse all the input.
  */
bool parse_grammar(char const *txt_input);

#endif /* PARSER_AG_H_ */
