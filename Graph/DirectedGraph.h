#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"

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
    
            Edge<TV,TE>* newEdge = new Edge<TV,TE>;
            newEdge->weight = w;
            newEdge->edgeVertexes[0] = id1;
            newEdge->edgeVertexes[1] = id2;
            this->vertexes[id1]->edges.push_back(newEdge);
            this->numEdges++;
            return true;
        }     

        bool deleteVertex(string id)
        {

        }     

        bool deleteEdge(string id1, string id2)
        {

        }   

        TE &operator()(string start, string end)
        {

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

        }

        bool isStronglyConnected()
        {

        }

        bool empty()
        {

        }

        void clear()
        {

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
