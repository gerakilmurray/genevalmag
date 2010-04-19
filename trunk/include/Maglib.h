/**
  *  \file		Maglib.h
  *  \brief		Header of the library of evaluator's generator.
  *  \date		14/04/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef MAGLIB_H_
#define MAGLIB_H_

namespace genevalmag
{

class Maglib
{
	public:
		/**
		  * Contructor empty of Mag_lib.
		  */
		Maglib();

		/**
		  * Destructor empty of Mag_lib.
		  */
		virtual ~Maglib();

		/**
		  * Generates the static evaluator's files for the Attribute grammar specificated in the
		  * input_path_file passed as parameter.
		  * All outputs of the library be saved in the path_folder_output.
		  * The evaluator classname is defined by name_library.
		  * The user could include somes headers for uses externs functions to evaluator.
		  */
		int gen_evaluator
		(
			const string path_input_file,
			const string path_folder_output,
			const string name_library,
			const vector<string> &headers
		) const;
};

} /* end genevalmag */

#endif /* MAGLIB_H_ */
