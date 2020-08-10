
#ifndef GCALC_GRAPH1_H
#define GCALC_GRAPH1_H
#include <iostream>
#include <string.h>
#include <set>
#include <fstream>
#include <utility>
#include "Vertex.h"
#include "Edges.h"


class Graph1 {
private:
    Vertex vertexes;
    Edges edges;
public:
    Graph1(Vertex& vertexes, Edges& edges);

    Graph1();

    Graph1(const Graph1 &graph);

    Graph1 &operator=(const Graph1 &graph);

    friend Graph1 operator+(const Graph1 &graph1, const Graph1 &graph2);

    friend Graph1 operator^(const Graph1 &graph1, const Graph1 &graph2);

    friend Graph1 operator-(const Graph1 &graph1, const Graph1 &graph2);

    friend Graph1 operator*(const Graph1 &graph1, const Graph1 &graph2);

    friend Graph1 operator!(const Graph1 &graph1);

    bool isContain(std::string vertex);

    void addVertex(std::string vertex);

    void addEdge(std::pair<std::string,std::string> edge);

    friend std::ostream &operator<<(std::ostream &os, const Graph1 &graph){
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


    void WriteGraphToFile(Graph1 &graph, std::string basicString);
};

Graph1 operator+(const Graph1 &graph1, const Graph1 &graph2);

Graph1 operator^(const Graph1 &graph1, const Graph1 &graph2);

Graph1 operator-(const Graph1 &graph1, const Graph1 &graph2);

Graph1 operator*(const Graph1 &graph1, const Graph1 &graph2);

Graph1 operator!(const Graph1 &graph1);




#endif //GCALC_GRAPH1_H

