#ifndef DFS_H
#define DFS_H

#include "..\graph.h"
using namespace std;

template<typename TV, typename TE>
class DFS{
private:
	unordered_map<Vertex<TV, TE>* , bool> visited;
	Vertex<TV, TE>* startV;
public:
	DFS() = default;
	DFS(Graph<TV, TE>* graph)
	{
		auto un_map = graph->vertexes;
		this->startV = (un_map.begin())->second;
		for (auto [k, v] : un_map)
			this->visited[v] = false;
		//for (auto [k, v] : visited)
		//	cout << k->data << " -> " << v << endl;
	}
	DFS(umap_it<TV, TE> start, umap_it<TV, TE> end, Vertex<TV, TE>* startVertex = nullptr)
	{
		if (startVertex == nullptr)			// set first vertex
			startVertex = start->second;		
		this->startV = startVertex;

		while (start != end)				// iterate over all [k, v] in unordered_map
		{
			Vertex<TV, TE>* vertexIt = start->second;
			//cout << vertexIt->data << " ";
			this->visited[vertexIt] = false;		// initialize all as unvisited
			start = next(start);
		}
		//cout << '\n' << startVertex->data << '\n';
	}

	template<typename Op>
	void run(Op op)
	{
		//for (auto [k, v]: this->visited)
		//	cout << k->data << ": " << boolalpha << v << endl;
		stack<Vertex<TV, TE>*> st;
		st.push(this->startV);
		while (!st.empty())
		{
			auto currentV = st.top();
			st.pop();
			if (this->visited[currentV] == true)
				continue;	// verify if node already visited
			this->visited[currentV] = true;
			op(currentV);
			for (Edge<TV, TE>* edge : currentV->edges)
			{
				auto adj = edge->edgeVertexes[1];
				if (this->visited[adj] == false)
					st.push(adj);		//cout << '\t' << currentV->data << " - " << adj->data << endl;
			}
		}
	}
};

#endif