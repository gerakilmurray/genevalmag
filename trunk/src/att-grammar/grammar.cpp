/**
   \mainpage
   GenEval \n Generador de Evaluadores Estáticos
   <br>Director: Marcelo Daniel Arroyo <br>
   <hr>
   \author Kilmurray, Gerardo Luis
   \author Picco, Gonzalo Martín
   \date Agosto 2009

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

/**  \file grammar.cpp
  *      \brief Archivo que contiene la función main().
  *
  *  Este codigo es el encargado de realizar la llamadas a las funciones que realizan
  *  los algoritmos para ordenar los arreglos. Ademas se encarga de medir los tiempos
  *  que dichos algoritmos demoran y asi realizar un histograma. Para esto emplea
  *  las capacidades del utilitario &quot;GNUPLOT&quot;.
  */

#include "Attribute.h"
#include "AttrGrammar.h"

using namespace gen_eval_mag;

int main()
{
	Attribute val_N  = Attribute();
	Attribute val_B  = Attribute();
	Attribute val_L  = Attribute();
	Attribute val_L0 = Attribute();
	Attribute val_L1 = Attribute();
	Attribute pos_B  = Attribute();
	Attribute pos_L  = Attribute();
	Attribute pos_L0 = Attribute();
	Attribute pos_L1 = Attribute();

	val_L.setTipo(kSintetize);
	Rule *exampleGrammarRules[5];
	exampleGrammarRules[0] = new Rule();
	exampleGrammarRules[1] = new Rule();
	exampleGrammarRules[2] = new Rule();
	exampleGrammarRules[3] = new Rule();
	exampleGrammarRules[4] = new Rule();
	AttrGrammar exampleGram =  AttrGrammar(exampleGrammarRules);
	printf("Hello world %d", val_L.getTipo());
}
