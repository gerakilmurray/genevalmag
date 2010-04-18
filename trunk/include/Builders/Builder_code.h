/**
  *  \file		Builder_code.h
  *  \brief     Header with the functions for build the header and source code of the evaluator of MAG.
  *  \date		18/03/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef BUILDER_CODE_H_
#define BUILDER_CODE_H_

#include "../Attr_grammar/Attr_grammar.h"

#include "Builder_visit_sequences.h"

namespace genevalmag
{

class Builder_code
{
	private:
		/**
		  * Defines the path where the files generated be saved.
		  */
		string path_output;

		/**
		  * Defines the name of the files and the evaluator's class name.
		  */
		string file_name;

		/**
		  * Create the header file of the evaluator with some information.
		  */
		void generate_header_file() const;

		/**
		  * Insert the header file's footer of the evaluator.
		  */
		void generate_footer_header() const;

		/**
		  * Create the source code file of the evaluator with some information.
		  */
		void generate_code_file(const vector<string> &headers_file) const;

		/**
		  * Generates and inserts all structs for represent each symbol of the grammar.
		  * With constructor and to_string methods.
		  *		  *
		  *
		  * For symbol S, with attrs s1 <syn> int, inserts:
		  *
		  * typedef struct Symbol_S: Node
          * {
          *     int s0;
          *
          *     Symbol_S(unsgned short r_id);
          *
          *     string to_string() const;
          * } S ;
		  */
		void generate_structs(const Attr_grammar &attr_grammar) const;

		/**
		  * Generates and inserts the evaluator class's constructor.
		  * With all initializations of Evaluation Plans, Evaluation Plans Project, Visit Sequences and Rules.
		  */
		void generate_constructor(const vector<Visit_seq> & v_seq, const Builder_plans &b_plan, const Attr_grammar &attr_grammar) const;

		/**
		  * Generates and inserts all class methods, includind traverse, visit evaluator and the main evaluator.
		  * This methods are based on the article by Wuu Yang.
		  */
		void generate_methods(const Builder_plans &b_plan, const Attr_grammar &attr_grammar) const;

		/**
		  * Insert the source code file's footer of the evaluator.
		  */
		void generate_footer_code() const;

		/**
		  * Generates the print method, for show the all visit sequences.
		  */
		void generate_print(string &text) const;

		/**
		  * Generates the print method, for show the all visit sequences in a format more descriptive.
		  */
		void generate_translate(string &text) const;

		/**
		  * Generates the method that crosses the AST and sets the evaluation plan that corresponds to each node.
		  */
		void generate_traverse(string &text) const;

		/**
		  * Generates a method with a large switch with all equations, invoking in each case,
		  * the method that computes.
		  */
		void generate_all_compute_eq(string &text, const Attr_grammar &attr_grammar) const;

		/**
		  * Generates the evaluating method, which performs the method invocations
		  * to be computed all the attributes of the AST.
		  */
		void generate_evaluator(string &text, const Builder_plans &b_plan) const;

		/**
		  * Generates the evaluator method, which following the visit sequences drawn,
		  * visit the nodes of the tree until computes it completely.
		  */
		void generate_eval_visiter(string &text) const;

	public:
		/**
		  * Contructor with the path and name of output files to be generated.
		  */
		Builder_code(const string &path_folder_output, const string &name_file);

		/**
		  * Destructor of the Builder_code.
		  */
		virtual ~Builder_code();

		/**
		  * Generates the header and source code of the static evaluator of the grammar passed as parameter,
		  * alog with their evaluations plans, visit sequence and headers for uses user functions defined.
		  */
		bool generate_code(const Attr_grammar &attr_grammar, const Builder_plans &b_plan ,const vector<Visit_seq> &v_seq, const vector<string> &headers_file) const;
};

}

#endif /* BUILDER_CODE_H_ */
