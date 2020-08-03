
#ifndef GCALC_GRAPH_H
#define GCALC_GRAPH_H
#include <iostream>
#include <set>
#include <utility>
#include "Vertex.h"
#include "Edges.h"


class Graph {
private:
    Vertex vertexes;
    Edges edges;
public:
    Graph(Vertex& vertexes, Edges& edges);

    Graph();

    Graph(const Graph &graph);

    Graph &operator=(const Graph &graph);

    friend Graph operator+(const Graph &graph1, const Graph &graph2);

    friend Graph operator^(const Graph &graph1, const Graph &graph2);

    friend Graph operator-(const Graph &graph1, const Graph &graph2);

    friend Graph operator*(const Graph &graph1, const Graph &graph2);

    friend Graph operator!(const Graph &graph1);








};

Graph operator+(const Graph &graph1, const Graph &graph2);

Graph operator^(const Graph &graph1, const Graph &graph2);

Graph operator-(const Graph &graph1, const Graph &graph2);

Graph operator*(const Graph &graph1, const Graph &graph2);

Graph operator!(const Graph &graph1);




#endif //GCALC_GRAPH_H
