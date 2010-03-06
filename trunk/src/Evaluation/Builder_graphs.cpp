/**
  *  \file		Builder_graphs.cpp
  *  \brief		Implementation of the methods the DC_graph.h
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
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/transitive_closure.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>

#include "Builder_graphs.h"
#include "../Attr_grammar/Symbol.h"
#include "../Attr_grammar/Attr_grammar.h"
#include "../Parser/Semantics_actions.h"

using namespace boost;
using namespace std;

namespace genevalmag
{

const string PATH_OUTPUT_FILE ("./src/out_graph/");
const string FILE_DP_GRAPH ("_dp_graph");
const string FILE_DOWN_GRAPH ("_down_graph");
const string FILE_DCG_GRAPH ("_dcg_graph");
const string FILE_ADP_GRAPH ("_adp_graph");

Builder_graphs::Builder_graphs(){}

Builder_graphs::~Builder_graphs(){}

map<vector<unsigned short>, Dp_graph> & Builder_graphs::get_adp_graphs()
{
	return p_Adp_graphs;
}

void clean_output_folder()
{
	// Remove the folder.
	string command_rm_folder("rm -f -r ");
	command_rm_folder.append(PATH_OUTPUT_FILE);
	if (system (command_rm_folder.c_str()) != 0)
	{
		cerr << "ERROR: the filesystem denies folder's remove." << endl;
	}

	// Create folder.
	string command_mkdir_folder("mkdir -p ");
	command_mkdir_folder.append(PATH_OUTPUT_FILE);
	if (system (command_mkdir_folder.c_str()) != 0)
	{
		cerr << "ERROR: the filesystem denies folder's creation." << endl;
	}
}

/**
  * Prints a graph in a file dot for generate image png.
  */
