
#include <parser.h>

template<typename TV, typename TE>
string fillJSONVertex(Vertex<TV, TE>* ver, json::iterator jIt)
{
    string id;
    for (auto& [key, value]: jIt->items())
    {
        if (key == "airport_id")
            id = value;
        if (key != "destinations")
            std::cout << key << " ";
        //if (key == "Longitude")
        //    this->longitude = value;
    }
    return id;
}

void uGraphMake(UnDirectedGraph<string, double> &tempGraph)
{
    // llenar vertices + insertar vertice en grafo
    // por cada vertice generar sus aristas a partir del atributo destinatios que sera el id del umap del grafo
        //adj[a].push_back({b, w});
        //adj[b].push_back({a, w});
}   // Adds the parsed data into the specified undirected graph

void dGraphMake(DirectedGraph<string, double> &tempGraph)
{
    // iterate over array
    for (json::iterator it = tempGraph.file.begin(); it != tempGraph.file.end(); ++it)
    {   // STL-like access
        auto nodo = new Vertex<string, double>();
        tempGraph.addVertex(fillJSONVertex(nodo, it), nodo);
    }
    // llenar vertices + insertar vertice en grafo
    // por cada vertice generar sus aristas a partir del atributo destinatios que sera el id del umap del grafo
        //adj[a].push_back({b, w});
}   // Adds the parsed data into the specified directed graph