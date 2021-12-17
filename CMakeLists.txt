cmake_minimum_required(VERSION 3.20)
project(proyecto_grafos_proyecto_7)

set(CMAKE_CXX_STANDARD 17)

include_directories(Graph)
include_directories(Graph/Algorithms)
include_directories(Graph/Structures)
include_directories(Parser)
include_directories(Tester)
include_directories(Parser/nlohmann)

add_executable(proyecto_grafos_proyecto_7
        Graph/Algorithms/astar.h
        Graph/Algorithms/bfs.h
        Graph/Algorithms/dfs.h
        Graph/Algorithms/dijkstra.h
        Graph/Algorithms/kruskal.h
        Graph/Algorithms/prim.h
        Graph/Structures/ds.h
        Graph/Structures/dsarray.h
        Graph/DirectedGraph.h
        Graph/graph.h
        Graph/UndirectedGraph.h
        Parser/parser.h
        Tester/tester.h
        Parser/nlohmann/json.hpp
        main.cpp
        Graph/Algorithms/bellmanFord.h Graph/Algorithms/floydWarshall.h Graph/Algorithms/bestBFS.h)