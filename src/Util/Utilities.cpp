/**
  *  \file		Utilities.hpp
  *  \brief
  *  \date		08/03/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */
#include <fstream>

#include <boost/graph/graphviz.hpp>
#include <boost/graph/transitive_closure.hpp>

#include "Utilities.h"

using namespace boost;
using namespace genevalmag;

namespace utilities
{

/**
  * Create the folder passed as parameter.
  */
void create_folder(const string path)
{
	/* Create folder. */
	string command_mkdir_folder("mkdir -p ");
	command_mkdir_folder.append(path);
	if (system (command_mkdir_folder.c_str()) != 0)
	{
		cerr << "ERROR: the filesystem denies folder's creation." << endl;
	}
}

/**
  * Remove and create the output folder of files .dot and .png.
  */
void clean_output_folder(const string path)
{
	/* Remove the folder. */
	string command_rm_folder("rm -f -r ");
	command_rm_folder.append(path);
	if (system (command_rm_folder.c_str()) != 0)
	{
		cerr << "ERROR: the filesystem denies folder's remove." << endl;
	}
	/* Create folder. */
	create_folder(path);
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
void print_graph(const Dp_graph &graph, const string path, const string name_file, const string name_graph, const string names[], string shape_vertex)
{
	static int num_file(0); /* For name of file png. */

	/* Create file dot. */
	string n_f(path);
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
	graph_attr["rankdir"]		= "TD";
	graph_attr["ratio"]			= "compress";
	vertex_attr["shape"]		= shape_vertex;
	vertex_attr["color"] 		= "black";
	vertex_attr["style"] 		= "rounded,filled";
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
		Vertex source_vertex(source(*ei, graph));
		Vertex target_vertex(target(*ei, graph));

		cout << props[source_vertex]->to_string() << "---->" << props[target_vertex]->to_string() << endl;
	}
}

/**
  * Given a graph and node, returns the vertex descriptor of node in the graph.
  * If not search it, so returns USHRT_MAX.
  */
Vertex return_vertex(const Dp_graph &graph, const Ast_leaf *node)
{
	property_map<Dp_graph, vertex_data_t>::const_type props(get(vertex_data_t(), graph));
	for(size_t i(0); i < num_vertices(graph); i++)
	{
		if (node->equals(props[i]))
			return i;
	}
	return USHRT_MAX;
}

/**
  * Joins graph1 and graph2 in graph_merged.
  */
void merge_graph(const Dp_graph &graph1, const Dp_graph &graph2, Dp_graph &graph_merged)
{
	/* Cleans the result graph. */
	graph_merged.clear();

	/* Copies the graph1 to result graph. */
	graph_merged = graph1;

	/* Join the graph2 to result graph. */
	property_map<Dp_graph, vertex_data_t>::const_type props(get(vertex_data_t(), graph2));
	property_map<Dp_graph, vertex_data_t>::type props_merged(get(vertex_data_t(), graph_merged));
	/* Circle for vertices. */
	for(size_t i(0); i < num_vertices(graph2); i++)
	{
		Vertex vertex(return_vertex(graph_merged,props[i]));
		if (vertex == USHRT_MAX)
		{
			/* The vertex is new in the graph. */
			vertex = add_vertex(graph_merged);
			put(props_merged,vertex,props[i]);
		}
	}
	/* Cicle for edges. */
	graph_traits<Dp_graph>::edge_iterator ei, ei_end;
	for (tie(ei,ei_end) = edges(graph2); ei != ei_end; ++ei)
	{
		Vertex source_vertex(source(*ei, graph2));
		Vertex target_vertex(target(*ei, graph2));

		Vertex desc_source(return_vertex(graph_merged,props[source_vertex]));
		Vertex desc_target(return_vertex(graph_merged,props[target_vertex]));

		add_edge(desc_source,desc_target,graph_merged);
	}
}

/**
  * Projects a graph with only vertex that belongs to symbol "symb".
  * Modifies the parameter "graph".
  */
void project_graph(const Symbol *symb, Dp_graph &graph)
{
	/* Applies transitivity to graph with only nodes of symb. */
	warshall_transitive_closure(graph);

	property_map<Dp_graph, vertex_data_t>::type props(get(vertex_data_t(), graph));
	/* Reduces the graph for symbol "symb". */
	for (size_t i(num_vertices(graph)); i > 0; i--)
	{
		const Ast_instance *ins(dynamic_cast<const Ast_instance*>(props[i-1]));
		if (!ins || !ins->get_symb()->equals(*symb))
		/* The node is a literal-node or is a node with symbol diferent that symb. */
		{
			clear_vertex(i-1, graph);
			remove_vertex(i-1, graph);
		}
	}
}

/**
  * Remove tabs and replace for spaces.
  */
string cleaning_tabs(const string str)
{
	string aux("");
	for(int i=0; str[i] != '\0'; i++)
	{
		aux.push_back((str[i] == '\t')? ' ': str[i]);
	}
	return aux;
}

string write_inf_context(const vector<unsigned short> &context_vec)
{
	string context;
	if (context_vec.size() == 1)
	{
		context.append(" hasn't an inferior context");
	}
	else
	{
		context.append(" with inferior context: ");
		for(size_t i(1); i < context_vec.size(); i++)
		{
			context.append(" R");
			stringstream key_rule;
			key_rule << context_vec[i];
			context.append(key_rule.str());
			if(i < context_vec.size() - 1)
			{
				context.append(" ,");
			}
		}
	}
	return context;
}

} /* end utilities */
