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
#include "../Evaluation/Builder_graphs.h"

using namespace std;

using namespace genevalmag;

namespace utilities
{

/**
  * Remove and create the output folder of files .dot and .png.
  */
void clean_output_folder();

/**
  * Generates the names of vertex. (The vertex's name is an instance).
  */
void generate_names_instance(const Dp_graph &graph, string datas[], size_t size_d);

/**
  * Generates the names of vertex for down graph. (The vertex's name is an attribute).
  */
void generate_names_attr(const Dp_graph &graph, string datas[], size_t size_d);

/**
  * Prints a graph in a file .dot for generate image .spng.
  */
void print_graph(const Dp_graph &graph, const string name_file, const string name_graph, const string names[], string shape_vertex);
/**
  * Prints a graph in the standart output (std:cout).
  */
void print_graph_txt(const Dp_graph &graph);

/**
  * Given a graph and node, returns the vertex descriptor of node in the graph.
  * If not search it, so returns USHRT_MAX.
  */
Dp_graph::vertex_descriptor return_vertex(const Dp_graph &graph,const Ast_leaf *node);

/**
  * Joins graph1 and graph2 in graph_merged.
  */
void merge_graph(const Dp_graph &graph1, const Dp_graph &graph2, Dp_graph &graph_merged);

/**
  * Projects a graph with only vertex that belongs to symbol "symb".
  * Modifies the parameter "graph".
  */
void project_graph(const Symbol *symb, Dp_graph &graph);


/**
  * Remove tabs and replace for spaces.
  */
string cleaning_tabs(const string str);

string write_inf_context(const vector<unsigned short> &context_vec);

} /* end utilities */

#endif /* UTILITIES_H_ */
