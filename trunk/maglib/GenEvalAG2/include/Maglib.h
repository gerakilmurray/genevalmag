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
	Maglib();
	virtual ~Maglib();
	int gen_evaluator(const string path_input_file, const string path_folder_output,
			const string name_library, const vector<string> &headers) const;
};

} /* end genevalmag */

#endif /* MAGLIB_H_ */
