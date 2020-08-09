
#ifndef GCALC_CALC_GRAPH_H
#define GCALC_CALC_GRAPH_H
#include "Parser.h"
#include "Vertex.h"
#include "Edges.h"


Graph* create();

void destroy(Graph& graph);

Graph& addVertex(Graph& graph, std::string vertex);

Graph &addVertex(Graph &graph, const char* vertex);

Graph& addEdge(Graph& graph, std::string vertex1, std::string vertex2);

Graph& addEdge(Graph& graph,  const char* vertex1,  const char* vertex2);

void disp(Graph& graph);

Graph& graphUnion(Graph& graph_in1,Graph& graph_in2,Graph& graph_out);

Graph& graphIntersection(Graph &graph_in1, Graph &graph_in2, Graph &graph_out);

Graph& graphDifference(Graph &graph_in1, Graph &graph_in2, Graph &graph_out);

Graph& graphProduct(Graph &graph_in1, Graph &graph_in2, Graph &graph_out);

Graph& graphComplement(Graph &graph_in, Graph &graph_out);


#endif //GCALC_CALC_GRAPH_H
