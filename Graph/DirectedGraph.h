#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"

template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE>{

    public:
        DirectedGraph() = default;

        ~DirectedGraph();

        int numEdges = 0;

        DirectedGraph(string id, TV vertex){
            this->insertVertex(id, vertex);
        };

        bool findById(string id){
            if (this->vertexes.find(id) == this->vertexes.end()){
                return false;
            } return true;
        };

};

#endif
