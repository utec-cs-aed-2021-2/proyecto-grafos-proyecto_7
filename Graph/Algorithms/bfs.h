#ifndef BFS_H
#define BFS_H

#include "..\graph.h"
using namespace std;

template<typename TV, typename TE>
class BFS{
private:
	unordered_map<Vertex<TV, TE>* , bool> visited;
	Vertex<TV, TE>* startV;
public:
	BFS() = default;
	BFS(Graph<TV, TE>* graph)
	{
		auto un_map = graph->vertexes;
		this->startV = (un_map.begin())->second;
		for (auto [k, v] : un_map)
			this->visited[v] = false;
		//for (auto [k, v] : visited)
		//	cout << k->data << " -> " << v << endl;
	}

	BFS(Graph<TV, TE>* graph, TV dataId)
	{
		auto un_map = graph->vertexes;
		for (auto [k, v] : un_map)
		{
			if (v->data == dataId)
				this->startV = v;
			this->visited[v] = false;
		}
		//for (auto [k, v] : visited)
		//	cout << k->data << " -> " << v << endl;
	}

	BFS(umap_it<TV, TE> start, umap_it<TV, TE> end, Vertex<TV, TE>* startVertex = nullptr)
	{
		if (startVertex == nullptr)			// set first vertex
			startVertex = start->second;		
		this->startV = startVertex;

		while (start != end)				// iterate over all [k, v] in unordered_map
		{
			Vertex<TV, TE>* vertexIt = start->second;
			//cout << vertexIt->data << " ";
			visited[vertexIt] = false;		// initialize all as unvisited
			start = next(start);
		}
		//cout << '\n' << startVertex->data << '\n';
	}

	void setInitialVertex(Vertex<TV, TE>* startVV)
	{
		this->startV = startVV;
	}

	template<typename Op>
	void run(Op op)
	{
		//for (auto [k, v]: this->visited)
		//	cout << k->data << ": " << boolalpha << v << endl;
		queue<Vertex<TV, TE>*> qu;
		qu.push(this->startV);
		while (!qu.empty())
		{
			auto currentV = qu.front();
			qu.pop();
			if (this->visited[currentV] == true)
				continue;	// verify if node already visited
			this->visited[currentV] = true;
			op(currentV);
			for (Edge<TV, TE>* edge : currentV->edges)
			{
				auto adj = edge->edgeVertexes[1];
				if (this->visited[adj] == false)
					qu.push(adj);		//cout << '\t' << currentV->data << " - " << adj->data << endl;
			}
		}
	}
};


#endif
