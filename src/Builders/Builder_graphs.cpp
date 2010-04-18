/**
  *  \file		Builder_graphs.cpp
  *  \brief		Implementation of the methods the Builder_graph.h
  *  \date		17/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

/**
  * The main bibliography:
  *
  *  Wuu Yang (1997), "Multi-plan attribute grammars",
  *  Proceedings of the Joint 1997 Asia Pacific Software Engineering Conference
  *  and International Computer Science Conference, (Hong Kong, December 2-5), 62-71, 1997.
  *  (NSC 86-2213-E-009-079)
  *
  *  http://www.cis.nctu.edu.tw/~wuuyang/papers/magAPSEC.ps
  */

#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>

#include <boost/graph/graphviz.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>

#include "../../include/Builders/Builder_graphs.h"
#include "../../include/Util/Utilities.h"

using namespace std;
using namespace boost;
using namespace utilities;

namespace genevalmag
{

const string PATH_OUTPUT_GRAPHS("graphs/");
const string PATH_OUTPUT_DP("1_DP_graphs/");
const string PATH_OUTPUT_DOWN("2_DOWN_graphs/");
const string PATH_OUTPUT_DCG("3_DCG_graphs/");
const string PATH_OUTPUT_ADP("4_ADP_graphs/");
const string PATH_OUTPUT_CYCLIC("CYCLIC_graphs/");

const string FILE_DP_GRAPH ("_dp_graph");
const string FILE_DOWN_GRAPH ("_down_graph");
const string FILE_DCG_GRAPH ("_dcg_graph");
const string FILE_ADP_GRAPH ("_adp_graph");
const string FILE_ADP_SUBGRAPH_CYCLIC ("_adp_subgraph_with_cyclic");

/**
  * Constructor empty of Builder graphs.
  */
Builder_graphs::Builder_graphs()
{
}

/**
  * Destructor empty of Builder graphs.
  */
Builder_graphs::~Builder_graphs()
{
}

/**
  * Returns the map with all ADP graphs creates.
  */
const map<vector<unsigned short>, Graph> &Builder_graphs::get_adp_graphs() const
{
	return p_Adp_graphs;
}

/**
  * Returns the map with all ADP graphs creates.
  */
const map<vector<unsigned short>, Graph> &Builder_graphs::get_cyclic_graphs() const
{
	return p_Adp_subgraphs_cyclics;
}

/**
  * Returns the down graph of the symbol.
  */
const Graph &Builder_graphs::get_dcg_graph(unsigned short index_rule) const
{
	return p_Dcg_graphs.find(index_rule)->second;
}

/**
  * Algorithm DP
  * Builds a graph dp for each rule of the grammar.
  * Ex: E:= E + T
  * 	graph: 	vertex: E,T
  * 			Edges: 	E --> E
  * 					T---> E
  */
bool Builder_graphs::compute_dependency_graphs(const map<unsigned short,Rule> &rules)
{
	Graph current_p_Dp_graph;
	property_map<Graph, vertex_data_t>::type leafs(get(vertex_data_t(), current_p_Dp_graph));

	/* For the rules. */
	for(map<unsigned short,Rule>::const_iterator it(rules.begin()); it != rules.end(); it++)
	{
		const Rule *rule(&it->second);
		/* For the eqs. */
		for(map<unsigned short,Equation>::const_iterator eq(rule->get_eqs().begin()); eq != rule->get_eqs().end(); eq++)
		/* For each instance build a new edge entre left instance and rigth instance. */
		{
			/* Insert left instance. */
			vector<const Ast_leaf*> elem_leaf_tree;
			eq->second.inorder_only_leaf(eq->second.get_r_value(), elem_leaf_tree);

			/* Verify if vertex belong at graph. */
			Vertex l_v(return_vertex(current_p_Dp_graph, eq->second.get_l_value()));
			if (l_v == USHRT_MAX)
			{
				/* The vertex is new in the graph. */
				l_v = add_vertex(current_p_Dp_graph);
				put(leafs, l_v, eq->second.get_l_value());
			}
			/* For the right side of equation. */
			for(size_t i(0); i< elem_leaf_tree.size(); i++)
			{
				/* Verify if vertex belong at graph. */
				Vertex r_v(return_vertex(current_p_Dp_graph,elem_leaf_tree[i]));
				if (r_v == USHRT_MAX)
				{
					/* The vertex is new in the graph. */
					r_v = add_vertex(current_p_Dp_graph);
					put(leafs,r_v,elem_leaf_tree[i]);
				}
				/* Add edge between left instance and right instance. r_v --> l_v. */
				add_edge(r_v,l_v,current_p_Dp_graph);
			}
		}
		/* Insert current graph in map of denpendency graph. */
		pair<unsigned short, Graph > new_p(rule->key(), current_p_Dp_graph);
		p_Dp_graphs.insert(new_p);
		current_p_Dp_graph.clear();
	}
	return true;
}

/**
  * Builds a graph for each symbol of the grammar with all atributes.
  * The graph only has vertexs. It hasn't edges.
  * Ex: Symbol E ; attributes: s,i
  * 	graph: 	vertex: E.s, E.i
  */
void Builder_graphs::compute_attr_vertex(const map<string,Symbol> &symbols)
{
	Graph current_graph;
	/* For all symbol. */
	for(map<string,Symbol >::const_iterator s_it(symbols.begin()); s_it != symbols.end(); s_it++)
	{
		property_map<Graph, vertex_data_t>::type props_down(get(vertex_data_t(), current_graph));
		Ast_instance ins;
		ins.set_symb(&s_it->second);
		/* For all symbol's attributes */
		for (size_t i(0); i < s_it->second.get_attrs().size(); i++)
		{
			ins.set_num(0);
			ins.set_attr(s_it->second.get_attrs()[i]);
			/* For all dp graph*/
			for(map<unsigned short,Graph >::const_iterator dp(p_Dp_graphs.begin()); dp != p_Dp_graphs.end(); dp++)
			{
				Vertex node(return_vertex(dp->second, &ins));
				if (node != USHRT_MAX)
				{
					/* The vertex is new in the graph. */
					Vertex node_down(add_vertex(current_graph));
					property_map<Graph, vertex_data_t>::const_type props_dp(get(vertex_data_t(), dp->second));
					put(props_down, node_down, props_dp[node]);
					break;
				}
			}
		}
		/* Insert current graph in map of down graph. */
		pair<string, Graph > new_p(s_it->second.key(), current_graph);
		attr_vertex_graphs.insert(new_p);

		current_graph.clear();
	}
}

/**
  * Algorithm Down
  * Builds the graphs down for each symbol of the grammar.
  * Ex: Down(E) :
  * 	(1) E:= E + T.
  * 	graph G: DP(1) U Down(E) U Down(T)
  * 	Project(G,{attributes of E})
  */
bool Builder_graphs::compute_down_graph(const map<string,Symbol> &symbols, const map<unsigned short,Rule> &rules)
{
	compute_attr_vertex(symbols);

	complete_dp_graphs(rules);

	/* Insert current graph in map of down graph. */
	for(map<string,Graph >::iterator attr_it(attr_vertex_graphs.begin()); attr_it != attr_vertex_graphs.end(); attr_it++)
	{
		pair<string, Graph > new_p(attr_it->first, attr_it->second);
		p_Down_graphs.insert(new_p);
	}

	/* In this point obtains the all initialiced downs. */
	Graph current_graph;
	/* Circle Dp graph. */
	for(map<unsigned short, Graph >::iterator dp(p_Dp_graphs.begin()); dp != p_Dp_graphs.end(); dp++)
	{
		/* Obtain rule of graph. */
		const Rule *current_rule(&(rules.find(dp->first)->second));
		/* Obtain all non-terminals symbols of the right-side of the rule. */
		vector<const Symbol*> r_non_terminals(current_rule->get_non_terminals_right_side());

		/* curren_graph = Dp(rule). */
		current_graph = dp->second;

		/* Circle for join all Down of the symbol right-side. */
		for (size_t i(0); i < r_non_terminals.size(); i++)
		{
			Graph &down_graph(p_Down_graphs.find(r_non_terminals[i]->key())->second);
			Graph merged;
			merge_graph(current_graph, down_graph, merged);
			current_graph.clear();
			current_graph = merged;
		}
		/* In this point: current_graph = Dp(Rule) U down(X1) U....U down(Xn). */

		/* Project for left symbol of current_rule. */
		project_graph(current_rule->get_left_symbol(), current_graph);

		/* Modifies the down graph of symbol. */
		Graph &old_down_graph(p_Down_graphs.find(current_rule->get_left_symbol()->key())->second);
		Graph new_down_graph;
		merge_graph(current_graph,old_down_graph,new_down_graph);
		old_down_graph = new_down_graph;
		new_down_graph.clear();
		current_graph.clear();
	}
	return true;
}

/**
  * Algorithm DCG
  * Builds the graph Dcg for each rule of the grammar.
  * Ex: Dcg E(1) :
  * 	(1) E:= E + T.
  * 	graph G: DP(1) U Down(E) U Down(T)
  * 	Project(G,{attributes of E})
  */
bool Builder_graphs::compute_dcg(const map<unsigned short, Rule> &rules)
{
	Graph current_graph;
	/* Circle Dp graph. */
	for(map <unsigned short, Graph>::iterator it(p_Dp_graphs.begin()); it != p_Dp_graphs.end(); it++)
	{
		/* Obtain rule of graph. */
		const Rule *current_rule(&(rules.find(it->first)->second));
		/* Obtain all non-terminals symbols of the right-side of the rule. */
		vector<const Symbol*> r_non_terminals(current_rule->get_non_terminals_right_side());
		/* curren_graph = Dp(rule). */
		current_graph = it->second;

		/* Circle for join all Down of the symbol right-side. */
		for (size_t i(0); i < r_non_terminals.size(); i++)
		{
			Graph &down_graph(p_Down_graphs.find(r_non_terminals[i]->key())->second);
			Graph merged;
			merge_graph(current_graph,down_graph,merged);
			current_graph.clear();
			current_graph = merged;
		}
		/* In this point: current_graph = Dp(Rule) U down(X1) U....U down(Xn). */

		/* Project for left symbol of current_rule. */
		project_graph(current_rule->get_left_symbol(), current_graph);

		/* Insert current graph in map of down graph. */
		pair<unsigned short, Graph > new_p(current_rule->key(), current_graph);
		p_Dcg_graphs.insert(new_p);
	}
	return true;
}

/**
  * Generate all combinations of the rules and saves a graph ADP for each of them.
  */
bool Builder_graphs::combined_inf_contexts(const Rule *rule, Graph &graph, vector< vector<unsigned short> > &inf_context, size_t index_to_combine)
{
	static vector<unsigned short> adp_plan;

	if(index_to_combine == inf_context.size())
	{
		Graph current_graph(graph);

		vector<unsigned short> name_adp;

		/* Adds DP graph's key. */
		name_adp.push_back(rule->key());

		/* Circle for join all DCG of the symbol right-side. */
		for(size_t i(0); i < adp_plan.size(); i++)
		{
			Graph &dcg_graph(p_Dcg_graphs.find(adp_plan[i])->second);
			Graph merged;
			merge_graph(current_graph, dcg_graph, merged);
			current_graph.clear();
			current_graph = merged;

			/* Adds DCG graph's key. */
			name_adp.push_back(adp_plan[i]);
		}
		/* In this point: current_graph = Dp(Rule) U dcg(X1) U....U dcg(Xn). */

		/* Saving the ADP complete in the map. */
		pair<vector<unsigned short>, Graph> new_p(name_adp, current_graph);
		p_Adp_graphs.insert(new_p);
	}
	else
	{
		if (index_to_combine < inf_context.size())
		{
			for(size_t i(0); i < inf_context[index_to_combine].size(); i++)
			{
				adp_plan.push_back(inf_context[index_to_combine][i]);
				combined_inf_contexts(rule, graph, inf_context, index_to_combine + 1);
				adp_plan.pop_back();
			}
		}
		else
		{
			cerr << "ERROR: Index out bounds: combined ADP graphs." << endl;
			return false;
		}
	}
	return true;
}

/**
  * Algorithm ADP
  * Builds the graphs ADP for each rule of the grammar.
  * Ex: ADP(1):
  * 	(1) E:= E + T.
  * 	graph G: DP(1) U Dcg E (J1..JN) U Dcg T (K1..KM)
  * 	Where Ji y ki are rule with left-symbol E and T respectly.
  */
bool Builder_graphs::compute_adp_graph(const Attr_grammar &grammar)
{
	Graph current_graph;
	/* Circle Dp graph. */
	for(map <unsigned short,Graph>::iterator it(p_Dp_graphs.begin()); it != p_Dp_graphs.end(); it++)
	{
		/* Obtain rule of graph. */
		const Rule *current_rule(&(grammar.get_rules().find(it->first)->second));

		/* Obtain all non-terminals symbols of the right-side of the rule. */
		vector<const Symbol*> r_non_terminals(current_rule->get_non_terminals_right_side());

		/* curren_graph = Dp(rule). */
		current_graph = it->second;

		/* Inicializacion del vector de no terminales con todas las reglas en donde son left symbol. */
		vector< vector<unsigned short> > inf_contexts;
		for (size_t i(0); i < r_non_terminals.size(); i++)
		{
			/* Obtain all rule with the left-symbol one right symbol of the current_rule. */
			inf_contexts.push_back(grammar.get_rules_with_left_symbol(r_non_terminals[i]));
		}

		/* Generates and saves all combinatios of context with these rules. */
		if(!combined_inf_contexts(current_rule, current_graph, inf_contexts, 0))
		{
			return false;
		}
	}
	return true;
}

struct cycle_detector: public dfs_visitor<>
{
	public:
		cycle_detector(bool& has_cycle, Graph &graph): _has_cycle(has_cycle), _graph_cycle(graph){}

