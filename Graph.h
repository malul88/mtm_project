
#ifndef GCALC_GRAPH_H
#define GCALC_GRAPH_H
#include <iostream>
#include <string.h>
#include <set>
#include <fstream>
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

    bool isContain(std::string vertex);

    void addVertex(std::string vertex);

    void addEdge(std::pair<std::string,std::string> edge);

    friend std::ostream &operator<<(std::ostream &os, const Graph &graph){
        std::set<std::string>::iterator it = graph.vertexes.begin();
        for (;it!=graph.vertexes.end();it++){
            os << *it << std::endl;
        }
        os << "$"<<std::endl;
        std::set<std::pair<std::string,std::string>>::iterator it1 = graph.edges.begin();
        for (;it1!=graph.edges.end();it1++){
            os << it1->first <<" "<<it1->second<< std::endl;
        }
        return os;
    }

    bool checkIfEmpty();


    void WriteGraphToFile(Graph &graph, std::string basicString);
};

Graph operator+(const Graph &graph1, const Graph &graph2);

Graph operator^(const Graph &graph1, const Graph &graph2);

Graph operator-(const Graph &graph1, const Graph &graph2);

Graph operator*(const Graph &graph1, const Graph &graph2);

Graph operator!(const Graph &graph1);




#endif //GCALC_GRAPH_H

