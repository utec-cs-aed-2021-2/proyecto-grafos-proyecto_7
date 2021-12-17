#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <iterator>
#include <algorithm>
using namespace std;

template<typename TV, typename TE>
struct Edge;

template<typename TV, typename TE>
struct Vertex;

template<typename TV, typename TE>
class Graph;

template<typename TV, typename TE>
using umap_it = typename unordered_map<string, Vertex<TV, TE>*>::iterator;

//////////////////////////////////////////////////////

template<typename TV, typename TE>
struct Edge {
    Vertex<TV, TE>* edgeVertexes[2];    
    TE weight;

    Edge() = default;
    Edge(Vertex<TV, TE>* source, Vertex<TV, TE>* destiny, TE w)
    {
        this->edgeVertexes[0] = source;
        this->edgeVertexes[1] = destiny;
        this->weight = w;
    }
};

template<typename TV, typename TE>
ostream& operator << (ostream& os, Edge<TV, TE>* ed)
{
    os << " ("<< ed->edgeVertexes[0]->data << " " << ed->weight << " " << ed->edgeVertexes[1]->data << ")";
    return os;
}

template<typename TV, typename TE>
struct Vertex {
    TV data;
    string id;
    std::list<Edge<TV, TE>*> edges;
    Vertex() = default;
    Vertex(TV d, string id_){
        data = d;
        id = id_;
    };

    // add an edge in a graph 
    void addEdge(Vertex<TV, TE>* source, Vertex<TV, TE>* destiny, TE w)
    {   
        edges.push_back(new Edge<TV, TE>(source, destiny, w));
    }
    // add an edge in a graph (arg source is "this" pointer by default)
    void addEdge(Vertex<TV, TE>* destiny, TE w)
    {
        edges.push_back(new Edge<TV, TE>(this, destiny, w));
    }
    // std :: emplace_back () could be used, but to make it easier to read and 
    // initialize in heap, we'll use std :: push_back ()
};

template<typename TV, typename TE>
class Graph{
    template<typename TV1, typename TE1> friend class DFS;
    template<typename TV2, typename TE2> friend class BFS;
    template<typename TV3, typename TE3> friend class Kruskal;
    template<typename TV4, typename TE4> friend class Prim;
    template<typename TV5, typename TE5> friend class AStar;
    template<typename TV6, typename TE6> friend class Dijkstra;
    template<typename TV7, typename TE7> friend class BestBFS;
    template<typename TV8, typename TE8> friend class BellmanFord;
    template<typename TV9, typename TE9> friend class FloydWarshall;
protected:
    std::unordered_map<string, Vertex<TV, TE>*>  vertexes;
    int numEdges = 0;
    int numVertexes = 0;
public:
    virtual bool insertVertex(string id, TV vertex) = 0;   
    virtual bool createEdge(string id1, string id2, TE w) = 0;     
    virtual bool deleteVertex(string id) = 0;     
    virtual bool deleteEdge(string id1, string id2) = 0;   
    virtual TE &operator()(string start, string end)= 0;  
    virtual float density() = 0;
    virtual bool isDense(float threshold = 0.5) = 0;
    virtual bool isConnected() = 0;
    virtual bool isStronglyConnected() = 0;
    virtual bool empty() = 0;
    virtual void clear() = 0;  
      
    virtual void displayVertex(string id) = 0;
    virtual bool findById(string id) = 0;
    virtual void display() = 0;
    virtual void adjList() = 0;
    ~Graph() = default;
};
template<typename TV, typename TE> ostream& operator<<(ostream& os, Vertex<TV, TE>* vertex)
{
    os << vertex->id << " "; return os;
}
#endif
