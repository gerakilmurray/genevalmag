/**
  *  \file		Semantic_check.h
  *  \brief		Header method semantic check of Attribute grammar.
  *  \date		28/09/2009
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */
#ifndef SEMCKECK_H_
#define SEMCKECK_H_

#include "ast/Ast_function.h"

using namespace genevalmag;

void check_precedence(Ast_function ** root_tree);

void check_associativity(Ast_function ** root_tree);

void increment_level(char name);

void decrement_level(char name);

void reset_semantic_context();

#endif
