/**
  *  \file		DC_graph.cpp
  *  \brief		Implementation of the methods the DC_graph.h
  *  \date		17/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <iostream>                  // for std::cout
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

// create a typedef for the Graph type
/*adjacency_list<OutEdgeList, VertexList, Directed,
               VertexProperties, EdgeProperties,
               GraphProperties, EdgeList>*/


typedef int vertex_data_t;
typedef adjacency_list<listS, vecS, directedS, property<vertex_data_t, const genevalmag::Ast_leaf*> > Dp_graph;

// Store the down graphs. The key corresponds to the key Symbol.
//map <string,Graph> p_Down_graphs;

// Store the DP graphs. The key corresponds to the key Rule.
map <string, Dp_graph> p_Dp_graphs;


// Algorithm DP
void compute_dependency_graphs(const map<string, Rule> rules)
{
	// for the rules.
	for(map<string,Rule >::const_iterator it = rules.begin(); it != rules.end(); it++)
	{
		const Rule * rule = &it->second;
		Dp_graph current_p_Dp_graph(1);

		// for the eqs
		for(map<int,Equation >::const_iterator eq = rule->get_eqs().begin(); eq != rule->get_eqs().end(); eq++)
		{
			// insertar instancia left
			Dp_graph::vertex_descriptor v = *vertices(current_p_Dp_graph).first;
//			current_p_Dp_graph[v] = eq->second.get_l_value();

			add_edge(v,v,current_p_Dp_graph);

			std::map<std::string,std::string> graph_attr, vertex_attr, edge_attr;
			graph_attr["size"] = "3,3";
			graph_attr["rankdir"] = "LR";
			graph_attr["ratio"] = "fill";
			vertex_attr["shape"] = "circle";

			// por cada instancia y literales de la right insetar una arista de el al left instancia.
		}

		boost::write_graphviz(std::cout, current_p_Dp_graph);

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
