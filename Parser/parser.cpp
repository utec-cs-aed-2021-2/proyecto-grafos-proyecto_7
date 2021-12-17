
#include <parser.h>
#include <string>
template<typename TV, typename TE>
string fillJSONVertex(Vertex<TV, TE>* ver, json::iterator jIt)
{
    string id;
    for (auto&[key, value]: jIt->items()) {
        if (key == "Airport ID")
            ver->id = value;
        else if (key == "City")
            ver->city = value;
        else if (key == "Country")
            ver->pais = value;
        else if (key == "DBTZ")
            ver->DBTZ = value;
        else if (key == "Name")
            ver->name = value;
        else if (key == "IATA/FAA")
            ver->IAT = value;
        else if (key == "Longitude") {
            string a = value;
            double num_double = std::stod(a);
            ver->longitud = num_double;
        }
        else if (key == "ICAO")
            ver->ICAO = value;
        else if (key == "Latitude"){
            string a = value;
            double num_double = std::stod(a);
            ver->latitud = num_double;
        }
        else if (key == "Timezone") {
            string str = value;
            ver->timezone = stoi(str);
        }
        else if (key == "DST") {
            string str = value;
            ver->DST = stoi(str);
        }
        else if (key == "destinations") {
            for (auto &i: value) {
                ver->destinos.push_back(i);
            }
        }
    }
    return id;
}

void uGraphMake(UnDirectedGraph<string, double> &tempGraph) {
    for (json::iterator it = tempGraph.file.begin(); it != tempGraph.file.end(); ++it) {   // STL-like access
        auto nodo = new Vertex<string, double>();
        tempGraph.addVertex(fillJSONVertex(nodo, it), nodo);
    }
    for (auto &i: tempGraph.vertexes) {
        for (auto &j: i.second->destinos) {
            double distancia_total = sqrt(pow(i.second->latitud, 2) + pow(i.second->latitud, 2));
            tempGraph.createEdge(i.second->id, j, distancia_total);
            tempGraph.createEdge(j, i.second->id, distancia_total);
        }
    }

}   // Adds the parsed data into the specified undirected graph

void dGraphMake(DirectedGraph<string, double> &tempGraph) {
    // iterate over array
    for (json::iterator it = tempGraph.file.begin(); it != tempGraph.file.end(); ++it) {   // STL-like access
        auto nodo = new Vertex<string, double>();
        tempGraph.addVertex(fillJSONVertex(nodo, it), nodo);
    }
    for (auto &i: tempGraph.vertexes) {
        for (auto &j: i.second->destinos) {
            double distancia_total = sqrt(pow(i.second->latitud, 2) + pow(i.second->latitud, 2));
            tempGraph.createEdge(i.second->id, j, distancia_total);
        }
    }
}




