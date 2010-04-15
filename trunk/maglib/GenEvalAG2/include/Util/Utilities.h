/**
  * \file Utilities.h
  * 	\brief EXPLICAR QUE ES ESTO
  *  \date 09/03/2010
  *  \author    Kilmurray, Gerardo Luis. 
  *  \author    Picco, Gonzalo M. 
  */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>

#include "../Ast/Ast_leaf.h"
#include "../Attr_grammar/Symbol.h"
#include "../Builders/Builder_graphs.h"

using namespace std;

using namespace genevalmag;

namespace utilities
{

/**
  * Create the folder passed as parameter.
  */
bool create_folder(const string path);

/**
  * Remove and create the output folder of files .dot and .png.
  */
bool clean_output_folder(const string path);

/**
  * Copies the static file to the generation path.
  */
bool copy_static_code(const string path);

/**
  * Generates the names of vertex. (The vertex's name is an instance).
  */
void generate_names_instance(const Graph &graph, string datas[], size_t size_d);

/**
  * Generates the names of vertex for down graph. (The vertex's name is an attribute).
  */
void generate_names_attr(const Graph &graph, string datas[], size_t size_d);

/**
  * Prints a graph in a file .dot for generate image .spng.
  */
void print_graph(const Graph &graph,const string path ,const string name_file, const string name_graph, const string names[], string shape_vertex);
/**
  * Prints a graph in the standart output (std:cout).
  */
void print_graph_txt(const Graph &graph);

/**
  * Given a graph and node, returns the vertex descriptor of node in the graph.
  * If not search it, so returns USHRT_MAX.
  */
Vertex return_vertex(const Graph &graph,const Ast_leaf *node);

/**
  * Joins graph1 and graph2 in graph_merged.
  */
void merge_graph(const Graph &graph1, const Graph &graph2, Graph &graph_merged);

/**
  * Projects a graph with only vertex that belongs to symbol "symb".
  * Modifies the parameter "graph".
  */
void project_graph(const Symbol *symb, Graph &graph);


/**
  * Remove tabs and replace for spaces.
  */
string cleaning_tabs(const string str);

string write_inf_context(const vector<unsigned short> &context_vec);

bool belong_index(const unsigned short &index, const vector<unsigned short> &vec);

template < class T > bool belong_elem(const T &elem, const vector<T> &vec);


} /* end utilities */

#endif /* UTILITIES_H_ */
