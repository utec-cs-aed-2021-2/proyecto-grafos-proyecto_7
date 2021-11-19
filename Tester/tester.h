#ifndef TESTER_H
#define TESTER_H

#include <iostream>
#include <fstream>
#include <errno.h>
#include <string>
#include "../Graph/DirectedGraph.h"
#include "../Graph/UndirectedGraph.h"
#include "../Graph/Algorithms/kruskal.h"
#include "../Graph/Algorithms/prim.h"
#include "../Graph/Algorithms/astar.h"

using namespace std;

template<typename TV, typename TE>
class FileReader {
public:
	FileReader() = default;
	void insertElementsInGraph(const string& fname, Graph<TV, TE>* graph)
	{
		fstream file; 
		file.open(fname, ios::in);
		TV s, e; TE w;
		while (!file.eof())
		{
			file >> s >> w >> e;
			graph->insertVertex(s, s);
			graph->insertVertex(e, e);
			graph->createEdge(s, e, w);
			//cout << s << " " << w << " " << e << '\n';
		}
		file.close();
	}
};

namespace Tester
{
	using tK = string;		// type key
	using tV = int;			// type value

	void executeExamples()
	{
		cout << __PRETTY_FUNCTION__ << endl;
	}

	void executeParser()
	{
		cout << __PRETTY_FUNCTION__ << endl;
	}

	void runAlgorithms(Graph<tK, tV>* graph)
	{
		FileReader<tK, tV> FEngine;
		string fname; int input;
		cout << "================================================" << endl;
	    cout << "MENU ALGORITHMS" << endl;
	    cout << "================================================" << endl;
	    cout << "1. BFS-DFS\n";
	    cout << "2. Kruskal\n";
	    cout << "3. Prim\n";
	    cout << "================================================" << endl;
	    //cin >> input;
	    input = 4;
	    switch (input)
	    {
	    	case 1:
	    	{
	    		fname = "Tester/bfs_dfs.txt";
	    		string label_id = "0";
	    		FEngine.insertElementsInGraph(fname, graph);
	    		BFS tt1(graph, label_id); DFS tt2(graph, label_id);

	    		tt1.run([](Vertex<tK, tV>* current){
	    			cout << current->data << " ";
	    		}); cout << endl;

	    		tt2.run([](Vertex<tK, tV>* current){
	    			cout << current->data << " ";
	    		}); cout << endl;

	    		break;
	    	}
	    	case 2:
	    	{
	    		fname = "Tester/mst3.txt";
	    		FEngine.insertElementsInGraph(fname, graph);
	    		graph->adjList();

	    		Kruskal krus(graph);
	    		auto mst = krus.apply();
				mst.adjList();
	    		break;
	    	}
	    	case 3:
	    	{
	    		fname = "Tester/mst3.txt";
	    		FEngine.insertElementsInGraph(fname, graph);
	    		Prim prim(graph);
	    		prim.apply();
	    		break;
	    	}
	    	case 4:
	    	{
	    		fname = "Tester/connected_dir.txt";
	    		FEngine.insertElementsInGraph(fname, graph);
	    		cout << boolalpha << graph->isConnected() << endl;
	    		cout << boolalpha << graph->isStronglyConnected() << endl;
	    	}
	    	default: break;
	    }
	}

	void runMenu()
	{
		auto ugraph = new UnDirectedGraph<tK, tV>();
	    auto dgraph = new DirectedGraph<tK, tV>();
		int typeG;

		cout << __PRETTY_FUNCTION__ << endl;	
	    cout << "================================================" << endl;
	    cout << "MENU GRAPH TESTER" << endl;
	    cout << "================================================" << endl;
	    cout << "1. Undirected\n";
	    cout << "2. Directed\n";
	    cout << "================================================" << endl;
	    //cin >> typeG;
	    typeG = 2;
	    if (typeG == 1)
	    	runAlgorithms(ugraph);
    	else 
    		runAlgorithms(dgraph);
	}
}

#endif



//TGraph.displayVertex("A");
//TGraph.adjList();
//TGraph.deleteVertex("A");
//TGraph.adjList();
//TGraph.adjList();
//TGraph.deleteEdge("A", "B");
//TGraph.deleteEdge("D", "B");
//TGraph.adjList();
//cout << boolalpha << TGraph.isConnected();
//TGraph.display();
//cout << TGraph("D", "F") << endl;
//TGraph.deleteEdge("D", "C");
//TGraph.deleteVertex("E");
//TGraph.adjList();