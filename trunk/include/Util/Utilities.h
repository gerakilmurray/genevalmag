/**
  *  \file		Utilities.h
  *  \brief		Header of utilities module, where are methods and function used by many class.
  *  \date		09/03/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>

#include "../Expression_tree/Expr_leaf.h"
#include "../Attr_grammar/Symbol.h"
#include "../Builders/Builder_graphs.h"

using namespace std;

using namespace genevalmag;

namespace utilities
{

/**
  * Create the folder passed as parameter.
  * @param path
  * @return
  */
bool create_folder(const string path);

/**
  * Remove and create the output folder of files .dot and .png.
  * @param path
  * @return
  */
bool clean_output_folder(const string path);

/**
  * Copies the static file to the generation path.
  * @param path
  * @return
  */
bool copy_static_code(const string path_d, const string path_s);

/**
  * Generates the names of vertex. (The vertex's name is an instance).
  * @param graph
  * @param datas
  * @param size_d
  */
void generate_names_instance(const Graph &graph, string datas[], size_t size_d);

/**
  * Generates the names of vertex for down graph. (The vertex's name is an attribute).
  * @param graph
  * @param datas
  * @param size_d
  */
void generate_names_attr(const Graph &graph, string datas[], size_t size_d);

/**
  * Prints a graph in a file .dot for generate image .spng.
  * @param graph
  * @param path
  * @param name_file
  * @param name_graph
  * @param names
  * @param shape_vertex
  */
void print_graph(const Graph &graph,const string path ,const string name_file, const string name_graph, const string names[], string shape_vertex);
/**
  * Prints a graph in the standart output (std:cout).
  * @param graph
  */
void print_graph_txt(const Graph &graph);

/**
  * Given a graph and node, returns the vertex descriptor of node in the graph.
  * If not search it, so returns USHRT_MAX.
  * @param graph
  * @param node
  * @return
  */
Vertex return_vertex(const Graph &graph,const Expr_leaf *node);

/**
  * Joins graph1 and graph2 in graph_merged.
  * @param graph1
  * @param graph2
  * @param graph_merged
  */
void merge_graph(const Graph &graph1, const Graph &graph2, Graph &graph_merged);

/**
  * Projects a graph with only vertex that belongs to symbol "symb".
  * Modifies the parameter "graph".
  * @param symb
  * @param graph
  */
void project_graph(const Symbol *symb, Graph &graph);

/**
  * Remove tabs and replace for spaces.
  * @param str
  * @return
  */
string cleaning_tabs(const string str);

/**
 * Writes inferior contex in a string and returns it.
 * @param context_vec
 * @return
 */
string write_inf_context(const vector<unsigned short> &context_vec);
/**
 * Seachs a index in a vector.
 * @param index
 * @param vec
 * @return
 */
bool belong_index(const unsigned short &index, const vector<unsigned short> &vec);

} /* end utilities */

#endif /* UTILITIES_H_ */
