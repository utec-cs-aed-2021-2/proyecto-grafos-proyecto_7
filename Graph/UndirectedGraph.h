#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"
#include "Algorithms\dfs.h"
#include "Algorithms\bfs.h"
template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{
    friend void uGraphMake(UnDirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified undirected graph
    public:
        UnDirectedGraph() = default;
        ~UnDirectedGraph() = default;       

        UnDirectedGraph(string id, TV vertex)
        {
            this->insertVertex(id, vertex);
        }

        bool insertVertex(string id, TV vertex)
        {   
            // check if node already exists
            if (this->vertexes.find(id) != this->vertexes.end())
                return false; 
            
            // create and insert node in std::unordered_map
            Vertex<TV,TE>* newVertex = new Vertex<TV,TE>();
            newVertex->data = vertex;
            newVertex->id = id;
            this->vertexes[id] = newVertex;
            return true;
        }

        bool createEdge(string id1, string id2, TE w)
        {   
            // check if nodes don't exist
            if (this->vertexes.find(id1) == this->vertexes.end() || this->vertexes.find(id2) == this->vertexes.end())
                return false;
            
            // create bidirectional edges
            Edge<TV,TE>* newEdge1 = new Edge<TV,TE>();
            newEdge1->edgeVertexes[0] = this->vertexes[id1];
            newEdge1->edgeVertexes[1] = this->vertexes[id2];
            newEdge1->weight = w;
            
            Edge<TV,TE>* newEdge2 = new Edge<TV,TE>();
            newEdge2->edgeVertexes[0] = this->vertexes[id2];
            newEdge2->edgeVertexes[1] = this->vertexes[id1];
            newEdge2->weight = w;

            // add edges
            this->vertexes[id1]->edges.push_back(newEdge1);
            this->vertexes[id2]->edges.push_back(newEdge2);            
            
            this->numEdges++;
            return true;
        }

        bool deleteVertex(string id)
        {
            for(auto &i: this->vertexes){
                for(auto &j: i.second->edges){
                    if(j->edgeVertexes[1] == this->vertexes[id]){
                        i.second->edges.remove(j);
                        break;
                    }
                }
            }
            this->vertexes.erase(id);
            this->numVertexes--;
            return true;
        }

        bool deleteEdge(string id1, string id2)
        {
            if(this->vertexes.find(id1) == this->vertexes.end() || this->vertexes.find(id2) == this->vertexes.end())
                return false;
            for(auto &i: this->vertexes[id1]->edges){
                if(i->edgeVertexes[1]->data == this->vertexes[id2]->data){
                    this->vertexes[id1]->edges.remove(i);
                    break;
                }
            }
            for(auto &i: this->vertexes[id2]->edges){
                if(i->edgeVertexes[1]->data == this->vertexes[id1]->data){
                    this->vertexes[id2]->edges.remove(i);
                }
                break;
            }
            this->numEdges--;
            return true;
        }

        bool findById(string id)
        {
            if (this->vertexes.find(id) == this->vertexes.end())
                return false;
            return true;
        }

        TE &operator()(string start, string end)
        {
            if (!findById(start))
                throw std::invalid_argument("invalid start node\n");

            auto aristas = this->vertexes[start]->edges; //std::list<Edge<TV, TE>*> //no se si el tipo es eso, falta probar
            for (auto it : aristas){
                //revisa cada par de vertices -> se puede verificar solo la componente[1]
                if (it->edgeVertexes[0] == this->vertexes[end] || it->edgeVertexes[1] == this->vertexes[end])
                    return it->weight;      //si es que encuentra una donde este el vertice end
            }
            // no encuentra arista
            throw std::invalid_argument("end node not found\n");
        }

        float density()
        {
            return (2 * this->numEdges)/(this->numVertexes * (this->numVertexes - 1));
        }

        bool isDense(float threshold = 0.5)
        {
            return this->density() > threshold;
        } 

        bool isConnected()
        {
            BFS<TV, TE> treeTraversal(this);
            //DFS<TV, TE> treeTraversal(this->vertexes.begin(), this->vertexes.end());
            int visitedNodes = 0;
            treeTraversal.run([&visitedNodes](Vertex<TV, TE>* currentVertex){
                cout << currentVertex->data << " ";
                visitedNodes++;
            });
            if (visitedNodes == this->vertexes.size())
                return true;
            return false;
        }

        bool isStronglyConnected(){ 
            throw std::runtime_error("funcion invalida\n");
        }
        bool empty()
        {
            return this->numEdges == 0 && this->numVertexes == 0;
        }

        void clear()
        {
            for(auto &[k,v]: this->vertexes){
                v->edges.clear();
            }
            this->numEdges = 0;
            this->vertexes.clear();
            this->numVertexes = 0;
        }
      
        void displayVertex(string id)
        {
            for(auto &i: this->vertexes){
                if(i.first == id)
                    for(auto &j:i.second->edges){
                        cout << j->edgeVertexes[0]->data << "-" << j->edgeVertexes[1]->data << ", weight: " << j->weight<< endl;
                    }
            }
        }

        void display()
        {
            for(auto &i: this->vertexes){
                cout << "Para el vertice " << i.first << " :" << endl;
                for(auto &j:i.second->edges){
                    cout << j->edgeVertexes[0]->data << "-" << j->edgeVertexes[1]->data << ", weight: " << j->weight << endl;
                }
                cout << endl;
            }
        }

        void adjList()
        {
            for (auto [k, v]: this->vertexes)
            {
                cout << v->data << ": ";
                for (Edge<TV, TE>* ed : v->edges)
                    cout << " ("<< ed->edgeVertexes[1]->data << " " << ed->weight << ") ";
                cout << endl;
            }
            cout << endl;
        }
};

#endif