	    template <class Edge, class G>
	    /**
	     *  Re-define method for detect circle when examine each edge: Save ciclic subgraph.
	     */
		void examine_edge(Edge u, const G &g)
	    {
	    	if(!_has_cycle)
	    	{
	    		typename G::vertex_descriptor v1(source(u, g));
	    		typename G::vertex_descriptor v2(target(u, g));

	    		typename property_map<G, vertex_data_t>::const_type props(get(vertex_data_t(), g));
	    		property_map<Graph, vertex_data_t>::type prop_cycle(get(vertex_data_t(), _graph_cycle));

	    		Vertex v1_path(return_vertex(_graph_cycle, props[v1]));
	    		if (v1_path == USHRT_MAX)
	    		{
	    			v1_path = add_vertex(_graph_cycle);
					put(prop_cycle, v1_path, props[v1]);
	    		}

	    		Vertex v2_path(return_vertex(_graph_cycle, props[v2]));
				if (v2_path == USHRT_MAX)
				{
					v2_path = add_vertex(_graph_cycle);
					put(prop_cycle, v2_path, props[v2]);
				}

	    		add_edge(v1_path, v2_path, _graph_cycle);
	    	}
	    }

	    template <class Edge, class G>
	    void back_edge(Edge u, const G& g)
		{
			_has_cycle = true;
		}

