/**
  *  \file		Gen_eval_AG.cpp
  *  \brief		Main module.
  *  \date		09/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <stdio.h>
#include <iostream>
#include <string>

#include "Parser/Parser_AG.h"
#include "Attr_grammar/Attr_grammar.h"

using namespace std;
using namespace genevalmag;

/**
  * /var attr_grammar
  * /brief Variable to represent Semantic domain.
  */
Attr_grammar attr_grammar;

/**
  *	Path of the input file with the specification of AG.
  */
#define PATH_INPUT_FILE "./src/Test/aritmetic.txt"

/**
  * Constant that represent the maximum size of the file buffer.
  */
#define MAX_INPUT_FILE 32000

/**
  * Constant that represent the maximum size of the line read.
  */
#define MAX_INPUT_LINE 256

/**
  * Reads the contents of the file and save it in the
  * string passed as parameter.
  */
void read_file_in(string &txt_output)
{
	FILE*	p_file;
	char	buffer[MAX_INPUT_FILE];

	p_file = fopen(PATH_INPUT_FILE, "r");
	if(p_file == NULL)
		perror("Error opening file");
	else
	{
		while(!feof(p_file))
		{
			  fgets(buffer, MAX_INPUT_LINE, p_file);
			  txt_output += buffer;
		}
		fclose(p_file);
	}
}

/**
  * Main method of the parsing.
  */
int main()
{
	string input_grammar;
	read_file_in(input_grammar);
	cout << "-------------------------\n";
	if(parse_grammar(input_grammar.c_str()))
	{
		cout << attr_grammar.to_string();
		cout << "-------------------------\n";
		cout << "Parsing OK\n";
	}
	else
	{
		cout << "Parsing FAILED\n";
	}
	cout << "-------------------------\n";
	cout << "Bye... :-D" << endl;
	return 0;
}
