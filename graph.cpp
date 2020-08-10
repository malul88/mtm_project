
#include "graph.h"

using std::string;
Graph1 *create() {
    //string graph_name = 'g'+std::to_string(counter++);
    Graph1 *g1 = new Graph1;
    return g1;
}

void destroy(Graph1 &graph) {
    delete &graph;
}
Graph1 &addVertex(Graph1 &graph, const char* vertex) {
try
{
    
    graph.addVertex(string(vertex));
}
catch(const std::exception& e)
{
    std::cout << e.what() << '\n';
}
    return graph;
}


Graph1 &addVertex(Graph1 &graph, string vertex) {
try{

    graph.addVertex(vertex);
}   
catch(const std::exception& e)
{
    std::cout << e.what() << '\n';
}
    return graph;
}

Graph1 &addEdge(Graph1 &graph, string vertex1, string vertex2) {
    try{
    if (!Vertex::checkVertexName(vertex1) || !Vertex::checkVertexName(vertex2)){
        throw WrongVertexName();
    }
    if (!graph.isContain(vertex1) || !graph.isContain(vertex2)){
        throw ArgumentNotFound();
    }
    std::pair<string, string> edge;
    edge.first =vertex1;
    edge.second = vertex2;
    graph.addEdge(edge);
    } catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    return graph;
}

Graph1& addEdge(Graph1& graph, const char* vertex1, const char* vertex2) {
    try
    {
    if (!Vertex::checkVertexName(vertex1) || !Vertex::checkVertexName(vertex2)){
        throw WrongVertexName();
    }
    if (!graph.isContain(vertex1) || !graph.isContain(vertex2)){
        throw ArgumentNotFound();
    }
    std::pair<string, string> edge;
    edge.first =vertex1;
    edge.second = vertex2;
    graph.addEdge(edge);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    return graph;
}

void disp(Graph1 &graph) {
    std::cout << graph;
}



Graph1 &graphUnion(Graph1 &graph_in1, Graph1 &graph_in2, Graph1 &graph_out) {
    graph_out = graph_in1 + graph_in2;
    return graph_out;
}

Graph1 &graphIntersection(Graph1 &graph_in1, Graph1 &graph_in2, Graph1 &graph_out) {
    graph_out = graph_in1 ^ graph_in2;
    return graph_out;
}

Graph1 &graphDifference(Graph1 &graph_in1, Graph1 &graph_in2, Graph1 &graph_out) {
    graph_out = graph_in1 - graph_in2;
    return graph_out;
}

Graph1 &graphProduct(Graph1 &graph_in1, Graph1 &graph_in2, Graph1 &graph_out) {
    graph_out = graph_in1*graph_in2;
    return graph_out;
}

Graph1 &graphComplement(Graph1 &graph_in, Graph1 &graph_out) {
    graph_out = !graph_in;
    return graph_out;
}