	protected:
		bool     &_has_cycle;
	    Graph    &_graph_cycle;
};

/**
  * Checks if the graph contains cycle.
  * Utilities a deph-firts-seach for traverse the graphs.
  */
bool Builder_graphs::check_cyclic_adp_dependencies()
{
	bool cycles_detect(false);
	for(map <vector<unsigned short>,Graph>::iterator adp_it(p_Adp_graphs.begin()); adp_it != p_Adp_graphs.end(); adp_it++)
	{
		bool has_cycle(false);
		Graph g_cycle;
		cycle_detector vis(has_cycle, g_cycle);
		boost::depth_first_search(adp_it->second, visitor(vis));

		cycles_detect = (cycles_detect || has_cycle);

		if(has_cycle)
		{
			/* Saving the ADP subgraph with cycle in the map. */
			pair<vector<unsigned short>, Graph> new_p(adp_it->first, g_cycle);
			p_Adp_subgraphs_cyclics.insert(new_p);
		}
	}
	return cycles_detect;
}

/**
  * Completes dp-graph with the vertex of low on instances.
  */
void Builder_graphs::complete_dp_graphs(const map<unsigned short, Rule> &rules)
{
	for(map<unsigned short,Graph >::iterator dp(p_Dp_graphs.begin()); dp != p_Dp_graphs.end(); dp++)
	{
		const Rule &rule(rules.find(dp->first)->second);
		Graph attr_symb(attr_vertex_graphs.find(rule.get_left_symbol()->key())->second);
		Graph new_with_attr_symb;
		merge_graph(dp->second, attr_symb, new_with_attr_symb);
		dp->second = new_with_attr_symb;
	}
}

/**
  * Saves all dp-graphs generates
  */
bool Builder_graphs::save_dp_graphs(const map<unsigned short, Rule> &rules, const string path_output) const
{
	string path_out(path_output);
	path_out.append(PATH_OUTPUT_DP);

	if(!clean_output_folder(path_out))
	{
		return false;
	}

	for(map <unsigned short,Graph>::const_iterator it(p_Dp_graphs.begin()); it != p_Dp_graphs.end(); it++)
	{
		string name_graph("Dependency Graph of rule ");
		const Rule *current_rule(&(rules.find(it->first)->second));
		name_graph.append(cleaning_tabs(current_rule->to_string_not_eqs()));

		size_t count_vertex(num_vertices(it->second));
		string names[count_vertex];
		generate_names_instance(it->second,names,count_vertex);
		print_graph(it->second,path_out ,FILE_DP_GRAPH, name_graph,names,"ellipse");
	}
	return true;
}
/**
  * Saves all down-graphs generates.
  */
bool Builder_graphs::save_down_graphs(const string path_output) const
{
	string path_out(path_output);
	path_out.append(PATH_OUTPUT_DOWN);

	if(!clean_output_folder(path_out))
	{
		return false;
	}

	for(map <string,Graph>::const_iterator it(p_Down_graphs.begin()); it != p_Down_graphs.end(); it++)
	{
		string name_graph("Graph Down(");
		name_graph.append(it->first);
		name_graph.append(")");

		size_t count_vertex(num_vertices(it->second));
		string names[count_vertex];
		generate_names_attr(it->second,names,count_vertex);
		print_graph(it->second,path_out.c_str(),FILE_DOWN_GRAPH,name_graph,names,"ellipse");
	}
	return true;
}
/**
  * Saves all dcg-graphs generates.
  */
bool Builder_graphs::save_dcg_graphs(const map<unsigned short, Rule> &rules, const string path_output) const
{
	string path_out(path_output);
	path_out.append(PATH_OUTPUT_DCG);

	if(!clean_output_folder(path_out))
	{
		return false;
	}

	for(map <unsigned short,Graph>::const_iterator it(p_Dcg_graphs.begin()); it != p_Dcg_graphs.end(); it++)
	{
		string name_graph("DCG Graph of rule ");
		const Rule *current_rule(&(rules.find(it->first)->second));
		name_graph.append(cleaning_tabs(current_rule->to_string_not_eqs()));
		name_graph.append(" with symbol ");
		name_graph.append(current_rule->get_left_symbol()->get_name());

		size_t count_vertex(num_vertices(it->second));
		string names[count_vertex];
		generate_names_instance(it->second,names,count_vertex);
		print_graph(it->second,path_out.c_str(),FILE_DCG_GRAPH,name_graph,names,"ellipse");
	}
	return true;
}
/**
  * Saves all adp-graphs generates.
  */
bool Builder_graphs::save_adp_graphs(const map<unsigned short, Rule> &rules, const string path_output) const
{
	string path_out(path_output);
	path_out.append(PATH_OUTPUT_ADP);

	if(!clean_output_folder(path_out))
	{
		return false;
	}

	for(map <vector<unsigned short>,Graph>::const_iterator it(p_Adp_graphs.begin()); it != p_Adp_graphs.end(); it++)
	{
		string name_graph("ADP Graph of rule ");
		const Rule *rule(&(rules.find(it->first[0])->second));
		name_graph.append(cleaning_tabs(rule->to_string_not_eqs()));

		name_graph.append(write_inf_context(it->first));
		name_graph.append(".");

		size_t count_vertex(num_vertices(it->second));
		string names[count_vertex];
		generate_names_instance(it->second,names,count_vertex);
		print_graph(it->second,path_out.c_str(), FILE_ADP_GRAPH, name_graph,names,"ellipse");
	}
	return true;
}

/**
  * Saves all graphs generates: DP, Down, DCG and ADP.
  */
bool Builder_graphs::save_all_graphs(const map<unsigned short, Rule> &rules, const string path_output) const
{
	string path_out(path_output);
	path_out.append(PATH_OUTPUT_GRAPHS);

	if(clean_output_folder(path_out) &&
       save_dp_graphs(rules, path_out) &&
       save_down_graphs(path_out) &&
       save_dcg_graphs(rules, path_out) &&
       save_adp_graphs(rules, path_out))
	{
		return true;
	}
	return false;
}

bool Builder_graphs::save_cyclic_graphs(const map<unsigned short, Rule> &rules, const string path_output) const
{
	string path_out(path_output);
	path_out.append(PATH_OUTPUT_GRAPHS);

	if(!clean_output_folder(path_out))
	{
		return false;
	}
	path_out.append(PATH_OUTPUT_CYCLIC);
	if(!clean_output_folder(path_out))
	{
		return false;
	}

	for(map <vector<unsigned short>,Graph>::const_iterator it(p_Adp_subgraphs_cyclics.begin()); it != p_Adp_subgraphs_cyclics.end(); it++)
	{
		string name_graph("ADP Subgraph cyclic of rule ");
		const Rule *rule(&(rules.find(it->first[0])->second));
		name_graph.append(cleaning_tabs(rule->to_string_not_eqs()));

		name_graph.append(write_inf_context(it->first));
		name_graph.append(".");

		size_t count_vertex(num_vertices(it->second));
		string names[count_vertex];
		generate_names_instance(it->second,names,count_vertex);
		print_graph(it->second,path_out.c_str(), FILE_ADP_SUBGRAPH_CYCLIC, name_graph,names,"ellipse");
	}
	return true;
}

} /* end genevalmag */
