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
#include <algorithm>                 // for std::for_each
//#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

#include "DC_graph.h"
#include "../Attr_grammar/Symbol.h"
#include "../Attr_grammar/Attr_grammar.h"

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

//typedef property <vertex_data_t, const genevalmag::Attribute*> property_vertex_down;
//typedef adjacency_list<hash_setS, vecS, directedS, property_vertex_down > Ds_graph;

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
	system ( command_folder.c_str());

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
	if (system ( command.c_str() ) == 0 )
		cout << "OK, creado los archivos de salida" << endl;
	else
		cout << "<<<<Fail>>>> Archivos mal creados" << endl;
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
				//property_map<Dp_graph, vertex_data_t>::type leafs = get(vertex_data_t(), *current_p_Dp_graph);

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
					//property_map<Dp_graph, vertex_data_t>::type leafs = get(vertex_data_t(), *current_p_Dp_graph);

					put(leafs,r_v,elem_leaf_tree[i]);

				}
				// Add edge between left instance and right instance. r_v --> l_v.
				add_edge(r_v,l_v,current_p_Dp_graph);
			}
		}

		// Print current graph
		//print_graph<Dp_graph>(current_p_Dp_graph,FILE_DP_GRAPH,rule->to_string_not_eqs());

		// Insert current graph in map of denpendency graph.
		pair<string, Dp_graph > new_p(rule->to_string_not_eqs(), current_p_Dp_graph);
		pair<map<string, Dp_graph >::iterator, bool > result = p_Dp_graphs.insert(new_p);
		current_p_Dp_graph.clear();
//		current_p_Dp_graph = NULL;

	}
//		for(map <string,Dp_graph>::iterator it = p_Dp_graphs.begin(); it != p_Dp_graphs.end(); it++)
//		{
//			print_graph<Dp_graph>(it->second,FILE_DP_GRAPH,it->first);
//		}

}

// Algorithm Down
void compute_down_graph(const map<string,Symbol> symbols)
{
	Dp_graph current_p_Down_graph;
	// for the dp_graph
	for(map<string,Symbol >::const_iterator it = symbols.begin(); it != symbols.end(); it++)
	{
		const Symbol * symb = &it->second;

		for(map<string,Dp_graph >::iterator dp = p_Dp_graphs.begin(); dp != p_Dp_graphs.end(); dp++)
		{
			property_map<Dp_graph, vertex_data_t>::type props = get(vertex_data_t(), dp->second);
			for(size_t i = 0; i < num_vertices(dp->second); i++)
			{
				const Ast_instance * instance = dynamic_cast<const Ast_instance*>(props[i]);
				if (instance)
				{
					if (instance->get_symb()->equals(*symb))
					{
						Dp_graph::vertex_descriptor ins = return_vertex(current_p_Down_graph,instance);
						if (ins == USHRT_MAX)
						{
							// The vertex is new in the graph.
							ins = add_vertex(current_p_Down_graph);
							property_map<Dp_graph, vertex_data_t>::type nodes = get(vertex_data_t(), current_p_Down_graph);
							put(nodes,ins,props[i]);
						}
					}
				}
			}

			graph_traits<Dp_graph>::edge_iterator ei, ei_end;
			for (tie(ei,ei_end) = edges(dp->second); ei != ei_end; ++ei)
			{
				Dp_graph::vertex_descriptor s = source(*ei, dp->second);
				Dp_graph::vertex_descriptor t = target(*ei, dp->second);
				const Ast_instance * ins_source = dynamic_cast<const Ast_instance*>(props[s]);
				const Ast_instance * ins_target = dynamic_cast<const Ast_instance*>(props[t]);
				if (ins_source && ins_target)
				{
					if(ins_source->get_symb()->equals(*ins_target->get_symb()))
					{
						if(!ins_source->get_attr()->equals(*ins_target->get_attr()))
						{
							cout << "rule" << dp->first << endl;
							cout << ins_source->to_string() << ins_target->to_string() << "aca ta" << endl;
						}
						else
						{
							cout << "CICLOOOOOOOO" << endl;
						}
					}
				}
			}
		}

//		print_graph<Dp_graph>(current_p_Down_graph,FILE_DOWN_GRAPH,symb->get_name());
		// Insert current graph in map of down graph
		pair<string, Dp_graph > new_p(symb->key(), current_p_Down_graph);
		pair<map<string, Dp_graph >::iterator, bool > result = p_Down_graphs.insert(new_p);
		current_p_Down_graph.clear();
	}


}

// Algorithm DCG
void compute_dcg()
{
	for(map <string,Dp_graph>::iterator it = p_Dp_graphs.begin(); it != p_Dp_graphs.end(); it++)
	{
		print_graph<Dp_graph>(it->second,FILE_DP_GRAPH,it->first);

	}

	for(map <string,Dp_graph>::iterator it = p_Down_graphs.begin(); it != p_Down_graphs.end(); it++)
	{
		print_graph<Dp_graph>(it->second,FILE_DOWN_GRAPH,it->first);
	}


}

// Algorithm ADP
void compute_adp_graph(Rule *rule)
{


}
