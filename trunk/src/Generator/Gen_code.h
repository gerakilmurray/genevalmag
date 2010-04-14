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
#include "../Evaluation/Builder_visit_sequences.h"

namespace genevalmag
{

class Gen_code
{
	private:
		string path_output;
		string file_name_header;
		string file_name_code;

		void generate_grammar_file(const Attr_grammar &attr_grammar) const;

		void generate_header_file();

		void generate_footer_header();

		void generate_code_file();

		void generate_structs(const Attr_grammar &attr_grammar);

		void generate_constructor(const vector<Visit_seq> & v_seq, const Builder_plans &b_plan, const Attr_grammar &attr_grammar);

		void generate_methods(const Builder_plans &b_plan, const Attr_grammar &attr_grammar);

		void generate_footer_code();

	public:
		Gen_code(const string &path_folder_output, const string &name_file);

		virtual ~Gen_code();

		bool generate_code(const Attr_grammar &attr_grammar, const Builder_plans &b_plan ,const vector<Visit_seq> &v_seq);
};

}

#endif /* GEN_CODE_H_ */