void print_graph(Dp_graph &graph, const string name_file, const string name_graph)
{
	static int num_file = 0; // For name of file png
	size_t count_vertex(num_vertices(graph));

	// Arrays of node's name.
	string datas[count_vertex];
	property_map<Dp_graph, vertex_data_t>::type props(get(vertex_data_t(), graph));

	for(size_t i(0); i < count_vertex; i++)
	{
		if(name_file.compare(FILE_DOWN_GRAPH) == 0)
		{
			// The vertexs in a Down graph are ONLY Ast_instance.
			datas[i] = ((Ast_instance*)props[i])->get_attr()->get_name();
		}
		else
		{
			datas[i] = props[i]->to_string();
		}
	}

	// Create file dot.
	string n_f(PATH_OUTPUT_FILE);

	stringstream ins;
	ins << ++num_file;
	n_f.append(ins.str());

	n_f.append(name_file);

	n_f.append(".dot");

	// Obtain of file of graphviz.
	ofstream salida(n_f.c_str());
	std::map<std::string,std::string> graph_attr, vertex_attr, edge_attr;
	//graph_attr["size"] = "5,3";
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

/**
  * Prints a graph in the standart out (std:cout).
  */
void print_graph_txt(Dp_graph &graph)
{
	size_t count_vertex = num_vertices(graph);
	cout << "<< Vertex >> " << num_vertices(graph) << endl;
	// Arrays of node's name.
	property_map<Dp_graph, vertex_data_t>::type props = get(vertex_data_t(), graph);
	for(size_t i = 0; i < count_vertex; i++)
	{
		cout << props[i]->to_string() << endl;;
	}
	cout << "<< Edges >> " << num_edges(graph) << endl;
	graph_traits<Dp_graph>::edge_iterator ei, ei_end;
	for (tie(ei,ei_end) = edges(graph); ei != ei_end; ++ei)
	{
		Dp_graph::vertex_descriptor source_vertex = source(*ei, graph);
		Dp_graph::vertex_descriptor target_vertex = target(*ei, graph);

		cout << props[source_vertex]->to_string() << "---->" << props[target_vertex]->to_string() << endl;
	}
}

/**
  * Given a graph and node,  returns vertex descriptor of node in the graph.
  * If not search it, so returns USHRT_MAX.
  */
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

/**
  * Algorithm DP
  * Builds a graph dp for each rule of the grammar.
  * Ex: E:= E + T
  * 	graph: 	vertex: E,T
  * 			Edges: 	E --> E
  * 					T---> E
  */
void Builder_graphs::compute_dependency_graphs(const map<unsigned short, Rule> &rules)
{
	Dp_graph current_p_Dp_graph;
	property_map<Dp_graph, vertex_data_t>::type leafs = get(vertex_data_t(), current_p_Dp_graph);

	// for the rules.
	for(map<unsigned short,Rule>::const_iterator it = rules.begin(); it != rules.end(); it++)
	{
		const Rule * rule = &it->second;
		// for the eqs
		for(map<unsigned short,Equation>::const_iterator eq = rule->get_eqs().begin(); eq != rule->get_eqs().end(); eq++)
		// For each instance build a new edge entre left instance and rigth instance.
		{
			// Insert left instance.
			vector<const Ast_leaf*> elem_leaf_tree;
			eq->second.inorder_only_leaf(eq->second.get_r_value(), elem_leaf_tree);

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
		// Insert current graph in map of denpendency graph.
		pair<unsigned short, Dp_graph > new_p(rule->key(), current_p_Dp_graph);
		pair<map<unsigned short, Dp_graph >::iterator, bool > result = p_Dp_graphs.insert(new_p);
		current_p_Dp_graph.clear();
	}
}

/**
  * Joins graph1 and graph2 in graph_merged.
  */
void merge_graph(Dp_graph &graph1, Dp_graph &graph2, Dp_graph &graph_merged)
{
	// Cleans the result graph.
	graph_merged.clear();

	// Copies the graph1 to result graph.
	graph_merged = graph1;

	// Join the graph2 to result graph.
	property_map<Dp_graph, vertex_data_t>::type props = get(vertex_data_t(), graph2);
	property_map<Dp_graph, vertex_data_t>::type props_merged = get(vertex_data_t(), graph_merged);
	// Circle for vertices.
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
	// Cicle for edges.
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

/**
  * Projects a graph with only vertex that belongs to symbol "symb".
  * Modifies the parameter "graph".
  */
void Builder_graphs::project_graph(const Symbol * symb, Dp_graph &graph)
{
	// Applies transitivity to graph with only nodes of symb.
	warshall_transitive_closure(graph);

	property_map<Dp_graph, vertex_data_t>::type props = get(vertex_data_t(), graph);
	// Reduces the graph for symbol "symb".
	for (size_t i = num_vertices(graph); i > 0; i--)
	{
		const Ast_instance *ins = dynamic_cast<const Ast_instance*>(props[i-1]);
		if (!ins || !ins->get_symb()->equals(*symb))
		// The node is a literal-node or is a node with symbol diferent that symb.
		{
			clear_vertex(i-1, graph);
			remove_vertex(i-1, graph);
		}
	}
	Dp_graph attr_symb = attr_vertex_graphs.find(symb->key())->second;
	Dp_graph new_with_attr_symb;
	merge_graph(graph,attr_symb,new_with_attr_symb);
	graph = new_with_attr_symb;
}

/**
  * Builds a graph for each symbol of the grammar with all atributes.
  * The graph only has vertexs. It hasn't edges.
  * Ex: Symbol E ; attributes: s,i
  * 	graph: 	vertex: E.s, E.i
  */
void Builder_graphs::compute_attr_vertex(const map<string,Symbol> &symbols)
{
	Dp_graph current_graph;
	for(map<string,Symbol >::const_iterator s_it = symbols.begin(); s_it != symbols.end(); s_it++)
	{
		property_map<Dp_graph, vertex_data_t>::type props_down = get(vertex_data_t(), current_graph);
		Ast_instance ins;
		ins.set_symb(&s_it->second);
		for (size_t i(0); i < s_it->second.get_attrs().size(); i++)
		{
			ins.set_num(0);
			ins.set_attr(s_it->second.get_attrs()[i]);
			for(map<unsigned short,Dp_graph >::iterator dp = p_Dp_graphs.begin(); dp != p_Dp_graphs.end(); dp++)
			{
				Dp_graph::vertex_descriptor node = return_vertex(dp->second, &ins);
				if (node != USHRT_MAX)
				{
					Dp_graph::vertex_descriptor node_down = add_vertex(current_graph);
					property_map<Dp_graph, vertex_data_t>::type props_dp = get(vertex_data_t(), dp->second);
					put(props_down, node_down, props_dp[node]);
					break;
				}
			}
		}
		// Insert current graph in map of down graph
		pair<string, Dp_graph > new_p(s_it->second.key(), current_graph);
		pair<map<string, Dp_graph >::iterator, bool > result = attr_vertex_graphs.insert(new_p);

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
void Builder_graphs::compute_down_graph(const map<string,Symbol> &symbols, const map<unsigned short,Rule> &rules)
{
	compute_attr_vertex(symbols);

	// Insert current graph in map of down graph
	for(map<string,Dp_graph >::iterator attr_it = attr_vertex_graphs.begin(); attr_it != attr_vertex_graphs.end(); attr_it++)
	{
		pair<string, Dp_graph > new_p(attr_it->first, attr_it->second);
		pair<map<string, Dp_graph >::iterator, bool > result = p_Down_graphs.insert(new_p);
	}

	// In this point obtains the all initialiced downs.

	Dp_graph current_graph;
	// Circle Dp graph.
	for(map<unsigned short, Dp_graph >::iterator dp = p_Dp_graphs.begin(); dp != p_Dp_graphs.end(); dp++)
	{
		// Obtain rule of graph.
		const Rule *current_rule = &(rules.find(dp->first)->second);
		// Obtain all non-terminals symbols of the right-side of the rule.
		vector<const Symbol*> r_non_terminals = current_rule->get_non_terminals_right_side();

		// curren_graph = Dp(rule).
		current_graph = dp->second;

		// Circle for join all Down of the symbol right-side.
		for (size_t i = 0; i < r_non_terminals.size();i++)
		{
			Dp_graph &down_graph = p_Down_graphs.find(r_non_terminals[i]->key())->second;
			Dp_graph merged;
			merge_graph(current_graph,down_graph,merged);
			current_graph.clear();
			current_graph = merged;
		}
		// In this point: current_graph = Dp(Rule) U down(X1) U....U down(Xn).

		// Project for left symbol of current_rule.
		project_graph(current_rule->get_left_symbol(),current_graph);

		// Modifies the down graph of symbol.
		Dp_graph &old_down_graph = p_Down_graphs.find(current_rule->get_left_symbol()->key())->second;
		Dp_graph new_down_graph;
		merge_graph(current_graph,old_down_graph,new_down_graph);
		old_down_graph = new_down_graph;
		new_down_graph.clear();
		current_graph.clear();
	}
}

/**
  * Algorithm DCG
  * Builds the graph Dcg for each rule of the grammar.
  * Ex: Dcg E(1) :
  * 	(1) E:= E + T.
  * 	graph G: DP(1) U Down(E) U Down(T)
  * 	Project(G,{attributes of E})
  */
void Builder_graphs::compute_dcg(const map<unsigned short, Rule> &rules)
{
	Dp_graph current_graph;
	// Circle Dp graph.
	for(map <unsigned short, Dp_graph>::iterator it = p_Dp_graphs.begin(); it != p_Dp_graphs.end(); it++)
	{
		// Obtain rule of graph.
		const Rule *current_rule = &(rules.find(it->first)->second);
		// Obtain all non-terminals symbols of the right-side of the rule.
		vector<const Symbol*> r_non_terminals = current_rule->get_non_terminals_right_side();
		// curren_graph = Dp(rule).
		current_graph = it->second;

		// Circle for join all Down of the symbol right-side.
		for (size_t i = 0; i < r_non_terminals.size();i++)
		{
			Dp_graph &down_graph = p_Down_graphs.find(r_non_terminals[i]->key())->second;
			Dp_graph merged;
			merge_graph(current_graph,down_graph,merged);
			current_graph.clear();
			current_graph = merged;
		}
		// In this point: current_graph = Dp(Rule) U down(X1) U....U down(Xn)
		project_graph(current_rule->get_left_symbol(),current_graph);

		// Insert current graph in map of down graph
		pair<unsigned short, Dp_graph > new_p(current_rule->key(), current_graph);
		pair<map<unsigned short, Dp_graph >::iterator, bool > result = p_Dcg_graphs.insert(new_p);
	}
}

void Builder_graphs::combined_inf_contexts(const Rule* rule, Dp_graph &graph, vector< vector<const Rule*> > &inf_context, size_t index_to_combine)
{
	static vector<const Rule*> adp_plan;

	if(index_to_combine == inf_context.size())
	{
		Dp_graph current_graph = graph;

		vector<unsigned short> name_adp;

		// Adds DP graph's key.
		name_adp.push_back(rule->key());

		// Circle for join all DCG of the symbol right-side.
		for(size_t i = 0; i < adp_plan.size(); i++)
		{
			Dp_graph &dcg_graph = p_Dcg_graphs.find(adp_plan[i]->key())->second;
			Dp_graph merged;
			merge_graph(current_graph, dcg_graph, merged);
			current_graph.clear();
			current_graph = merged;

			// Adds DCG graph's key.
			name_adp.push_back(adp_plan[i]->key());
		}
		// In this point: current_graph = Dp(Rule) U dcg(X1) U....U dcg(Xn)

		// Saving the ADP complete in the map.
		pair<vector<unsigned short>, Dp_graph> new_p(name_adp, current_graph);
		pair<map<vector<unsigned short>, Dp_graph>::iterator, bool > result = p_Adp_graphs.insert(new_p);
	}
	else
	{
		if (index_to_combine < inf_context.size())
		{
			for(size_t i = 0; i < inf_context[index_to_combine].size(); i++)
			{
				adp_plan.push_back(inf_context[index_to_combine][i]);

				combined_inf_contexts(rule, graph, inf_context, index_to_combine + 1);

				adp_plan.pop_back();
			}
		}
		else
		{
			cerr << "Index out bounds: combined ADP graphs.";
		}
	}
}

/**
  * Algorithm ADP
  * Builds the graphs ADP for each rule of the grammar.
  * Ex: ADP(1):
  * 	(1) E:= E + T.
  * 	graph G: DP(1) U Dcg E (J1..JN) U Dcg T (K1..KM)
  * 	Where Ji y ki are rule with left-symbol E and T respectly.
  */
void Builder_graphs::compute_adp_graph(const Attr_grammar &grammar)
{
	Dp_graph current_graph;
	// Circle Dp graph.
	for(map <unsigned short,Dp_graph>::iterator it = p_Dp_graphs.begin(); it != p_Dp_graphs.end(); it++)
	{
		// Obtain rule of graph.
		const Rule *current_rule = &(grammar.get_rules().find(it->first)->second);

		// Obtain all non-terminals symbols of the right-side of the rule.
		vector<const Symbol*> r_non_terminals = current_rule->get_non_terminals_right_side();

		// curren_graph = Dp(rule).
		current_graph = it->second;

		// Inicializacion del vector de no terminales con todas las reglas en donde son left symbol.
		vector< vector<const Rule*> > inf_contexts;
		for (size_t i = 0; i < r_non_terminals.size();i++)
		{
			// Obtain all rule with the left-symbol one right symbol of the current_rule.
			inf_contexts.push_back(grammar.get_rules_with_left_symbol(r_non_terminals[i]));
		}

		// Generates and saves all combinatios of context with these rules.
		combined_inf_contexts(current_rule, current_graph, inf_contexts, 0);
	}
}

// Prints all graph.
void Builder_graphs::print_all_graphs(const map<unsigned short, Rule> &rules)
{
	clean_output_folder();

	for(map <unsigned short,Dp_graph>::iterator it = p_Dp_graphs.begin(); it != p_Dp_graphs.end(); it++)
	{
		const Rule *current_rule = &(rules.find(it->first)->second);
		string name_graph = "Dependency Graph of rule ";
		name_graph.append(cleaning_tabs(current_rule->to_string_not_eqs()));
		print_graph(it->second,FILE_DP_GRAPH,name_graph);
	}

	for(map <string,Dp_graph>::iterator it = p_Down_graphs.begin(); it != p_Down_graphs.end(); it++)
	{
		string name_graph = "Graph Down(";
		name_graph.append(it->first);
		name_graph.append(")");
		print_graph(it->second,FILE_DOWN_GRAPH,name_graph);
	}

	for(map <unsigned short,Dp_graph>::iterator it = p_Dcg_graphs.begin(); it != p_Dcg_graphs.end(); it++)
	{
		const Rule *current_rule = &(rules.find(it->first)->second);
		string name_graph = "DCG Graph of rule ";
		name_graph.append(cleaning_tabs(current_rule->to_string_not_eqs()));
		name_graph.append(" with symbol ");
		name_graph.append(current_rule->get_left_symbol()->get_name());
		print_graph(it->second,FILE_DCG_GRAPH,name_graph);
	}

	for(map <vector<unsigned short>,Dp_graph>::iterator it = p_Adp_graphs.begin(); it != p_Adp_graphs.end(); it++)
	{
		string name_graph = "ADP Graph of rule ";
		const Rule *rule = &(rules.find(it->first[0])->second);
		name_graph.append(cleaning_tabs(rule->to_string_not_eqs()));

		if (it->first.size() == 1)
		{
			name_graph.append(" hasn't an inferior context");
		}
		else
		{
			name_graph.append(" with inferior context: ");
			for(size_t i = 1; i < it->first.size(); i++)
			{
				name_graph.append(" R");
				stringstream key_rule;
				key_rule << it->first[i];
				name_graph.append(key_rule.str());
				if(i < it->first.size() - 1)
				{
					name_graph.append(" ,");
				}
			}
		}
		name_graph.append(".");
		print_graph(it->second,FILE_ADP_GRAPH,name_graph);
	}
}

struct cycle_detector: public dfs_visitor<>
{
	public:
		cycle_detector(bool& has_cycle): _has_cycle(has_cycle){}

		void set_path(vector<unsigned short> *path)
		{
			_path = path;
		}

	    template <class Vertex, class Graph>
	    void discover_vertex(Vertex u, const Graph& g)
	    {
	    	if(!_has_cycle)
	    	{
	    		_path->push_back(u);
	    	}
	    }

	    template <class Edge, class Graph>
	    void back_edge(Edge u, const Graph& g)
		{
			_has_cycle = true;
		}

	protected:
		vector<unsigned short>	*_path;
		bool&					_has_cycle;
};

void Builder_graphs::check_cyclic_adp_dependencies()
{
	for(map <vector<unsigned short>,Dp_graph>::iterator adp_it = p_Adp_graphs.begin(); adp_it != p_Adp_graphs.end(); adp_it++)
	{
		bool has_cycle = false;
		vector<unsigned short> path;
		cycle_detector vis(has_cycle);
		vis.set_path(&path);
		boost::depth_first_search(adp_it->second, visitor(vis));
		if(has_cycle)
		{
			cout << "Grafo con ciclo: " << endl;

			property_map<Dp_graph, vertex_data_t>::type props(get(vertex_data_t(), adp_it->second));

			Dp_graph subgraph_circle;

			property_map<Dp_graph, vertex_data_t>::type prop_subgraph(get(vertex_data_t(), subgraph_circle));

			graph_traits<Dp_graph>::edge_iterator ei, ei_end;
			for (tie(ei,ei_end) = edges(adp_it->second); ei != ei_end; ++ei)
			{
				Dp_graph::vertex_descriptor source_vertex = source(*ei, adp_it->second);
				Dp_graph::vertex_descriptor target_vertex = target(*ei, adp_it->second);

				for(size_t i(0); i < path.size(); i++)
				{
					if(source_vertex == path[i])
					{
						for(size_t j(0); j < path.size(); j++)
						{
							if(target_vertex == path[j])
							{
								Dp_graph::vertex_descriptor source = return_vertex(subgraph_circle,props[source_vertex]);
								if (source == USHRT_MAX)
								{
									// The vertex is new in the graph.
									source = add_vertex(subgraph_circle);
									put(prop_subgraph,source,props[source_vertex]);
								}

								Dp_graph::vertex_descriptor target = return_vertex(subgraph_circle,props[target_vertex]);
								if (target == USHRT_MAX)
								{
									// The vertex is new in the graph.
									target = add_vertex(subgraph_circle);
									put(prop_subgraph,target,props[target_vertex]);
								}

								add_edge(source,target,subgraph_circle);
							}
						}
					}
				}
			}

			print_graph(subgraph_circle,"_adpWITHcircle","chupame la pija");
		}
	}
}

} // end genevalmag
