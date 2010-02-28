/**
  *  \file		DC_graph.cpp
  *  \brief		Implementation of the methods the DC_graph.h
  *  \date		17/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>                  // for std::cout
#include <fstream>
#include <utility>                   // for std::pair
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/transitive_closure.hpp>

#include "DC_graph.h"
#include "../Attr_grammar/Symbol.h"
#include "../Attr_grammar/Attr_grammar.h"
#include "../Parser/Semantics_actions.h"

using namespace boost;
using namespace std;
using namespace genevalmag;

#define PATH_OUTPUT_FILE "./src/out_graph"
#define FILE_DP_GRAPH "/dp_graph_"
#define FILE_DOWN_GRAPH "/down_graph_"

struct vertex_data_t
{
    typedef vertex_property_tag kind;
};

typedef property <vertex_data_t, const genevalmag::Ast_leaf*> property_vertex_dp;
typedef adjacency_list<hash_setS, vecS, directedS, property_vertex_dp > Dp_graph;

// Store the DP graphs. The key corresponds to the key Rule.
map <string, Dp_graph> p_Dp_graphs;

// Store the down graphs. The key corresponds to the key Symbol.
map <string, Dp_graph> p_Down_graphs;

template <class Type_graph>
void print_graph(Type_graph &graph, string name_file,string name_graph)
{
	static int num_file = 0; // For name of file png
	size_t count_vertex = num_vertices(graph);
	// Arrays of node's name.
	string datas[count_vertex];
	typename property_map<Type_graph, vertex_data_t>::type props = get(vertex_data_t(), graph);
	for(size_t i = 0; i < count_vertex; i++)
	{
		datas[i] = props[i]->value_s();
	}

	// Create folder
	string command_folder = "mkdir -p ";
	command_folder.append(PATH_OUTPUT_FILE);
	if (system (command_folder.c_str()) != 0)
	{
		cerr << "ERROR: the filesystem denies folder's creation." << endl;
	}

	// Create file dot.
	string n_f = PATH_OUTPUT_FILE;
	n_f.append(name_file);
	stringstream ins;
	ins << ++num_file;
	n_f.append(ins.str());
	n_f.append(".dot");

	// Obtain of file of graphviz.
	ofstream salida(n_f.c_str());
	std::map<std::string,std::string> graph_attr, vertex_attr, edge_attr;
	//graph_attr["size"] = "5,5";
	graph_attr["label"] = name_graph;
	graph_attr["rankdir"] = "LR";
	graph_attr["ratio"] = "compress";
	vertex_attr["shape"] = "ellipse";
	vertex_attr["color"] = "black";
	vertex_attr["style"] = "filled";
	vertex_attr["fillcolor"] = "gray";

	write_graphviz(salida, graph, make_label_writer(datas),default_writer(),make_graph_attributes_writer(graph_attr, vertex_attr,edge_attr));

	// Convert file to png
	string command = "dot " ;
	command.append(n_f);
	command.append( " -Tpng -o ");
	command.append(n_f);
	command.append(".png");
	if (system (command.c_str()) != 0 )
	{
		cerr << "ERROR: DOT program can not generate the PNG image." << endl;
	}
}

void print_graph_txt(Dp_graph &graph)
{
	size_t count_vertex = num_vertices(graph);
	cout << "<< Vertex >> " << num_vertices(graph) << endl;
	// Arrays of node's name.
	property_map<Dp_graph, vertex_data_t>::type props = get(vertex_data_t(), graph);
	for(size_t i = 0; i < count_vertex; i++)
	{
		cout << props[i]->value_s() << endl;;
	}
	cout << "<< Edges >> " << num_edges(graph) << endl;
	graph_traits<Dp_graph>::edge_iterator ei, ei_end;
	for (tie(ei,ei_end) = edges(graph); ei != ei_end; ++ei)
	{
		Dp_graph::vertex_descriptor source_vertex = source(*ei, graph);
		Dp_graph::vertex_descriptor target_vertex = target(*ei, graph);

		cout << props[source_vertex]->value_s() << "---->" << props[target_vertex]->value_s() << endl;
	}
}


Dp_graph::vertex_descriptor return_vertex(Dp_graph graph,const Ast_leaf * node)
{
	property_map<Dp_graph, vertex_data_t>::type props = get(vertex_data_t(), graph);
	for(size_t i = 0; i < num_vertices(graph); i++)
	{
		if (node->equals(props[i]))
			return i;
	}
	return USHRT_MAX;
}

// Algorithm DP
void compute_dependency_graphs(const map<string, Rule> &rules)
{
	Dp_graph current_p_Dp_graph;
	property_map<Dp_graph, vertex_data_t>::type leafs = get(vertex_data_t(), current_p_Dp_graph);

	// for the rules.
	for(map<string,Rule>::const_iterator it = rules.begin(); it != rules.end(); it++)
	{
		const Rule * rule = &it->second;
		// for the eqs
		for(map<int,Equation>::const_iterator eq = rule->get_eqs().begin(); eq != rule->get_eqs().end(); eq++)
		// For each instance build a new edge entre left instance and rigth instance.
		{
			// Insert left instance.
			vector<const Ast_leaf*> elem_leaf_tree;
			eq->second.inner_order_only_leaf(eq->second.get_r_value(), elem_leaf_tree);

			// Verify if vertex belong at graph.
			Dp_graph::vertex_descriptor l_v = return_vertex(current_p_Dp_graph, eq->second.get_l_value());
			if (l_v == USHRT_MAX)
			{
				// The vertex is new in the graph.
				l_v = add_vertex(current_p_Dp_graph);

				put(leafs, l_v, eq->second.get_l_value());
			}
			// for the right side of equation.
			for(size_t i=0; i< elem_leaf_tree.size(); i++)
			{
				// Verify if vertex belong at graph.
				Dp_graph::vertex_descriptor r_v = return_vertex(current_p_Dp_graph,elem_leaf_tree[i]);
				if (r_v == USHRT_MAX)
				{
					// The vertex is new in the graph.
					r_v = add_vertex(current_p_Dp_graph);
					put(leafs,r_v,elem_leaf_tree[i]);

				}
				// Add edge between left instance and right instance. r_v --> l_v.
				add_edge(r_v,l_v,current_p_Dp_graph);
			}
		}

		// Print current graph
//		print_graph_txt(current_p_Dp_graph);
//		print_graph<Dp_graph>(current_p_Dp_graph,FILE_DP_GRAPH,rule->to_string_not_eqs());

		// Insert current graph in map of denpendency graph.
		pair<string, Dp_graph > new_p(rule->key(), current_p_Dp_graph);
		pair<map<string, Dp_graph >::iterator, bool > result = p_Dp_graphs.insert(new_p);
		current_p_Dp_graph.clear();
	}
}

void merge_graph(Dp_graph &graph1, Dp_graph &graph2, Dp_graph &graph_merged)
{
	graph_merged.clear();
	graph_merged = graph1;

	property_map<Dp_graph, vertex_data_t>::type props = get(vertex_data_t(), graph2);
	property_map<Dp_graph, vertex_data_t>::type props_merged = get(vertex_data_t(), graph_merged);
	for(size_t i = 0; i < num_vertices(graph2); i++)
	{
		Dp_graph::vertex_descriptor vertex = return_vertex(graph_merged,props[i]);
		if (vertex == USHRT_MAX)
		{
			// The vertex is new in the graph.
			vertex = add_vertex(graph_merged);
			put(props_merged,vertex,props[i]);
		}
	}

	graph_traits<Dp_graph>::edge_iterator ei, ei_end;
	for (tie(ei,ei_end) = edges(graph2); ei != ei_end; ++ei)
	{
		Dp_graph::vertex_descriptor source_vertex = source(*ei, graph2);
		Dp_graph::vertex_descriptor target_vertex = target(*ei, graph2);

		Dp_graph::vertex_descriptor desc_source = return_vertex(graph_merged,props[source_vertex]);
		Dp_graph::vertex_descriptor desc_target = return_vertex(graph_merged,props[target_vertex]);

		add_edge(desc_source,desc_target,graph_merged);
	}
}

void project_graph(const Symbol * symb, Dp_graph &graph)
{
//	transitive_closure(graph,graph_projected,vertex_index_map(identity_property_map()));

	property_map<Dp_graph, vertex_data_t>::type props = get(vertex_data_t(), graph);
	for (size_t i = num_vertices(graph); i > 0; i--)
	{
		const Ast_instance *ins = dynamic_cast<const Ast_instance*>(props[i-1]);
		if (!ins || !ins->get_symb()->equals(*symb))
		{
			clear_vertex(i-1, graph);
			remove_vertex(i-1, graph);
		}
	}
	warshall_transitive_closure(graph);
}

// Algorithm Down
void compute_down_graph(const map<string,Symbol> &symbols, const map<string,Rule> &rules)
{
	Dp_graph current_p_Down_graph;
	// for the dp_graph
	for(map<string,Dp_graph >::iterator dp = p_Dp_graphs.begin(); dp != p_Dp_graphs.end(); dp++)
	{
		Dp_graph merged_g;
		merge_graph(dp->second, current_p_Down_graph, merged_g);
		current_p_Down_graph.clear();
		current_p_Down_graph = merged_g;
	}

	for(map<string,Symbol >::const_iterator it = symbols.begin(); it != symbols.end(); it++)
	{
		Dp_graph copy_down_g;

		copy_down_g = current_p_Down_graph;

		const Symbol *symb = &it->second;

		project_graph(symb, copy_down_g);

		// Insert current graph in map of down graph
		pair<string, Dp_graph > new_p(symb->key(), copy_down_g);
		pair<map<string, Dp_graph >::iterator, bool > result = p_Down_graphs.insert(new_p);
	}
}

// Algorithm DCG
void compute_dcg(const map<string, Rule> &rules)
{
	for(map <string,Dp_graph>::iterator it = p_Dp_graphs.begin(); it != p_Dp_graphs.end(); it++)
	{
		const Rule *current_rule = &(rules.find(it->first)->second);
		string name_graph = "Dependency Graph of rule ";
		name_graph.append(cleaning_tabs(current_rule->to_string_not_eqs()));
		print_graph<Dp_graph>(it->second,FILE_DP_GRAPH,name_graph);
	}

	for(map <string,Dp_graph>::iterator it = p_Down_graphs.begin(); it != p_Down_graphs.end(); it++)
	{
		string name_graph = "Graph Down(";
		name_graph.append(it->first);
		name_graph.append(")");
		print_graph<Dp_graph>(it->second,FILE_DOWN_GRAPH,name_graph);
	}
}

// Algorithm ADP
void compute_adp_graph(Rule *rule)
{

}
