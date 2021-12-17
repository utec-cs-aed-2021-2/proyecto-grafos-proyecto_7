#ifndef PARSER_H
#define PARSER_H

#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
using json = nlohmann::json;

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
                if (key != "destinations")
                    std::cout << key << " ";
                //if (key == "Longitude")
                //    this->longitude = value;
            }
            std::cout << endl;
        }
    }
};

#endif