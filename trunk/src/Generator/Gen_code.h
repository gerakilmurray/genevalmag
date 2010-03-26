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
#include "../Evaluation/Build_visit_sequence.h"

namespace genevalmag
{

class Gen_code
{
	private:
		string path_output_code;

		string full_path;

		void generate_grammar_file(const Attr_grammar &attr_grammar) const;

		void generate_header_file();

		void generate_header_class();

		void generate_main();

		void generate_footer();

		void generate_private();

		void generate_public(const vector<Visit_seq> & v_seq, const Builder_plan &b_plan, const Attr_grammar &attr_grammar);

		void generate_methods(const Builder_plan &b_plan, const Attr_grammar &attr_grammar);

		void generate_externs(const Attr_grammar &attr_grammar);

		void generate_structs(const Attr_grammar &attr_grammar);

	public:
		Gen_code();
		Gen_code(string path);

		virtual ~Gen_code();

		void generate_code(const Attr_grammar &attr_grammar,const Builder_plan &b_plan ,const vector<Visit_seq> & v_seq);
};

}

#endif /* GEN_CODE_H_ */
