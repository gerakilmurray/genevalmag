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
//#include <algorithm>                 // for std::for_each
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

struct vertex_data_t
{
    typedef vertex_property_tag kind;
};
typedef property <vertex_data_t, const genevalmag::Ast_leaf*> property_vertex;
typedef adjacency_list<hash_setS, vecS, directedS, property_vertex > Dp_graph;

// Store the down graphs. The key corresponds to the key Symbol.
//map <string,Graph> p_Down_graphs;

// Store the DP graphs. The key corresponds to the key Rule.
map <string, Dp_graph> p_Dp_graphs;


void print_graph(Dp_graph &graph)
{
	static int num_file = 0; // For name of file png
	size_t count_vertex = num_vertices(graph);
	// Arrays of node's name.
	string datas[count_vertex];
	property_map<Dp_graph, vertex_data_t>::type props = get(vertex_data_t(), graph);
	for(size_t i = 0; i < count_vertex; i++)
	{
		datas[i] = props[i]->to_string();
	}

	// Create folder
	string command_folder = "mkdir -p ";
	command_folder.append(PATH_OUTPUT_FILE);
	system ( command_folder.c_str());

	// Create file dot.
	string n_f = PATH_OUTPUT_FILE;
	n_f.append("/dp_graph_");
	stringstream ins;
	ins << ++num_file;
	n_f.append(ins.str());
	n_f.append(".dot");

	// Obtain of file of graphviz.
	ofstream salida(n_f.c_str());
	write_graphviz(salida, graph, make_label_writer(datas));

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

Dp_graph::vertex_descriptor return_vertex(Dp_graph graph,const Ast_node * node)
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
void compute_dependency_graphs(const map<string, Rule> rules)
{
	// for the rules.
	for(map<string,Rule >::const_iterator it = rules.begin(); it != rules.end(); it++)
	{
		const Rule * rule = &it->second;
		Dp_graph current_p_Dp_graph;

		// for the eqs
		for(map<int,Equation >::const_iterator eq = rule->get_eqs().begin(); eq != rule->get_eqs().end(); eq++)
		{
			// insertar instancia left
			vector<const Ast_leaf*> elem_leaf_tree;
			eq->second.inner_order_only_leaf(eq->second.get_r_value(), elem_leaf_tree);

			Dp_graph::vertex_descriptor l_v = return_vertex(current_p_Dp_graph, eq->second.get_l_value());
			if (l_v == USHRT_MAX)
			{
				l_v = add_vertex(current_p_Dp_graph);
				property_map<Dp_graph, vertex_data_t>::type leafs = get(vertex_data_t(), current_p_Dp_graph);
				put(leafs,l_v,eq->second.get_l_value());
			}

			for(size_t i=0; i< elem_leaf_tree.size(); i++)
			{
				Dp_graph::vertex_descriptor r_v = return_vertex(current_p_Dp_graph,elem_leaf_tree[i]);
				if (r_v == USHRT_MAX)
				{
					r_v = add_vertex(current_p_Dp_graph);
					property_map<Dp_graph, vertex_data_t>::type leafs = get(vertex_data_t(), current_p_Dp_graph);
					put(leafs,r_v,elem_leaf_tree[i]);

				}
				add_edge(r_v,l_v,current_p_Dp_graph);
			}
			// por cada instancia y literales de la right insetar una arista de el al left instancia.
		}

		print_graph(current_p_Dp_graph);

		pair<string, Dp_graph > new_p(rule->key(), current_p_Dp_graph);
		pair<map<string, Dp_graph >::iterator, bool > result = p_Dp_graphs.insert(new_p);
	}
}

// Algorithm Down
void compute_down_graph(Symbol *symb)
{

}

// Algorithm DCG
void compute_dcg(Rule *rule, Symbol *symb)
{

}

// Algorithm ADP
void compute_adp_graph(Rule *rule)
{


}
