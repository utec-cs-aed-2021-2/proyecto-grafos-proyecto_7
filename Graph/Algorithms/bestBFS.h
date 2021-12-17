#ifndef BESTBFS_H
#define BESTBFS_H

#include "..\graph.h"
#include "../UndirectedGraph.h"

#include <map>
#include <queue>
#include <vector>
using namespace std;


using peso = double;
//peso, start y end 
using weightPar = pair<peso, pair<string, string>>; 

struct Comparator{
    bool operator()(const weightPar w1, const weightPar w2) const {
        return w1.first > w2.first;
    }
};


template<typename TV, typename TE>
class BestBFS{
private:
    DirectedGraph<TV,TE>* outGraph;

public:
    BestBFS() = default;

    BestBFS(Graph<TV,TE>* graph, string start, string end){
        if (!(graph->findById(start)) || !(graph->findById(end))) throw std::invalid_argument("one or both nodes not found\n");

        unordered_map<string, bool> visitados;

        for (auto i : graph->vertexes){
            visitados[i.first] = false;
        }
        //weightpar = weight, start, end
        priority_queue<weightPar,vector<weightPar>, Comparator> pq;        


        pq.push(make_pair(0,make_pair(start,"")));

        outGraph = new DirectedGraph<TV,TE>;
        outGraph->insertVertex(start, graph->vertexes[start]->data);
        
        visitados[start] = true;

        while(!pq.empty()){
            string idF = "";
            if (pq.top().second.second == ""){
                idF = pq.top().second.first;
            } else{
                idF = pq.top().second.second;
            }

            string idS = pq.top().second.first;
            auto weight = pq.top().first;
            Vertex<TV,TE>* vertStart = graph->vertexes[idF];

            if (idF != "" && (visitados[vertStart->id] == false)){
                visitados[vertStart->id] = true;
                outGraph->insertVertex(idF, vertStart->data);
                outGraph->createEdge(idS,idF, weight);
            }
            
            pq.pop();

            if (idS == end) break;

            for (auto currEdge : vertStart->edges){
                Vertex<TV,TE>* currVert = currEdge->edgeVertexes[1];
                if (visitados[currVert->id] == false){
                    pq.push(make_pair(currEdge->weight, make_pair(vertStart->id, currVert->id)));
                }
            }
        }
    }

    BestBFS(UnDirectedGraph<TV,TE>* graph, string start, string end){
        if (!(graph->findById(start)) || !(graph->findById(end))) throw std::invalid_argument("one or both nodes not found\n");

        unordered_map<string, bool> visitados;

        for (auto i : graph->vertexes){
            visitados[i.first] = false;
        }
        //weightpar = weight, start, end
        priority_queue<weightPar,vector<weightPar>, Comparator> pq;        


        pq.push(make_pair(0,make_pair(start,"")));

        outGraph = new DirectedGraph<TV,TE>;
        outGraph->insertVertex(start, graph->vertexes[start]->data);
        
        visitados[start] = true;

        while(!pq.empty()){
            string idF = "";
            if (pq.top().second.second == ""){
                idF = pq.top().second.first;
            } else{
                idF = pq.top().second.second;
            }

            string idS = pq.top().second.first;
            auto weight = pq.top().first;
            Vertex<TV,TE>* vertStart = graph->vertexes[idF];

            if (idF != "" && (visitados[vertStart->id] == false)){
                visitados[vertStart->id] = true;
                outGraph->insertVertex(idF, vertStart->data);
                outGraph->createEdge(idS,idF, weight);
            }
            
            pq.pop();

            if (idS == end) break;

            for (auto currEdge : vertStart->edges){
                Vertex<TV,TE>* currVert = currEdge->edgeVertexes[1];
                if (visitados[currVert->id] == false){
                    pq.push(make_pair(currEdge->weight, make_pair(vertStart->id, currVert->id)));
                }
            }
        }
    }

    BestBFS(DirectedGraph<TV,TE>* graph, string start, string end){
        if (!(graph->findById(start)) || !(graph->findById(end))) throw std::invalid_argument("one or both nodes not found\n");

        unordered_map<string, bool> visitados;

        for (auto i : graph->vertexes){
            visitados[i.first] = false;
        }
        //weightpar = weight, start, end
        priority_queue<weightPar,vector<weightPar>, Comparator> pq;        


        pq.push(make_pair(0,make_pair(start,"")));

        outGraph = new DirectedGraph<TV,TE>;
        outGraph->insertVertex(start, graph->vertexes[start]->data);
        
        visitados[start] = true;

        while(!pq.empty()){
            string idF = "";
            if (pq.top().second.second == ""){
                idF = pq.top().second.first;
            } else{
                idF = pq.top().second.second;
            }

            string idS = pq.top().second.first;
            auto weight = pq.top().first;
            Vertex<TV,TE>* vertStart = graph->vertexes[idF];

            if (idF != "" && (visitados[vertStart->id] == false)){
                visitados[vertStart->id] = true;
                outGraph->insertVertex(idF, vertStart->data);
                outGraph->createEdge(idS,idF, weight);
            }
            
            pq.pop();

            if (idS == end) break;

            for (auto currEdge : vertStart->edges){
                Vertex<TV,TE>* currVert = currEdge->edgeVertexes[1];
                if (visitados[currVert->id] == false){
                    pq.push(make_pair(currEdge->weight, make_pair(vertStart->id, currVert->id)));
                }
            }
        }
    }

    DirectedGraph<TV,TE>* apply() {
        return outGraph;
    }

};

#endif
