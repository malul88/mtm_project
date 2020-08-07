#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"

#include "Graph.h"

#include <utility>

Graph::Graph(Vertex& vertex, Edges& edges): vertexes(vertex), edges(edges) {
}

Graph::Graph() {
}

Graph::Graph(const Graph &graph) {
    vertexes = graph.vertexes;
    edges = graph.edges;
}

Graph &Graph::operator=(const Graph &graph) {
    if (this == &graph){
        return *this;
    }
    vertexes = graph.vertexes;
    edges = graph.edges;
    return *this;
}

Graph operator+(const Graph &graph1, const Graph &graph2){
    Graph result;
    result.vertexes = graph1.vertexes + graph2.vertexes;
    result.edges = graph1.edges + graph2.edges;
    return result;
}

Graph operator^(const Graph &graph1, const Graph &graph2) {
    Graph result;
    result.vertexes = graph1.vertexes ^ graph2.vertexes;
    result.edges = graph1.edges ^ graph2.edges;
    return result;
}

Graph operator-(const Graph &graph1, const Graph &graph2) {
    Graph result;
    result.vertexes = graph1.vertexes - graph2.vertexes;
    result.edges = graph1.edges - graph2.edges;
    return result;
}

Graph operator*(const Graph &graph1, const Graph &graph2){
    Graph result;
    result.vertexes = graph1.vertexes * graph2.vertexes;
    result.edges = graph1.edges * graph2.edges;
    return result;
}

Graph operator!(const Graph &graph1) {
    Graph result;
    result.vertexes = graph1.vertexes;
    std::set<std::string>::iterator it1 = graph1.vertexes.begin();
    for (;it1!=graph1.vertexes.end();it1++){
        std::set<std::string>::iterator it2 = graph1.vertexes.begin();
        for (;it2!=graph1.vertexes.end();it2++){
            std::pair<std::string,std::string> temp (*it1,*it2);
            if (*it1 == *it2 || graph1.edges.isContain(temp)) {
                continue;
            }
            result.edges.addEdge(temp);
        }

    }
    return result;
}

bool Graph::checkIfEmpty() {
    return vertexes.checkIfEmpty() && edges.checkIfEmpty();
}

bool Graph::isContain(std::string vertex) {
    return vertexes.isContain(vertex);
}

void Graph::addVertex(std::string vertex) {
vertexes.addVertex(vertex);
}

void Graph::addEdge(std::pair<std::string, std::string> edge) {
    edges.addEdge(edge);

}


#pragma clang diagnostic pop