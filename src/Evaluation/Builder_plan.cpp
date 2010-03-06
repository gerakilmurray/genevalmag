/**
  *  \file		Builder_plan.cpp
  *  \brief		Implementation of the methods the Builder_plan.h
  *  \date		18/02/2010
  *  \author	Kilmurray, Gerardo Luis <gerakilmurray@gmail.com>
  *  \author	Picco, Gonzalo Martin <gonzalopicco@gmail.com>
  */

#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/topological_sort.hpp>

#include <iostream>

#include "Builder_plan.h"
#include "Builder_graphs.h"

using namespace boost;

namespace genevalmag
{

Builder_plan::Builder_plan(){}
Builder_plan::~Builder_plan(){}

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

void check_cyclic_dependencies(map<vector<unsigned short>, Dp_graph> &adp_graphs)
{
	for(map <vector<unsigned short>,Dp_graph>::iterator adp_it = adp_graphs.begin(); adp_it != adp_graphs.end(); adp_it++)
	{
		bool has_cycle = false;
		vector<unsigned short> path;
		cycle_detector vis(has_cycle);
		vis.set_path(&path);
		boost::depth_first_search(adp_it->second, visitor(vis));

		if(has_cycle)
		{
			cout << "Grafo con ciclo: ";
			property_map<Dp_graph, vertex_data_t>::type props(get(vertex_data_t(), adp_it->second));

			for(size_t i(0); i < path.size(); i++)
			{
				cout << props[path[i]]->to_string() << ",";
			}
			cout << endl;
		}
	}
}

void Builder_plan::build_plans(const Attr_grammar &attr_grammar)
{
	Builder_graphs b_graphs;

	b_graphs.compute_dependency_graphs(attr_grammar.get_rules());
	cout << "DP" << endl;
	b_graphs.compute_down_graph(attr_grammar.get_non_terminal_symbols(), attr_grammar.get_rules());
	cout << "DOWN" << endl;
	b_graphs.compute_dcg(attr_grammar.get_rules());
	cout << "DCG" << endl;
	b_graphs.compute_adp_graph(attr_grammar);
	cout << "ADP" << endl;
	b_graphs.print_all_graphs(attr_grammar.get_rules());
	cout << "PRINT" << endl;
	check_cyclic_dependencies(b_graphs.get_adp_graphs());
	cout << "CHECK CYCLES" << endl;
}
} // end genevalmag
