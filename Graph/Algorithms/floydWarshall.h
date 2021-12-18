#ifndef FLOYDWARSHALL_H
#define FLOYDWARSHALL_H

#include "../graph.h"
using namespace std;

template<typename TV, typename TE>
class FloydWarshall{
    map<Vertex<TV, TE>*, map<Vertex<TV, TE>*, TE>> dist;
public:
    FloydWarshall(DirectedGraph<TV, TE>* graph)
    {
        for (const auto& v1 : graph->vertexes)
            for (const auto& v2 : graph->vertexes)
                this->dist[v1.second][v2.second] = (*graph->vertexes[v1.first])[v2.second];
        for (const auto& v1 : graph->vertexes)
            for (const auto& v2 : graph->vertexes)
                for (const auto& v3 : graph->vertexes)
                    if (dist[v1.second][v2.second] < INF && dist[v3.second][v2.second] < INF)
                        this->dist[v1.second][v2.second] = min(dist[v1.second][v2.second], dist[v1.second][v3.second] + dist[v3.second][v2.second]);
    }
    auto run(){ return this->dist; }
};
// shortest path between two nodes in directed weighted graphs
#endif
