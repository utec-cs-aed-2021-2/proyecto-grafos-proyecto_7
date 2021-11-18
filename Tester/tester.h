#ifndef TESTER_H
#define TESTER_H

#include <iostream>
#include <fstream>
#include <errno.h>
#include <string>
#include "../Graph/DirectedGraph.h"
#include "../Graph/UndirectedGraph.h"
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
	void executeExamples()
	{
		cout << __PRETTY_FUNCTION__ << endl;
	}

	void executeParser()
	{
		cout << __PRETTY_FUNCTION__ << endl;
	}

	void runMenu()
	{
		using tK = string;		// type key
		using tV = int;			// type value

		cout << __PRETTY_FUNCTION__ << endl;	
	    cout << "================================================" << endl;
	    cout << "MENU GRAPH TESTER" << endl;
	    cout << "================================================" << endl;
	    FileReader<tK, tV> FEngine;
	    DirectedGraph<tK, tV> TGraph;
	    string fname = "Tester/test_kruskal_undirected_1.txt";
	    FEngine.insertElementsInGraph(fname, &TGraph);
	    
	    //TGraph.displayVertex("A");
	    //TGraph.adjList();
	    //TGraph.deleteVertex("A");
	    //TGraph.adjList();
	    //TGraph.adjList();
	    //TGraph.deleteEdge("A", "B");
	    //TGraph.deleteEdge("D", "B");
	    TGraph.adjList();
	    //cout << boolalpha << TGraph.isConnected();
	    //TGraph.display();
	    cout << TGraph("D", "F") << endl;
	    TGraph.deleteEdge("D", "C");
	    TGraph.deleteVertex("E");
	    TGraph.adjList();
	}
}

#endif