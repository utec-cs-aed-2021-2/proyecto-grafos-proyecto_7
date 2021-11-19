#ifndef PRIM_H
#define PRIM_H

#include "..\graph.h"
#include "../UndirectedGraph.h"
#include "queue"
#include <tuple>
using namespace std;

template<typename TE>
struct Compare{
    bool operator()(const tuple<TV, TE, TV>& tup1, const tuple<TV, TE, TV>& tup2){
        if(get<1>(tup1) > get<1>(tup2)){
            return true;
        }
        return false;
    }
};

template<typename TV, typename TE>
class Prim{
private:
	unordered_map<string, Vertex<TV, TE>*> vertices;
	unordered_map<Vertex<TV, TE>* , bool> visited;
	Vertex<TV, TE>* startV;
    int costo;
public:
	Prim() = default;
	Prim(UnDirectedGraph<TV, TE>* graph)
	{
		vertices = graph->vertexes;
		this->startV = (vertices.begin())->first;
		for (auto [k, v] : vertices)
			this->visited[v] = false;
	}

	Prim(UnDirectedGraph<TV, TE>* graph, Vertex<TV, TE>* startVertex = nullptr)
	{
		vertices = graph->vertexes;
		if (startVertex == nullptr)			// set first vertex
			startVertex = (vertices.begin())->second;		
		this->startV = startVertex;

		auto vertexInicio = vertices.begin();
		while (vertexInicio != vertices.end())				// iterate over all [k, v] in unordered_map
		{
			Vertex<TV, TE>* vertexIt = vertexInicio->second;
			this->visited[vertexIt] = false;		// initialize all as unvisited
			vertexInicio = next(vertexInicio);
		}	
	}

	UnDirectedGraph<TV,TE>* apply()
	{
		priority_queue<tuple<TV, TE, TV>, vector<tuple<TV ,TE, TV>>, Compare<TE>> cont;
		UnDirectedGraph<TV,TE>* primm = new UnDirectedGraph<TV,TE>;

		primm->insertVertex(this->startV->id, this->vertices[this->startV->id]->data);
		visited[this->startV] = true;


        Vertex<TV,TE>* temp = this->vertices[this->startV->id];
        for(auto i: temp->edges){
            Vertex<TV,TE>* auxiliar = i->vertexes[1];
			if(visited.find(auxiliar) == visited.end()){
                cont.push(make_tuple(i->data,i->weight,auxiliar->data));
            }
        }

        cost = 0;

		while (!cont.empty()){
            Vertex<TV,TE>* source = get<0>(cont.top());
            Vertex<TV,TE>* destiny = get<2>(cont.top());
            int costSD  = get<1>(cont.top());
            cont.pop();

            if(visited.find(destiny) == visited.end()){
                cost += costSD;
                visited[destiny] = true;
				primm->insertVertex(destiny->id, vertices[destiny->id]->data);
                primm->createEdge(source->id, destiny->id, costSD);
				Vertex<TV,TE>* tmp = vertices[destiny->id];

				for(auto i: tmp->edges){
                    Vertex<TV,TE>* aux = i->vertexes[1];
                    if(visited.find(aux) == visited.end()){
                        cont.push(make_tuple(destiny->id, i->weight, aux->id));
                    }
                }
            }
        }
		return primm;
	}
};

#endif
