#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template<typename TV, typename TE>
struct Edge;

template<typename TV, typename TE>
struct Vertex;

template<typename TV, typename TE>
class Graph;

//////////////////////////////////////////////////////

template<typename TV, typename TE>
struct Edge {
    Vertex<TV, TE>* vertexes[2];    
    TE weight;

    Edge() = default;
    Edge(Vertex<TV, TE>* source, Vertex<TV, TE>* destiny, TE w)
    {
        this->vertexes[0] = source;
        this->vertexes[1] = destiny;
        this->weight = w;
    }
};

template<typename TV, typename TE>
struct Vertex {
    TV data;
    std::list<Edge<TV, TE>*> edges;

    Vertex(TV d):data{d}{};

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
private:    
    std::unordered_map<string, Vertex<TV, TE>*>  vertexes;
    int numEdges = 0;
    int numVertexes = 0;
public:
    virtual bool insertVertex(string id, TV vertex) = 0;   
    virtual bool createEdge(string id1, string id2, TE w) = 0;     
    virtual bool deleteVertex(string id) = 0;     
    virtual bool deleteEdge(string id) = 0;   
    virtual TE &operator()(string start, string end)= 0;  
    virtual float density() = 0;
    virtual bool isDense(float threshold = 0.5) = 0;
    virtual bool isConnected() = 0;
    bool isStronglyConnected() throw();
    virtual bool empty() = 0;
    virtual void clear() = 0;  
      
    virtual void displayVertex(string id) = 0;
    virtual bool findById(string id) = 0;
    virtual void display() = 0;

    ~Graph() = default;
};

#endif
