#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <algorithm>
#include "..\graph.h"
#include "..\Structures\dsarray.h"

template<typename TV, typename TE>
class Kruskal{
	vector<Edge<TV, TE>*> vEdges;
	vector<Vertex<TV, TE>*> vNodes;
	DisjoinSetArray<Vertex<TV, TE>*>* ds = nullptr;
	unordered_map<Vertex<TV, TE>*, int> posVertex;
public:
	Kruskal(Graph<TV, TE>* graph)
	{
		for (auto [id, vertex] : graph->vertexes)
		{
			vNodes.push_back(vertex);
			for (Edge<TV, TE>* ed : vertex->edges)
				vEdges.push_back(ed);		// add edges on std::vector
		}
		this->ds = new DisjoinSetArray<Vertex<TV, TE>*>(this->vNodes);
		int idx = 0;
		for (auto node : this->vNodes)			// initialize position hash
			posVertex[node] = idx++;
	}
	~Kruskal()
	{
		vEdges.clear(); posVertex.clear();
	}

	UnDirectedGraph<TV, TE> apply()
	{
		vector<Edge<TV, TE>*> nEdges;
		sort(vEdges.begin(), vEdges.end(), [](Edge<TV, TE>* e1, Edge<TV, TE>* e2){
			return e1->weight < e2->weight;
		});
		//for (auto ed: vEdges)	cout << ed << '\n';	cout << '\n';
		//for (auto [k, idx] : posVertex) cout << k->data << " -> " << idx << endl;

		for (Edge<TV, TE>* ed: vEdges)
		{
			auto posFNode = posVertex[ed->edgeVertexes[0]];
			auto posSNode = posVertex[ed->edgeVertexes[1]];
			if (!ds->isConnected(posFNode, posSNode))
			{
				nEdges.push_back(ed);
				ds->Union(posFNode, posSNode);
			}
		}
		auto mstResult = new UnDirectedGraph<TV, TE>();
		for (auto v : this->vNodes)
			mstResult->insertVertex(v->data, v->data);
		for (auto ed: nEdges)
		{	// cout << ed << '\n';
			auto id1 = ed->edgeVertexes[0]->data;
			auto id2 = ed->edgeVertexes[1]->data;
			mstResult->createEdge(id1, id2, ed->weight);
		}
			
		return *mstResult;
	}
};

#endif

