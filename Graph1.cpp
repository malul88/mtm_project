#include "Graph1.h"

using namespace std;
Graph1::Graph1(Vertex& vertex, Edges& edges): vertexes(vertex), edges(edges) {
}

Graph1::Graph1() {
}

Graph1::Graph1(const Graph1 &graph) {
    vertexes = graph.vertexes;
    edges = graph.edges;
}

Graph1 &Graph1::operator=(const Graph1 &graph) {
    if (this == &graph){
        return *this;
    }
    vertexes = graph.vertexes;
    edges = graph.edges;
    return *this;
}

Graph1 operator+(const Graph1 &graph1, const Graph1 &graph2){
    Graph1 result;
    result.vertexes = graph1.vertexes + graph2.vertexes;
    result.edges = graph1.edges + graph2.edges;
    return result;
}

Graph1 operator^(const Graph1 &graph1, const Graph1 &graph2) {
    Graph1 result;
    result.vertexes = graph1.vertexes ^ graph2.vertexes;
    result.edges = graph1.edges ^ graph2.edges;
    return result;
}

Graph1 operator-(const Graph1 &graph1, const Graph1 &graph2) {
    Graph1 result;
    result.vertexes = graph1.vertexes - graph2.vertexes;
    result.edges = graph1.edges - graph2.edges;
    return result;
}

Graph1 operator*(const Graph1 &graph1, const Graph1 &graph2){
    Graph1 result;
    result.vertexes = graph1.vertexes * graph2.vertexes;
    result.edges = graph1.edges * graph2.edges;
    return result;
}

Graph1 operator!(const Graph1 &graph1) {
    Graph1 result;
    result.vertexes = graph1.vertexes;
    set<string>::iterator it1 = graph1.vertexes.begin();
    for (;it1!=graph1.vertexes.end();it1++){
        set<string>::iterator it2 = graph1.vertexes.begin();
        for (;it2!=graph1.vertexes.end();it2++){
            pair<string,string> temp (*it1,*it2);
            if (*it1 == *it2 || graph1.edges.isContain(temp)) {
                continue;
            }
            result.edges.addEdge(temp);
        }

    }
    return result;
}

bool Graph1::checkIfEmpty() {
    return vertexes.checkIfEmpty() && edges.checkIfEmpty();
}

bool Graph1::isContain(string vertex) {
    return vertexes.isContain(vertex);
}

void Graph1::addVertex(string vertex) {
    vertexes.addVertex(vertex);
}

void Graph1::addEdge(pair<string, string> edge) {
    edges.addEdge(edge);

}

void Graph1::WriteGraphToFile(Graph1 &graph, string file_name) {
    ofstream outfile(file_name, ios_base::binary);
    if (!outfile){
        throw CantOpenFile();
    }
    int vertex_num = vertexes.size();
    int edge_num = edges.size();
    outfile.write((const char*)&vertex_num, sizeof(int));
    outfile.write((const char*)&edge_num, sizeof(int));
    set<string>::iterator it = vertexes.begin();
    string buffer;
    for (; it !=vertexes.end();  ++it) {
        int size_of_ver = it->length();
        outfile.write((const char*)&size_of_ver, sizeof(int));
        buffer = *it;
        int length = buffer.size() +1 ;
        char *buffer1 = new char [length];
        copy(buffer.begin(),buffer.end(),buffer1);
        buffer1[length-1] = '\0';
        outfile.write(buffer1,buffer.length());
        buffer.clear();
        delete[] buffer1;
    }
    set<pair<string,string>>::iterator it1 = edges.begin();
    for (; it1 !=edges.end();  ++it1) {
        buffer = it1->first;
        int size_of_edge = buffer.length();
        outfile.write((const char*)&size_of_edge, sizeof(int));
        int length = buffer.size() +1;
        char *buffer2 = new char[length];
        copy(buffer.begin(),buffer.end(),buffer2);
        buffer2[length-1] = '\0';
        outfile.write(buffer2,buffer.length());
        delete[] buffer2;
        buffer = it1->second;
        size_of_edge = buffer.length();
        outfile.write((const char*)&size_of_edge, sizeof(int));
        length = buffer.length() + 1;
        char *buffer3 = new char[length];
        copy(buffer.begin(),buffer.end(),buffer3);
        buffer3[length-1] = '\0';
        outfile.write(buffer3,buffer.length());
        delete[] buffer3;
    }

}


