#ifndef TESTER_H
#define TESTER_H
#include <string>
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
#include "../Graph/Algorithms/bestBFS.h"
#include "../Graph/Algorithms/bellmanFord.h"
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
	using tV = double;			// type value

	void TesterrunAlgorithms(UnDirectedGraph<tK, tV>* graph)
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
	            fname = "../Tester/prim.txt";
	            FEngine.insertElementsInGraph(fname, graph);
	            Prim prim(graph, "A");
	            auto camino = prim.apply();
	            camino->adjList();
	            cout << "El coste del camino es " << prim.primmCosto() << endl;
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
	            fname = "../Tester/greedybfs.txt";
	            FEngine.insertElementsInGraph(fname, graph);
	            BestBFS bbfs(graph,"A", "B");
	            auto caminoCorto = bbfs.apply();
	            caminoCorto->adjList();
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

	void TesterrunAlgorithms(DirectedGraph<tK, tV>* graph)
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
	            fname = "../Tester/prim.txt";
	            FEngine.insertElementsInGraph(fname, graph);
	            Prim prim(graph, "A");
	            auto camino = prim.apply();
	            camino->adjList();
	            cout << "El coste del camino es " << prim.primmCosto() << endl;
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
	            fname = "../Tester/greedybfs.txt";
	            FEngine.insertElementsInGraph(fname, graph);
	            BestBFS bbfs(graph,"A", "B");
	            auto caminoCorto = bbfs.apply();
	            caminoCorto->adjList();
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
	        case 8:
	        {
	            cin >> input;
	            switch(input){
	                case 1:
	                {
	                    fname = "../Tester/bellman.txt";
	                    FEngine.insertElementsInGraph(fname, graph);
	                    BellmanFord<tK, tV> bell(graph, "E");
	                    if (!bell.hayNegCycle()){
	                        cout << "El camino más corto desde " << "E es" << ": " << endl;
	                        cout << "Vértice Peso" << endl;
	                        auto a = bell.apply();
	                        for (auto i : a) {
	                            cout << i.first << "\t" << i.second << endl;
	                        }
	                    }
	                    /*solucion https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
                        A                6
                        B                3
                        C                3
                        D                2
                        E                0
                        */
	                    break;
	                }
	                case 2:
	                {
	                    fname = "../Tester/bellman2.txt";
	                    FEngine.insertElementsInGraph(fname, graph);
	                    BellmanFord<tK, tV> bell(graph, "A");
	                    if (!bell.hayNegCycle()){
	                        cout << "El camino más corto desde " << "A es" << ": " << endl;
	                        cout << "Vértice Peso" << endl;
	                        auto a = bell.apply();
	                        for (auto i : a) {
	                            cout << i.first << "\t" << i.second << endl;
	                        }
	                    }
	                    /*solucion https://ycpcs.github.io/cs360-spring2019/lectures/lecture21.html
                        A                0
                        B                -1
                        C                2
                        D                -2
                        E                1
                        */
	                    break;
	                } default: break;
	            }
	            break;
	        }
	        default: break;
	    }
	}

    void ParserrunAlgorithms(UnDirectedGraph<tK, tV>* graph) {
        int input;
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
        switch (input) {
            case 1: {
                string label_id = "2789";
                graph->readJSON();
                uGraphMake(*graph);
                //graph->print();
                BFS tt1(graph, label_id);
                DFS tt2(graph, label_id);
                tt1.run([](Vertex<tK, tV> *current) {
                    cout << current << " ";
                });
                cout << endl;

                tt2.run([](Vertex<tK, tV> *current) {
                    cout << current << " ";
                });
                cout << endl;
                break;
            }
            case 2: {
                graph->readJSON();
                uGraphMake(*graph);
                graph->adjList();
                Kruskal krus(graph);
                auto mst = krus.apply();
                mst.adjList();
                break;
            }

            case 3: {
                graph->readJSON();
                uGraphMake(*graph);
                Prim prim(graph, "2786");
                auto camino = prim.apply();
                camino->adjList();
                cout << "El coste del camino es " << prim.primmCosto() << endl;
                break;
            }
            case 4: {
                graph->readJSON();
                uGraphMake(*graph);
                AStar<tK, tV> a(graph, "2786", "2812");
                a.apply();
                break;
            }
            case 5: {
                graph->readJSON();
                uGraphMake(*graph);
                BestBFS bbfs(graph, "2789", "6067");
                auto caminoCorto = bbfs.apply();
                caminoCorto->adjList();
                break;
            }
            case 6: {
                graph->readJSON();
                uGraphMake(*graph);
                Dijkstra<tK, tV> djkstr(graph);
                for (const auto&[vertex, weight]: djkstr.run())
                    cout << vertex << " -> " << weight << endl;
                break;
            }
            default:
                break;
        }
    }

    void ParserrunAlgorithms(DirectedGraph<tK, tV>* graph)
    {
        int input;
        cout << "================================================" << endl;
        cout << "MENU ALGORITHMS" << endl;
        cout << "================================================" << endl;
        cout << "1. BFS-DFS\n";
        cout << "2. Kruskal\n";
        cout << "3. Prim\n";
        cout << "4. AStar\n";
        cout << "5. BestBFS\n";
        cout << "6. Dijkstra\n";
        cout << "7. FloydWarshall\n";
        cout << "8. BellmanFord\n";
        cout << "================================================" << endl;
        cin >> input;
        switch (input)
        {
            case 1:
            {
                string label_id = "2789";
                graph->readJSON();
                dGraphMake(*graph);
                BFS tt1(graph, label_id);
                DFS tt2(graph, label_id);

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
                graph->readJSON();
                dGraphMake(*graph);
                graph->adjList();
                Kruskal krus(graph);
                auto mst = krus.apply();
                mst.adjList();
                break;
            }

            case 3:
            {
                graph->readJSON();
                dGraphMake(*graph);
                Prim prim(graph, "2786");
                auto camino = prim.apply();
                camino->adjList();
                cout << "El coste del camino es " << prim.primmCosto() << endl;
                break;
            }
            case 4:
            {
                graph->readJSON();
                dGraphMake(*graph);
                AStar<tK,tV> a(graph,"2786","2812");
                a.apply();
                break;
            }
            case 5:
            {
                graph->readJSON();
                dGraphMake(*graph);
                BestBFS bbfs(graph,"2789", "6067");
                auto caminoCorto = bbfs.apply();
                caminoCorto->adjList();
                break;
            }
            case 6:
            {
                graph->readJSON();
                dGraphMake(*graph);
                Dijkstra<tK, tV> djkstr(graph);
                for (const auto& [vertex, weight] : djkstr.run())
                    cout << vertex << " -> " << weight << endl;
                break;
            }
            case 7:
            {
                graph->readJSON();
                dGraphMake(*graph);
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
            case 8:
            {
                cin >> input;
                graph->readJSON();
                dGraphMake(*graph);
                switch(input){
                    case 1:
                    {
                        BellmanFord<tK, tV> bell(graph, "6067");
                        if (!bell.hayNegCycle()){
                            cout << "El camino más corto desde " << "E es" << ": " << endl;
                            cout << "Vértice Peso" << endl;
                            auto a = bell.apply();
                            for (auto i : a) {
                                cout << i.first << "\t" << i.second << endl;
                            }
                        }
                        /*solucion https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
                        A                6
                        B                3
                        C                3
                        D                2
                        E                0
                        */
                        break;
                    }
                    case 2:
                    {
                        BellmanFord<tK, tV> bell(graph, "6067");
                        if (!bell.hayNegCycle()){
                            cout << "El camino más corto desde " << "A es" << ": " << endl;
                            cout << "Vértice Peso" << endl;
                            auto a = bell.apply();
                            for (auto i : a) {
                                cout << i.first << "\t" << i.second << endl;
                            }
                        }
                        /*solucion https://ycpcs.github.io/cs360-spring2019/lectures/lecture21.html
                        A                0
                        B                -1
                        C                2
                        D                -2
                        E                1
                        */
                        break;
                    } default: break;
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
	    cout << "1. Undirected Tester\n";
	    cout << "2. Directed Tester \n";
        cout << "3. Undirected Parser\n";
        cout << "4. Directed Parser \n";
	    cout << "================================================" << endl;
	    cin >> typeG;
        switch (typeG) {
            case 1:
                TesterrunAlgorithms(ugraph);
                break;
            case 2:
                TesterrunAlgorithms(dgraph);
                break;
            case 3:
                ParserrunAlgorithms(ugraph);
                break;
            case 4:
                ParserrunAlgorithms(dgraph);
                break;
            default:
                break;
        }

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
