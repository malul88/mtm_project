
#ifndef GCALC_GRAPH_H
#define GCALC_GRAPH_H
#include "Parser.h"
#include "Vertex.h"
#include "Edges.h"
#include "Exeptions.h"


Graph1* create();

void destroy(Graph1& graph);

Graph1& addVertex(Graph1& graph, std::string vertex);

Graph1 &addVertex(Graph1 &graph, const char* vertex);

Graph1& addEdge(Graph1& graph, std::string vertex1, std::string vertex2);

Graph1& addEdge(Graph1& graph, const char* vertex1, const char* vertex2);

void disp(Graph1& graph);

Graph1& graphUnion(Graph1& graph_in1, Graph1& graph_in2, Graph1& graph_out);

Graph1& graphIntersection(Graph1 &graph_in1, Graph1 &graph_in2, Graph1 &graph_out);

Graph1& graphDifference(Graph1 &graph_in1, Graph1 &graph_in2, Graph1 &graph_out);

Graph1& graphProduct(Graph1 &graph_in1, Graph1 &graph_in2, Graph1 &graph_out);

Graph1& graphComplement(Graph1 &graph_in, Graph1 &graph_out);


#endif //GCALC_GRAPH1_H
