/**
  *  \file		Builder_graphs.h
  *  \brief		Header with the functions for evaluation of AG.
  *  \date		17/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef BUILDER_GRAPHS_H_
#define BUILDER_GRAPHS_H_

#include <map>
#include <string>

#include <boost/graph/adjacency_list.hpp>

#include "../Attr_grammar/Rule.h"
#include "../Attr_grammar/Symbol.h"
#include "../Attr_grammar/Attr_grammar.h"

using namespace boost;
namespace genevalmag
{

struct vertex_data_t
{
    typedef vertex_property_tag kind;
};

typedef property <vertex_data_t, const genevalmag::Ast_leaf*> property_vertex_dp;

typedef adjacency_list<hash_setS, vecS, directedS, property_vertex_dp > Dp_graph;

class Builder_graphs
{
	private:
		// Store the DP graphs. The key corresponds to the key Rule.
		map <unsigned short, Dp_graph> p_Dp_graphs;

		// Store the vertex-attr graphs. The key corresponds to the key Symbol.
		map <string, Dp_graph> attr_vertex_graphs;

		// Store the down graphs. The key corresponds to the key Symbol.
		map <string, Dp_graph> p_Down_graphs;

		// Store the dcg graphs. The key corresponds to the key Rule.
		map <unsigned short, Dp_graph> p_Dcg_graphs;

		// Store the adp graphs. The key corresponds to the key Rule.
		map <vector<unsigned short>, Dp_graph> p_Adp_graphs;


		/**
		  * Projects a graph with only vertex that belongs to symbol "symb".
		  * Modifies the parameter "graph".
		  */
		void project_graph(const Symbol * symb, Dp_graph &graph);

		/**
		  * Builds a graph for each symbol of the grammar with all atributes.
		  * The graph only has vertexs. It hasn't edges.
		  * Ex: Symbol E ; attributes: s,i
		  * 	graph: 	vertex: E.s, E.i
		  */
		void compute_attr_vertex(const map<string,Symbol> &symbols);

		void combined_inf_contexts(const Rule* rule, Dp_graph &graph, vector< vector<const Rule*> > &inf_context, size_t index_to_combine);

	public:

		Builder_graphs();

		~Builder_graphs();

		void compute_dependency_graphs(const map<unsigned short, Rule> &rules);

		void compute_down_graph(const map<string, Symbol> &symbols, const map<unsigned short, Rule> &rules);

		void compute_dcg(const map<unsigned short, Rule> &rules);

		void compute_adp_graph(const Attr_grammar &grammar);

		void print_all_graphs(const map<unsigned short, Rule> &rules);
};

} // end genevalmag

#endif /* BUILDER_GRAPHS_H_ */
