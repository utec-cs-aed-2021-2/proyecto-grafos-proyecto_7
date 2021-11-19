#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"
#include "Algorithms\dfs.h"
#include "Algorithms\bfs.h"
template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE>{

    public:
        DirectedGraph() = default;

        ~DirectedGraph() = default;

        DirectedGraph(string id, TV vertex){
            this->insertVertex(id, vertex);
        }

        bool insertVertex(string id, TV vertex)
        {
            if(this->vertexes.find(id) != this->vertexes.end())
                return false;
            Vertex<TV,TE>* newVertex = new Vertex<TV,TE>();
            newVertex->data = vertex;
            this->vertexes[id] = newVertex;
            this->numVertexes++;
            return true;
        }   

        bool createEdge(string id1, string id2, TE w)
        {
            if (this->vertexes.find(id1) == this->vertexes.end() || 
                this->vertexes.find(id2) == this->vertexes.end())
                return false;
    
            Edge<TV,TE>* newEdge = new Edge<TV,TE>();
            newEdge->weight = w;
            newEdge->edgeVertexes[0] = this->vertexes[id1];
            newEdge->edgeVertexes[1] = this->vertexes[id2];
            this->vertexes[id1]->edges.push_back(newEdge);
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
            return true;
        }     

        bool deleteEdge(string id1, string id2)
        {
            if (this->vertexes.find(id1) == this->vertexes.end() || 
                this->vertexes.find(id2) == this->vertexes.end())
                return false;
            for(auto &i: this->vertexes[id1]->edges){
                if(i->edgeVertexes[1]->data == this->vertexes[id2]->data){
                    this->vertexes[id1]->edges.remove(i);
                    break;
                }
            }
            return true;
        }   

        TE& operator()(string start, string end)
        {
            if (this->vertexes.find(start) == this->vertexes.end() || 
                this->vertexes.find(end) == this->vertexes.end())
                throw std::invalid_argument("inexistent node(s)\n");
            for (Edge<TV, TE>* ed : this->vertexes[start]->edges)
                if (ed->edgeVertexes[1]->data == this->vertexes[end]->data)
                    return ed->weight;
            throw std::invalid_argument("inexistent edge\n");
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
            umap_it<TV, TE> it1 = this->vertexes.begin();
            unordered_map<TV, bool> vis1;
            unordered_map<TV, bool> vis2;
            DirectedGraph<TV, TE> dgraph;
            for (auto [k, n] : this->vertexes)
            {
                vis1[n->data] = vis2[n->data] = false; 
                dgraph.insertVertex(n->data, n->data);
            }
            for (auto [k, n] : this->vertexes)
            {
                for (auto ed : n->edges)
                    dgraph.createEdge(ed->edgeVertexes[1]->data, ed->edgeVertexes[0]->data, ed->weight);
            }

            this->adjList();
            dgraph.adjList();

            DFS<TV, TE> treeTraversal1(this);
            treeTraversal1.run([&vis1](auto currentVertex){
                vis1[currentVertex->data] = true;
            });

            DFS<TV, TE> treeTraversal2(&dgraph);
            treeTraversal2.run([&vis2](auto currentVertex){
                vis2[currentVertex->data] = true;
            });

            for (auto [k, v]: vis1)
            {
                if ( (v | vis2[k]) == false )
                    return false;
            }
            return true;
        }

        bool empty()
        {
            return this->numEdges == 0 && this->numVertexes == 0;
        }

        bool isStronglyConnected()
        {
            if (this->empty())
                return false;

            for (auto [k, v] : this->vertexes){
                DFS<TV, TE> treeTraversal(this->vertexes.begin(), this->vertexes.end(), v);
                int visitedNodes = 0;
                treeTraversal.run([&visitedNodes](Vertex<TV, TE>* currentVertex){
                    cout << currentVertex->data << " ";
                    visitedNodes++;
                }); cout << endl;
                if (visitedNodes != this->vertexes.size())
                    return false;
            }
            return true;
        }

        void clear()
        {
            for (auto [k, v] : this->vertexes)
                v->edges.clear();
            this->numEdges = 0;
            this->vertexes.clear();
            this->numVertexes = 0;
        }  
          
        void displayVertex(string id)
        {

        }

        bool findById(string id)
        {
            if (this->vertexes.find(id) == this->vertexes.end())
                return false;
            return true;
        }

        void display()
        {

        }

        void adjList()
        {
            //for (auto [k, v]: this->vertexes)
            //    cout << v->data << " ";
            //cout << endl;
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

