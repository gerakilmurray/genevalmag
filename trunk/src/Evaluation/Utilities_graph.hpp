/**
  *  \file		Utilities_graph.hpp
  *  \brief
  *  \date		08/03/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef UTILITIES_GRAPH_HPP_
#define UTILITIES_GRAPH_HPP_

#include <fstream>

#include <boost/graph/graphviz.hpp>

using namespace std;
using namespace boost;

namespace genevalmag
{

const string PATH_OUTPUT_FILE ("./src/out_graph/");
const string FILE_DP_GRAPH ("_dp_graph");
const string FILE_DOWN_GRAPH ("_down_graph");
const string FILE_DCG_GRAPH ("_dcg_graph");
const string FILE_ADP_GRAPH ("_adp_graph");
const string FILE_ADP_SUBGRAPH_CYCLIC ("_adp_subgraph_with_cyclic");

/**
  * Remove and create the output folder of files .dot and .png.
  */
void clean_output_folder()
{
	/* Remove the folder. */
	string command_rm_folder("rm -f -r ");
	command_rm_folder.append(PATH_OUTPUT_FILE);
	if (system (command_rm_folder.c_str()) != 0)
	{
		cerr << "ERROR: the filesystem denies folder's remove." << endl;
	}
	/* Create folder. */
	string command_mkdir_folder("mkdir -p ");
	command_mkdir_folder.append(PATH_OUTPUT_FILE);
	if (system (command_mkdir_folder.c_str()) != 0)
	{
		cerr << "ERROR: the filesystem denies folder's creation." << endl;
	}
}

/**
  * Generates the names of vertex. (The vertex's name is an instance).
  */
void generate_names_instance(const Dp_graph &graph, string datas[], size_t size_d)
{
	property_map<Dp_graph, vertex_data_t>::const_type props(get(vertex_data_t(), graph));

	for(size_t i(0); i < size_d; i++)
	{
		datas[i] = props[i]->to_string();
	}
}

/**
  * Generates the names of vertex for down graph. (The vertex's name is an attribute).
  */
void generate_names_attr(const Dp_graph &graph, string datas[], size_t size_d)
{
	property_map<Dp_graph, vertex_data_t>::const_type props(get(vertex_data_t(), graph));

	for(size_t i(0); i < size_d; i++)
	{
		/* The vertexs in a Down graph are ONLY Ast_instance. */
		datas[i] = ((Ast_instance*)props[i])->get_attr()->get_name();

	}
}

/**
  * Prints a graph in a file .dot for generate image .spng.
  */
void print_graph(const Dp_graph &graph, const string name_file, const string name_graph, const string names[])
{
	static int num_file(0); /* For name of file png. */

	/* Create file dot. */
	string n_f(PATH_OUTPUT_FILE);

	stringstream ins;
	ins << ++num_file;
	n_f.append(ins.str());

	n_f.append(name_file);

	n_f.append(".dot");

	/* Obtain of file of graphviz. */
	std::ofstream salida(n_f.c_str());
	std::map<std::string,std::string> graph_attr, vertex_attr, edge_attr;
	/*graph_attr["size"]		= "5,3"; */
	graph_attr["label"]			= name_graph;
	graph_attr["rankdir"]		= "LR";
	graph_attr["ratio"]			= "compress";
	vertex_attr["shape"]		= "ellipse";
	vertex_attr["color"] 		= "black";
	vertex_attr["style"] 		= "filled";
	vertex_attr["fillcolor"]	= "gray";

	write_graphviz(salida, graph, make_label_writer(names),default_writer(),make_graph_attributes_writer(graph_attr, vertex_attr,edge_attr));

	/* Convert file to png. */
	string command("dot ");
	command.append(n_f);
	command.append(" -Tpng -o ");
	command.append(n_f);
	command.append(".png");
	if (system (command.c_str()) != 0 )
	{
		cerr << "ERROR: DOT program can not generate the PNG image." << endl;
	}
}
/**
  * Prints a graph in the standart output (std:cout).
  */
void print_graph_txt(const Dp_graph &graph)
{
	size_t count_vertex(num_vertices(graph));
	cout << "<< Vertex >> " << count_vertex << endl;
	/* Arrays of node's name. */
	property_map<Dp_graph, vertex_data_t>::const_type props(get(vertex_data_t(), graph));
	for(size_t i(0); i < count_vertex; i++)
	{
		cout << props[i]->to_string() << endl;;
	}
	cout << "<< Edges >> " << num_edges(graph) << endl;
	graph_traits<Dp_graph>::edge_iterator ei, ei_end;
	for(tie(ei,ei_end) = edges(graph); ei != ei_end; ++ei)
	{
		Dp_graph::vertex_descriptor source_vertex(source(*ei, graph));
		Dp_graph::vertex_descriptor target_vertex(target(*ei, graph));

		cout << props[source_vertex]->to_string() << "---->" << props[target_vertex]->to_string() << endl;
	}
}

/**
  * Given a graph and node, returns the vertex descriptor of node in the graph.
  * If not search it, so returns USHRT_MAX.
  */
Dp_graph::vertex_descriptor return_vertex(const Dp_graph &graph,const Ast_leaf *node)
{
	property_map<Dp_graph, vertex_data_t>::const_type props(get(vertex_data_t(), graph));
	for(size_t i(0); i < num_vertices(graph); i++)
	{
		if (node->equals(props[i]))
			return i;
	}
	return USHRT_MAX;
}

} /* end genevalmag */

#endif
