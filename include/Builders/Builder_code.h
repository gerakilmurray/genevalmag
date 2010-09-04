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
		  * \var attr_grammar.
		  * \brief References to the attribute grammar.
		  */
		const Attr_grammar &attr_grammar;

		/**
		  * \var b_plans.
		  * \brief References to all plans generates.
		  */
		const Builder_plans &b_plans;

		/**
		  * \var b_v_seq.
		  * \brief References to all visit sequences generates.
		  */
		const Builder_visit_sequences &b_v_seq;

		/**
		  * \var path_output
		  * \brief Defines the path where the files generated be saved.
		  */
		string path_output;

		/**
		  * \var file_name
		  * \brief Defines the name of the files and the evaluator's class name.
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
		  * @param headers_file
		  */
		void generate_code_file(const vector<string> &headers_file) const;

		/**
		  * Generates and inserts all structs for represent each symbol of the grammar.
		  * With constructor and to_string methods.
		  *
		  * For symbol S, with attrs s1 \<syn\> int, inserts:\n
		  *\n
		  * typedef struct Symbol_S: Node\n
          * {\n
          *     int s0;\n
          *\n
          *     Symbol_S(unsgned short r_id);\n
          *\n
          *     string to_string() const;\n
          * } S ;\n
		  */
		void generate_structs() const;

		/**
		  * Generates and inserts the evaluator class's constructor.
		  * With all initializations of Evaluation Plans, Evaluation Plans Project, Visit Sequences and Rules.
		  */
		void generate_constructor() const;

		/**
		  * Generates and inserts all class methods, includind traverse, visit evaluator and the main evaluator.
		  * This methods are based on the article by Wuu Yang.
		  */
		void generate_methods() const;

		/**
		  * Insert the source code file's footer of the evaluator.
		  */
		void generate_footer_code() const;

		/**
		  * Generates the print method, for show the all visit sequences.
		  * @return
		  */
		string generate_print() const;

		/**
		  * Generates the print method, for show the all visit sequences in a format more descriptive.
		  * @return
		  */
		string generate_translate() const;

		/**
		  * Generates the method that crosses the AST and sets the evaluation plan that corresponds to each node.
		  * @return
		  */
		string generate_traverse() const;

		/**
		  * Generates a method with a large switch with all equations, invoking in each case,
		  * the method that computes.
		  * @return
		  */
		string generate_all_compute_eq() const;

		/**
		  * Generates the evaluating method, which performs the method invocations
		  * to be computed all the attributes of the AST.
		  * @return
		  */
		string generate_evaluator() const;

		/**
		  * Generates the evaluator method, which following the visit sequences drawn,
		  * visit the nodes of the tree until computes it completely.
		  * @return
		  */
		string generate_eval_visiter() const;

		/**
		  * Generates and inserts the class method that insert a new plan.
		  * @return
		  */
		string generate_add_plan() const;
		/**
		  * Generates and inserts the class method that insert a new projected plan.
		  * @return
		  */
		string generate_add_plan_project() const;

		/**
		  * Generates one method for each equation in the grammar, that computes it's value.
		  * @return
		  */
		string generate_all_methods_eqs() const;

		/**
		  * Generates the initialization of all rules.
		  * @return
		  */
		string generate_initialize_rules() const;

		/**
		  * Generates the initialization of all visit sequences.
		  * @return
		  */
		string generate_initialize_v_seq() const;

		/**
		  * Generates the initialization of all contexts rules uniques.
		  * @return
		  */
		string generate_initialize_context() const;

		/**
		  * Generates the initialization of all evaluations plans.
		  * @return
		  */
		string generate_initialize_plans() const;

		/**
		  * Generates the initialization of all evaluation plan projects.
		  * @return
		  */
		string generate_initialize_plan_proj() const;

	public:
		/**
		  * Contructor with the path and name of output files to be generated.
		  * @param path_folder_output
		  * @param name_file
		  * @param attribute_grammar
		  * @param builder_plan
		  * @param builder_v_seq
		  * @return
		  */
		Builder_code
		(
			const string &path_folder_output,
			const string &name_file,
			const Attr_grammar &attribute_grammar,
			const Builder_plans &builder_plan,
			const Builder_visit_sequences &builder_v_seq
		);

		/**
		  * Destructor of the Builder_code.
		  * @return
		  */
		virtual ~Builder_code();

		/**
		  * Generates the header and source code of the static evaluator of the grammar passed as parameter,
		  * with their evaluations plans, visit sequence and headers for uses user functions defined.
		  * @param headers_file
		  * @param path
		  * @return
		  */
		bool generate_code(const vector<string> &headers_file, const string path) const;
};

} /* end genevalmag */

#endif /* BUILDER_CODE_H_ */
