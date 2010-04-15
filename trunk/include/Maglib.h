/**
  *  \file		Maglib.h
  *  \brief		Header of the library of evaluator's generator.
  *  \date		14/04/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

/**
   \mainpage
   maglib - Multiplan Attribute Grammar Library
   <br>Director: Marcelo Daniel Arroyo <br>
   <hr>
   \author Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
   \author Picco, Gonzalo Martin <gonzalopicco@gmail.com>
   \date Mayo 2010

   \par Leeme:
   Trabajo realizado en el marco de la Tesis de Licenciatura en Ciencias de la Computación
   <ul>
   <li> Enlaces principales </li>
   <li> algo
   \htmlonly
   <strong>HTML válido</strong><br>

   \endhtmlonly
   </li>
   <li>etc...</li>
   </ul>
   <br><img src="../../../recursos/chinpance.png"><br>
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
