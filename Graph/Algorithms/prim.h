#ifndef PRIM_H
#define PRIM_H

#include "../graph.h"
#include "../UndirectedGraph.h"
#include "../DirectedGraph.h"

#include <map>
#include <queue>
#include <vector>
using namespace std;

using peso = double;
//peso, start y end 
using weightPar = pair<peso, pair<string, string>>; 

struct ComparatorPrim{
    bool operator()(const weightPar w1, const weightPar w2) const {
        return w1.first > w2.first;
    }
};


template<typename TV, typename TE>
class Prim{
private:
	int costo;
	UnDirectedGraph<TV,TE>* outGraph;
   
public:
	Prim() = default;
	Prim(UnDirectedGraph<TV, TE>* graph, string start)
	{
		if (!(graph->findById(start))) throw std::invalid_argument("node not found\n");

		priority_queue<weightPar,vector<weightPar>, ComparatorPrim> pq;        
		unordered_map<string, bool> visitados;
		
		for (auto i : graph->vertexes){
            visitados[i.first] = false;
        }
		outGraph = new UnDirectedGraph<TV,TE>;

		visitados[start] = true;
		outGraph->insertVertex(start, graph->vertexes[start]->data);

		Vertex<TV,TE>* auxVert = graph->vertexes[start];

		for(auto currEdge: auxVert->edges){
			Vertex<TV,TE>* currVert = currEdge->edgeVertexes[1];
			if(visitados[currVert->id] == false){
				pq.push(make_pair(currEdge->weight, make_pair(start,currVert->id)));
			}
		}
		costo = 0;

		while(!pq.empty()){
			string idS = pq.top().second.first;
			string idF = pq.top().second.second;
			auto peso = pq.top().first;

			pq.pop();

			if(visitados[idF] == false){
				costo += peso;
				visitados[idF] = true;
				outGraph->insertVertex(idF, graph->vertexes[idF]->data);
				outGraph->createEdge(idS, idF, peso);
				Vertex<TV,TE>* vertStart = graph->vertexes[idF];
				for (auto currEdge: vertStart->edges){
					Vertex<TV,TE>* currVert = currEdge->edgeVertexes[1];
					if (visitados[currVert->id] == false){
						pq.push(make_pair(currEdge->weight, make_pair(vertStart->id, currVert->id)));
					}
				}
			}
		}
	}

	Prim(DirectedGraph<TV, TE>* graph, string start)
	{
		if (!(graph->findById(start))) throw std::invalid_argument("node not found\n");

		priority_queue<weightPar,vector<weightPar>, ComparatorPrim> pq;        
		unordered_map<string, bool> visitados;
		for (auto i : graph->vertexes){
            visitados[i.first] = false;
        }
		outGraph = new UnDirectedGraph<TV,TE>;	

		visitados[start] = true;
		outGraph->insertVertex(start, graph->vertexes[start]->data);

		Vertex<TV,TE>* auxVert = graph->vertexes[start];

		for(auto currEdge: auxVert->edges){
			Vertex<TV,TE>* currVert = currEdge->edgeVertexes[1];
			if(visitados[currVert->id] == false){
				pq.push(make_pair(currEdge->weight, make_pair(start,currVert->id)));
			}
		}
		costo = 0;

		while(!pq.empty()){
			string idS = pq.top().second.first;
			string idF = pq.top().second.second;
			auto peso = pq.top().first;

			pq.pop();

			if(visitados[idF] == false){
				costo += peso;
				visitados[idF] = true;
				outGraph->insertVertex(idF, graph->vertexes[idF]->data);
				outGraph->createEdge(idS, idF, peso);
				Vertex<TV,TE>* vertStart = graph->vertexes[idF];

				for (auto currEdge: vertStart->edges){
					Vertex<TV,TE>* currVert = currEdge->edgeVertexes[1];
					if (visitados[currVert->id] == false){
						pq.push(make_pair(currEdge->weight, make_pair(vertStart->id, currVert->id)));
					}
				}
			}
		}
	}

	Prim(Graph<TV, TE>* graph, string start)
	{
		if (!(graph->findById(start))) throw std::invalid_argument("node not found\n");

		priority_queue<weightPar,vector<weightPar>, ComparatorPrim> pq;        
		unordered_map<string, bool> visitados;
		for (auto i : graph->vertexes){
            visitados[i.first] = false;
        }
		outGraph = new UnDirectedGraph<TV,TE>;	

		visitados[start] = true;
		outGraph->insertVertex(start, graph->vertexes[start]->data);

		Vertex<TV,TE>* auxVert = graph->vertexes[start];

		for(auto currEdge: auxVert->edges){
			Vertex<TV,TE>* currVert = currEdge->edgeVertexes[1];
			if(visitados[currVert->id] == false){
				pq.push(make_pair(currEdge->weight, make_pair(start,currVert->id)));
			}
		}
		costo = 0;

		while(!pq.empty()){
			string idS = pq.top().second.first;
			string idF = pq.top().second.second;
			auto peso = pq.top().first;

			pq.pop();

			if(visitados[idF] == false){
				costo += peso;
				visitados[idF] = true;
				outGraph->insertVertex(idF, graph->vertexes[idF]->data);
				outGraph->createEdge(idS, idF, peso);
				Vertex<TV,TE>* vertStart = graph->vertexes[idF];

				for (auto currEdge: vertStart->edges){
					Vertex<TV,TE>* currVert = currEdge->edgeVertexes[1];
					if (visitados[currVert->id] == false){
						pq.push(make_pair(currEdge->weight, make_pair(vertStart->id, currVert->id)));
					}
				}
			}
		}
	}

	int primmCosto(){
		return costo;
	}

	UnDirectedGraph<TV,TE>* apply()
	{
		return outGraph;
	}

};

#endif
