/**
  *  \file		Gen_code.h
  *  \brief
  *  \date		18/03/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef GEN_CODE_H_
#define GEN_CODE_H_

#include "../Attr_grammar/Attr_grammar.h"
#include "../Builders/Builder_visit_sequences.h"

namespace genevalmag
{

class Gen_code
{
	private:
		string path_output;
		string file_name;

		void generate_header_file() const;

		void generate_footer_header() const;

		void generate_code_file(const vector<string> &headers_file) const;

		void generate_structs(const Attr_grammar &attr_grammar) const;

		void generate_constructor(const vector<Visit_seq> & v_seq, const Builder_plans &b_plan, const Attr_grammar &attr_grammar) const;

		void generate_methods(const Builder_plans &b_plan, const Attr_grammar &attr_grammar) const;

		void generate_footer_code() const;

		void generate_print(string &text) const;

		void generate_translate(string &text) const;

		void generate_traverse(string &text) const;

		void generate_all_compute_eq(string &text, const Attr_grammar &attr_grammar) const;

		void generate_evaluator(string &text, const Builder_plans &b_plan) const;

		void generate_eval_visiter(string &text) const;

	public:
		Gen_code(const string &path_folder_output, const string &name_file);

		virtual ~Gen_code();

		bool generate_code(const Attr_grammar &attr_grammar, const Builder_plans &b_plan ,const vector<Visit_seq> &v_seq, const vector<string> &headers_file) const;
};

}

#endif /* GEN_CODE_H_ */
