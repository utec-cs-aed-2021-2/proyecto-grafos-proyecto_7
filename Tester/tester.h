#ifndef TESTER_H
#define TESTER_H

#include <iostream>
#include <fstream>
#include <cerrno>
#include <string>
#include "../Graph/DirectedGraph.h"
#include "../Graph/UndirectedGraph.h"
#include "../Graph/Algorithms/kruskal.h"
#include "../Graph/Algorithms/prim.h"
#include "../Graph/Algorithms/astar.h"
#include "../Graph/Algorithms/dijkstra.h"
#include "../Graph/Algorithms/floydWarshall.h"

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
		//cout << __PRETTY_FUNCTION__ << endl;
	}

	void executeParser()
	{
	    //cout << __PRETTY_FUNCTION__ << endl;
	}

	void runAlgorithms(UnDirectedGraph<tK, tV>* graph)
	{
	    FileReader<tK, tV> FEngine;
	    string fname; int input;
	    cout << "================================================" << endl;
	    cout << "MENU ALGORITHMS" << endl;
	    cout << "================================================" << endl;
	    cout << "1. BFS-DFS\n";
	    cout << "2. Kruskal\n";
	    cout << "3. Prim\n";
	    cout << "4. AStar\n";
	    cout << "5. BestBFS\n";
	    cout << "6. Dijkstra\n";
	    cout << "================================================" << endl;
	    cin >> input;
	    switch (input)
	    {
	        case 1:
	        {
	            fname = "../Tester/bfs_dfs.txt";
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
	            fname = "../Tester/mst3.txt";
	            FEngine.insertElementsInGraph(fname, graph);
	            graph->adjList();

	            Kruskal krus(graph);
	            auto mst = krus.apply();
	            mst.adjList();
	            break;
	        }
	        case 3:
	        {
	            fname = "../Tester/mst3.txt";
	            FEngine.insertElementsInGraph(fname, graph);
	            Kruskal krus(graph);
	            krus.apply();
	            break;
	        }
	        case 4:
	        {
	            fname = "../Tester/mst1.txt";
                    FEngine.insertElementsInGraph(fname,graph);
                    AStar<tK,tV> a(graph,"A","H");
                    a.apply();
		    break;
	        }
	        case 5:
	        {
	            break;
	        }
	        case 6:
	        {
	            fname = "../Tester/dijkstra.txt";
	            FEngine.insertElementsInGraph(fname, graph);
	            Dijkstra<tK, tV> djkstr(graph);
	            for (const auto& [vertex, weight] : djkstr.run())
	                cout << vertex << " -> " << weight << endl;
	            break;
	        }
	        default: break;
	    }
	}

	void runAlgorithms(DirectedGraph<tK, tV>* graph)
	{
	    FileReader<tK, tV> FEngine;
	    string fname; int input;
	    cout << "================================================" << endl;
	    cout << "MENU ALGORITHMS" << endl;
	    cout << "================================================" << endl;
	    cout << "1. BFS-DFS\n";
	    cout << "2. Kruskal\n";
	    cout << "3. Prim\n";
	    cout << "4. AStar\n";
	    cout << "5. BestBFS\n";
	    cout << "6. Dijkstra\n";
	    cout << "7. Floyd Warshall\n";
	    cout << "8. Bellman Ford\n";
	    cout << "================================================" << endl;
	    cin >> input;
	    switch (input)
	    {
	        case 1:
	        {
	            fname = "../Tester/bfs_dfs.txt";
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
	            fname = "../Tester/mst3.txt";
	            FEngine.insertElementsInGraph(fname, graph);
	            graph->adjList();

	            Kruskal krus(graph);
	            auto mst = krus.apply();
	            mst.adjList();
	            break;
	        }
	        case 3:
	        {
	            fname = "../Tester/mst3.txt";
	            FEngine.insertElementsInGraph(fname, graph);
	            Kruskal krus(graph);
	            krus.apply();
	            break;
	        }
	        case 4:
	        {
	            fname = "../Tester/mst1.txt";
                    FEngine.insertElementsInGraph(fname,graph);
                    AStar<tK,tV> a(graph,"A","H");
                    a.apply();
		    break;
	        }
	        case 5:
	        {
	            break;
	        }
	        case 6:
	        {
	            fname = "../Tester/dijkstra.txt";
	            FEngine.insertElementsInGraph(fname, graph);
	            Dijkstra<tK, tV> djkstr(graph);
	            for (const auto& [vertex, weight] : djkstr.run())
	                cout << vertex << " -> " << weight << endl;
	            break;
	        }
	        case 7:
	        {
	            fname = "../Tester/floyd.txt";
	            FEngine.insertElementsInGraph(fname, graph);
	            FloydWarshall<tK, tV> floyd(graph);
	            auto matrix = floyd.run();
	            for (const auto& [v1, row] : matrix)
	            {
	                cout << v1 << " -> ";
	                for (const auto& [v2, weight] : row)
	                    cout << "(" << v2 << ", " << weight << ") ";
	                cout << endl;
	            }
	            break;
	        }
	        default: break;
	    }
	}

	void runMenu()
	{
		auto ugraph = new UnDirectedGraph<tK, tV>();
	    auto dgraph = new DirectedGraph<tK, tV>();
		int typeG;

		//cout << __PRETTY_FUNCTION__ << endl;
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
