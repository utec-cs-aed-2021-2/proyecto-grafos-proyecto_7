#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <iostream>
#include "../Graph/graph.h"
#include "../Graph/UndirectedGraph.h"
#include "../Graph/DirectedGraph.h"
#include "../Graph/Algorithms/kruskal.h"
#include "../Graph/Algorithms/prim.h"
#include "../Graph/Algorithms/astar.h"
#include "../Graph/Algorithms/dijkstra.h"
#include "../Graph/Algorithms/floydWarshall.h"
#include "../Graph/Algorithms/bestBFS.h"


class parser
{
    double longitude;
public:
    void readJSON()
    {
        // read a JSON file
        std::ifstream i("../Parser/Data/pe.json");
        json j;
        i >> j;

        // write prettified JSON to another file
        //std::cout << std::setw(4) << j << std::endl;

        // iterate over array
        for (json::iterator it = j.begin(); it != j.end(); ++it)
        {   // STL-like access
            //std::cout << *it << endl;     // print the entire object
            for (auto& [key, value]: it->items())
            {
                //if (key != "destinations")
                //    std::cout << key << " ";
                //if (key == "Longitude")
                //    this->longitude = value;
            }
            //std::cout << endl;
        }
    }
};

#endif

