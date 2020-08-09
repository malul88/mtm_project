#include "Graph.h"


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

void Graph::WriteGraphToFile(Graph &graph, std::string file_name) {
    std::ofstream outfile(file_name, std::ios_base::binary);
    if (!outfile){
        throw CantOpenFile();
    }
    int vertex_num = vertexes.size();
    int edge_num = edges.size();
    outfile.write((const char*)&vertex_num, sizeof(int));
    outfile.write((const char*)&edge_num, sizeof(int));
    std::set<std::string>::iterator it = vertexes.begin();
    std::string buffer;
    for (; it !=vertexes.end();  ++it) {
        int size_of_ver = it->size();
        outfile.write((const char*)&size_of_ver, sizeof(int));
        buffer = *it;
        int length = buffer.size() + 1;
        char *buffer1 = new char [length];
        std::copy(buffer.begin(),buffer.end(),buffer1);
        outfile.write(buffer1,buffer.size());
        buffer.clear();
        delete[] buffer1;
    }
    std::set<std::pair<std::string,std::string>>::iterator it1 = edges.begin();
    for (; it1 !=edges.end();  ++it1) {
        buffer = it1->first;
        int size_of_edge = buffer.size();
        outfile.write((const char*)&size_of_edge, sizeof(int));
        int length = buffer.size() + 1;
        char *buffer2 = new char[length];
        std::copy(buffer.begin(),buffer.end(),buffer2);
        outfile.write(buffer2,buffer.size());
        delete[] buffer2;
        buffer = it1->second;
        size_of_edge = buffer.size();
        outfile.write((const char*)&size_of_edge, sizeof(int));
        length = buffer.size() + 1;
        char *buffer3 = new char[length];
        std::copy(buffer.begin(),buffer.end(),buffer3);
        outfile.write(buffer3,buffer.size());
        delete[] buffer3;
    }

}


