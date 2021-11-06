#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{
    
    public:
        UnDirectedGraph() = default;
        
        ~UnDirectedGraph();

        int numEdges = 0;

        UnDirectedGraph(string id, TV vertex){
            this->insertVertex(id, vertex);
        };

        bool insertVertex(string id, TV vertex){
            if (this->vertexes.find(id) != this->vertexes.end()){
                return false; //encuentra otro vertice con el mismo id
            }
            Vertex<TV,TE>* newVertex = new Vertex<TV,TE>;
            newVertex->data = vertex;
            this->vertexes[id] = newVertex;

            return true;
        };

        bool createEdge(string id1, string id2, TE w){
            if (this->vertexes.find(id1) == this->vertexes.end() || this->vertexes.find(id2) == this->vertexes.end()){
                return false;
            }
            Edge<TV,TE>* newEdge1 = new Edge<TV,TE>;
            newEdge1->vertexes[0] = this->vertexes[id1];
            newEdge1->vertexes[1] = this->vertexes[id2];
            newEdge1->weight = w;

            Edge<TV,TE>* newEdge2 = new Edge<TV,TE>;
            newEdge2->vertexes[1] = this->vertexes[id1];
            newEdge2->vertexes[0] = this->vertexes[id2];
            newEdge2->weight = w;

            this->vertexes[id1]->edges.push_back(newEdge1);
            this->vertexes[id2]->edges.push_back(newEdge2);            
            
            numEdges++;
            
            return true;
        };

        bool findById(string id){
            if (this->vertexes.find(id) == this->vertexes.end()){
                return false;
            } return true;
        };

        TE &operator()(string start, string end){
            if (!findById(start)){ //no encuentra vertice
                throw("error");
            }

            auto aristas = this->vertexes[start]->edges; //std::list<Edge<TV, TE>*> //no se si el tipo es eso, falta probar
            for (auto it : aristas){
                //revisa cada par de vertices
                if (it->vertexes[0] == this->vertexes[end] || it->vertexes[1] == this->vertexes[end]){
                    //si es que encuentra una donde este el vertice end
                    return it->weight;
                }
            }

            //no encuentra arista
            throw("error");
        };

        bool empty(){
            return this->vertexes.size() == 0;
        }
};

#endif
