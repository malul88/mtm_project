
#include "calc_graph.h"


Graph *calc_graph::create() {
    //std::string graph_name = 'g'+std::to_string(counter++);
    Graph *g1 = new Graph;
    return g1;
}

void calc_graph::destroy(Graph &graph) {
    delete &graph;
}

Graph &calc_graph::addVertex(Graph &graph, std::string vertex) {
    graph.addVertex(vertex);
    return graph;
}

Graph &calc_graph::addEdge(Graph &graph, std::string vertex1, std::string vertex2) {
    if (!Vertex::checkVertexName(vertex1) || !Vertex::checkVertexName(vertex2)){
        throw WrongVertexName();
    }
    if (!graph.isContain(vertex1) || !graph.isContain(vertex2)){
        throw ArgumentNotFound();
    }
    std::pair<std::string, std::string> edge;
    edge.first =vertex1;
    edge.second = vertex2;
    graph.addEdge(edge);
    return graph;

}

void calc_graph::disp(Graph &graph) {
    std::cout << graph;
}



Graph &calc_graph::graphUnion(Graph &graph_in1, Graph &graph_in2, Graph &graph_out) {
    graph_out = graph_in1 + graph_in2;
    return graph_out;
}

Graph &calc_graph::graphIntersection(Graph &graph_in1, Graph &graph_in2, Graph &graph_out) {
    graph_out = graph_in1 ^ graph_in2;
    return graph_out;
}

Graph &calc_graph::graphDifference(Graph &graph_in1, Graph &graph_in2, Graph &graph_out) {
    graph_out = graph_in1 - graph_in2;
    return graph_out;
}

Graph &calc_graph::graphProduct(Graph &graph_in1, Graph &graph_in2, Graph &graph_out) {
    graph_out = graph_in1*graph_in2;
    return graph_out;
}

Graph &calc_graph::graphComplement(Graph &graph_in, Graph &graph_out) {
    graph_out = !graph_in;
}
