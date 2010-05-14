/**
  *  \file		Builder_graphs.h
  *  \brief		Header with the functions for build graph of grammar.
  *  \date		17/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#ifndef BUILDER_GRAPHS_H_
#define BUILDER_GRAPHS_H_

#include <map>
#include <string>
#include <vector>

#include <boost/graph/adjacency_list.hpp>

#include "../Attr_grammar/Rule.h"
#include "../Attr_grammar/Symbol.h"
#include "../Attr_grammar/Attr_grammar.h"
#include "../Expression_tree/Expr_leaf.h"

using namespace std;
using namespace boost;

namespace genevalmag
{

struct vertex_data_t
{
    typedef vertex_property_tag kind;
};

typedef property <vertex_data_t, const genevalmag::Expr_leaf*> property_vertex_dp;

typedef adjacency_list<hash_setS, vecS, directedS, property_vertex_dp > Graph;

typedef Graph::vertex_descriptor Vertex;

class Builder_graphs
{
	private:
		/**
		  * \var p_Dp_graphs.
		  * \brief Store the DP graphs. The key corresponds to the key Rule..
		  */
		map <unsigned short, Graph> p_Dp_graphs;
		/**
		  * \var attr_vertex_graphs.
		  * \brief Store the vertex-attr graphs. The key corresponds to the key Symbol.
		  */
		map <string, Graph> attr_vertex_graphs;
		/**
		  * \var p_Down_graphs.
		  * \brief Store the down graphs. The key corresponds to the key Symbol.
		  */
		map <string, Graph> p_Down_graphs;
		/**
		  * \var p_Dcg_graphs.
		  * \brief Store the dcg graphs. The key corresponds to the key Rule.
		  */
		/* Store the dcg graphs. The key corresponds to the key Rule. */
		map <unsigned short, Graph> p_Dcg_graphs;
		/**
		  * \var p_Adp_graphs.
		  * \brief Store the adp graphs. The key corresponds to the key Rule with the inferior context.
		  */
		map <vector<unsigned short>, Graph> p_Adp_graphs;
		/**
		  * \var p_Adp_subgraphs_cyclics.
		  * \brief Store the adp graphs. The key corresponds to the key Rule with the inferior context.
		  */
		map <vector<unsigned short>, Graph> p_Adp_subgraphs_cyclics;

		/**
		  * Builds a graph for each symbol of the grammar with all atributes.
		  * The graph only has vertexs. It hasn't edges.
		  * Ex: Symbol E ; attributes: s,i
		  * 	graph: 	vertex: E.s, E.i
		  * @param symbols
		  */
		void compute_attr_vertex(const map<string,Symbol> &symbols);

		/**
		  * Completes dp-graph with the vertex of low on instances.
		  * @param rules
		  */
		void complete_dp_graphs(const map<unsigned short, Rule> &rules);

		/**
		  * Generate all combinations of the rules and saves a graph ADP for each of them.
		  * @param rule
		  * @param graph
		  * @param inf_context
		  * @param index_to_combine
		  * @return
		  */
		bool combined_inf_contexts(const Rule *rule, Graph &graph, vector< vector<unsigned short> > &inf_context, size_t index_to_combine);

	public:

		/**
		  * Constructor empty of Builder graphs.
		  * @return
		  */
		Builder_graphs();

		/**
		  * Destructor empty of Builder graphs.
		  * @return
		  */
		~Builder_graphs();

		/**
		  * Returns the map with all ADP graphs creates.
		  * @return
		  */
		const map<vector<unsigned short>, Graph> &get_adp_graphs() const;

		/**
		  * Returns the map with all ADP with cycle graphs creates.
		  * @return
		  */
		const map<vector<unsigned short>, Graph> &get_cyclic_graphs() const;

		/**
		  * Returns the down graph of the symbol.
		  * @param index_rule
		  * @return
		  */
		const Graph &get_dcg_graph(unsigned short index_rule) const;

		/**
		  * Algorithm DP
		  * Builds a graph dp for each rule of the grammar.
		  * Ex: E:= E + T
		  * 	graph: 	vertex: E,T
		  * 			Edges: 	E --> E
		  * 					T---> E
		  * @param rules
		  * @return
		  */
		bool compute_dependency_graphs(const map<unsigned short,Rule> &rules);

		/**
		  * Algorithm Down
		  * Builds the graphs down for each symbol of the grammar.
		  * Ex: Down(E) :
		  * 	(1) E:= E + T.
		  * 	graph G: DP(1) U Down(E) U Down(T)
		  * 	Project(G,{attributes of E})
		  * @param symbols
		  * @param rules
		  * @return
		  */
		bool compute_down_graph(const map<string, Symbol> &symbols, const map<unsigned short, Rule> &rules);

		/**
		  * Algorithm DCG
		  * Builds the graph Dcg for each rule of the grammar.
		  * Ex: Dcg E(1) :
		  * 	(1) E:= E + T.
		  * 	graph G: DP(1) U Down(E) U Down(T)
		  * 	Project(G,{attributes of E})
		  * @param rules
		  * @return
		  */
		bool compute_dcg(const map<unsigned short, Rule> &rules);

		/**
		  * Algorithm ADP
		  * Builds the graphs ADP for each rule of the grammar.
		  * Ex: ADP(1):
		  * 	(1) E:= E + T.
		  * 	graph G: DP(1) U Dcg E (J1..JN) U Dcg T (K1..KM)
		  * 	Where Ji y ki are rule with left-symbol E and T respectly.
		  * @param grammar
		  * @return
		  */
		bool compute_adp_graph(const Attr_grammar &grammar);

		/**
		  * Checks if the graph contains cycle.
		  * Utilities a deph-firts-seach for traverse the graphs.
		  * @return
		  */
		bool check_cyclic_adp_dependencies();

		/**
		  * Saves all graphs generates: DP, Down, DCG and ADP.
		  * @param rules
		  * @param path_output
		  * @return
 		  */
		bool save_all_graphs(const map<unsigned short, Rule> &rules, const string path_output) const;

		/**
		  * Saves all graphs graph cycles.
		  * @param rules
		  * @param path_output
		  * @return
		  */
		bool save_cyclic_graphs(const map<unsigned short, Rule> &rules, const string path_output) const;

		/**
		  * Saves all dp-graphs generates
		  * @param rules
		  * @param path_output
		  * @return
		  */
		bool save_dp_graphs(const map<unsigned short, Rule> &rules, const string path_output) const;

		/**
		  * Saves all down-graphs generates
		  * @param path_output
		  * @return
		  */
		bool save_down_graphs(const string path_output) const;

		/**
		  * Saves all dcg-graphs generates
		  * @param rules
		  * @param path_output
		  * @return
		  */
		bool save_dcg_graphs(const map<unsigned short, Rule> &rules, const string path_output) const;

		/**
		  * Saves all adp-graphs generates
		  * @param rules
		  * @param path_output
		  * @return
		  */
		bool save_adp_graphs(const map<unsigned short, Rule> &rules, const string path_output) const;
};

} /* end genevalmag */

#endif /* BUILDER_GRAPHS_H_ */