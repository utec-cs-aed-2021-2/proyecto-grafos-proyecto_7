#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../graph.h"

using namespace std;

template<typename TV, typename TE>
class Dijkstra{
    map<Vertex<TV, TE>*, TE> dist;

    void run(Graph<TV, TE>* graph, Vertex<TV, TE>* source)
    {
        auto comparer = [](pair<TE, Vertex<TV, TE>*> p1, pair<TE, Vertex<TV, TE>*> p2){
            return p1.first > p2.first;
        };
        priority_queue<pair<TE, Vertex<TV, TE>*>, vector<pair<TE, Vertex<TV, TE>*>>, decltype(comparer) > pq(comparer, vector<pair<TE, Vertex<TV, TE>*>>());
        for (const auto& [id, vertex] : graph->vertexes)
            this->dist[vertex] = INF;
        pq.push({0, source});
        this->dist[source] = 0;

        while (!pq.empty())
        {
            Vertex<TV, TE>* curr = pq.top().second;
            TE curr_d = pq.top().first;
            pq.pop();

            for (const auto& ed : curr->edges)
            {
                auto src = ed->edgeVertexes[1];
                if (curr_d + ed->weight < this->dist[src])
                {
                    dist[src] = curr_d + ed->weight;
                    pq.push({dist[src], src});
                }
            }
        }
    }
public:
    Dijkstra(Graph<TV, TE>* graph){
        Vertex<TV, TE>* start;
        for (auto [id, vertex] : graph->vertexes)
        {
            if (id == "1")
            {
                start = vertex;
                break;
            }
        }

        run(graph, start);
    }
    Dijkstra(Graph<TV, TE>* graph, Vertex<TV, TE>* source){
        run(graph, source);
    }


    map<Vertex<TV, TE>*, TE> run(){ return dist; }
};
// shortest path between nodes in graph
#endif