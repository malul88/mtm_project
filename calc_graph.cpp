
#include "calc_graph.h"

using std::string;
Graph *create() {
    //string graph_name = 'g'+std::to_string(counter++);
    Graph *g1 = new Graph;
    return g1;
}

void destroy(Graph &graph) {
    delete &graph;
}

Graph &addVertex(Graph &graph, const char* vertex) {
    graph.addVertex(string(vertex));
    return graph;
}

Graph &addVertex(Graph &graph, string vertex) {
    graph.addVertex(vertex);
    return graph;
}

Graph &addEdge(Graph &graph, string vertex1, string vertex2) {
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
    return graph;

}

Graph& addEdge(Graph& graph,  const char* vertex1,  const char* vertex2) {
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
    return graph;

}

void disp(Graph &graph) {
    std::cout << graph;
}



Graph &graphUnion(Graph &graph_in1, Graph &graph_in2, Graph &graph_out) {
    graph_out = graph_in1 + graph_in2;
    return graph_out;
}

Graph &graphIntersection(Graph &graph_in1, Graph &graph_in2, Graph &graph_out) {
    graph_out = graph_in1 ^ graph_in2;
    return graph_out;
}

Graph &graphDifference(Graph &graph_in1, Graph &graph_in2, Graph &graph_out) {
    graph_out = graph_in1 - graph_in2;
    return graph_out;
}

Graph &graphProduct(Graph &graph_in1, Graph &graph_in2, Graph &graph_out) {
    graph_out = graph_in1*graph_in2;
    return graph_out;
}

Graph &graphComplement(Graph &graph_in, Graph &graph_out) {
    graph_out = !graph_in;
    return graph_out;
}
