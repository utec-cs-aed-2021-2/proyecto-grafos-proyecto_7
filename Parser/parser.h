#ifndef PARSER_H
#define PARSER_H

#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
using json = nlohmann::json;

class parser
{
public:
    void readJSON()
    {
        // read a JSON file
        std::ifstream i("../Parser/Data/airports.json");
        json j;
        i >> j;

        // write prettified JSON to another file
        std::ofstream o("pretty.json");
        o << std::setw(4) << j << std::endl;
    }
};

#endif