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
#include <vector>

#include <boost/graph/adjacency_list.hpp>

#include "../Attr_grammar/Rule.h"
#include "../Attr_grammar/Symbol.h"
#include "../Attr_grammar/Attr_grammar.h"
#include "../Ast/Ast_leaf.h"

using namespace std;
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
		/* Store the DP graphs. The key corresponds to the key Rule. */
		map <unsigned short, Dp_graph> p_Dp_graphs;

		/* Store the vertex-attr graphs. The key corresponds to the key Symbol. */
		map <string, Dp_graph> attr_vertex_graphs;

		/* Store the down graphs. The key corresponds to the key Symbol. */
		map <string, Dp_graph> p_Down_graphs;

		/* Store the dcg graphs. The key corresponds to the key Rule. */
		map <unsigned short, Dp_graph> p_Dcg_graphs;

		/* Store the adp graphs. The key corresponds to the key Rule with the inferior context*/
		map <vector<unsigned short>, Dp_graph> p_Adp_graphs;

		/* Store the adp graphs. The key corresponds to the key Rule with the inferior context*/
		map <vector<unsigned short>, Dp_graph> p_Adp_subgraphs_cyclics;

		/**
		  * Builds a graph for each symbol of the grammar with all atributes.
		  * The graph only has vertexs. It hasn't edges.
		  * Ex: Symbol E ; attributes: s,i
		  * 	graph: 	vertex: E.s, E.i
		  */
		void compute_attr_vertex(const map<string,Symbol> &symbols);

		void complete_dp_graphs(const map<unsigned short, Rule> &rules);

		/**
		  * Generate all combinations of the rules and saves a graph ADP for each of them.
		  */
		void combined_inf_contexts(const Rule *rule, Dp_graph &graph, vector< vector<unsigned short> > &inf_context, size_t index_to_combine);

	public:

		/**
		  * Constructor empty of Builder graphs.
		  */
		Builder_graphs();

		/**
		  * Destructor empty of Builder graphs.
		  */
		~Builder_graphs();

		/**
		  * Returns the map with all ADP graphs creates.
		  */
		const map<vector<unsigned short>, Dp_graph> &get_adp_graphs() const;

		/**
		  * Returns the map with all ADP with cycle graphs creates.
		  */
		const map<vector<unsigned short>, Dp_graph> &get_cyclic_graphs() const;

		/**
		  * Returns the down graph of the symbol.
		  */
		const Dp_graph &get_dcg_graph(unsigned short index_rule) const;

		/**
		  * Algorithm DP
		  * Builds a graph dp for each rule of the grammar.
		  * Ex: E:= E + T
		  * 	graph: 	vertex: E,T
		  * 			Edges: 	E --> E
		  * 					T---> E
		  */
		void compute_dependency_graphs(const map<unsigned short,Rule> &rules);

		/**
		  * Algorithm Down
		  * Builds the graphs down for each symbol of the grammar.
		  * Ex: Down(E) :
		  * 	(1) E:= E + T.
		  * 	graph G: DP(1) U Down(E) U Down(T)
		  * 	Project(G,{attributes of E})
		  */
		void compute_down_graph(const map<string, Symbol> &symbols, const map<unsigned short, Rule> &rules);

		/**
		  * Algorithm DCG
		  * Builds the graph Dcg for each rule of the grammar.
		  * Ex: Dcg E(1) :
		  * 	(1) E:= E + T.
		  * 	graph G: DP(1) U Down(E) U Down(T)
		  * 	Project(G,{attributes of E})
		  */
		void compute_dcg(const map<unsigned short, Rule> &rules);

		/**
		  * Algorithm ADP
		  * Builds the graphs ADP for each rule of the grammar.
		  * Ex: ADP(1):
		  * 	(1) E:= E + T.
		  * 	graph G: DP(1) U Dcg E (J1..JN) U Dcg T (K1..KM)
		  * 	Where Ji y ki are rule with left-symbol E and T respectly.
		  */
		void compute_adp_graph(const Attr_grammar &grammar);

		bool check_cyclic_adp_dependencies();

		/**
		  * Prints all graphs generates: DP, Down, DCG and ADP.
		  */
		void print_all_graphs(const map<unsigned short, Rule> &rules) const;

		/**
		  * Prints all graphs graph cycles.
		  */
		void print_graphs_cyclic(const map<unsigned short, Rule> &rules) const;

		void print_dp_graphs(const map<unsigned short, Rule> &rules) const;

		void print_down_graphs() const;
		void print_dcg_graphs(const map<unsigned short, Rule> &rules) const;
		void print_adp_graphs(const map<unsigned short, Rule> &rules) const;
};

} /* end genevalmag */

#endif /* BUILDER_GRAPHS_H_ */
