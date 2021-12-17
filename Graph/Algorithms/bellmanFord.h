#ifndef BELLMANFORD_H
#define BELLMANFORD_H
#include "../graph.h"
#include "../UndirectedGraph.h"
#include "../DirectedGraph.h"

#include <map>
using namespace std;

template<typename TV, typename TE>
class BellmanFord{
private:
    DirectedGraph<TV,TE>* graph;
    string start;
    bool cicloNegativo = false;
public:
    BellmanFord(DirectedGraph<TV, TE>* graph, string start)
    {
        this->graph = graph;
        this->start = start;
    };

    unordered_map<TV,TE> apply(){
        unordered_map<TV, TE> distancia;
        DirectedGraph<TV,TE>* result;

        for (auto i: graph->vertexes){
            distancia[i.first] = INF;
        } distancia[start] = 0;

        auto tmn = graph->vertexes.size();


        for(int i = 0; i < tmn - 1; i++){
            for (auto currVert : graph->vertexes){
                for (auto currEdge : currVert.second->edges){
                    string idS = currEdge->edgeVertexes[0]->id;
                    string idF = currEdge->edgeVertexes[1]->id;
                    auto peso = currEdge->weight;
                    
                    if (distancia[idS] != INF && (distancia[idS]+peso < distancia[idF]))
                    {
                        distancia[idF] = distancia[idS]+peso;
                    }
                }
            }
        }

        for (auto currVert : graph->vertexes){
            for (auto currEdge : currVert.second->edges){
                string idS = currEdge->edgeVertexes[0]->id;
                string idF = currEdge->edgeVertexes[1]->id;
                auto peso = currEdge->weight;

                if (distancia[idS] != INF && (distancia[idS]+peso < distancia[idF]))
                {
                    cout << "Grafo tiene ciclo de peso negativo";
                    this->cicloNegativo = true;
                    return unordered_map<TV,TE>();
                }
            }
        }
        return distancia;
    }

    bool hayNegCycle(){
        return cicloNegativo;
    }
};
// shortest path between two nodes in directed weighted graphs
#endif
