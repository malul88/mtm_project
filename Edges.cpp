#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-inefficient-string-concatenation"


#include "Edges.h"

Edges::Edges(std::set<std::pair<std::string, std::string>> edges):edges(edges){}

Edges::Edges() {}

Edges::Edges(const Edges &edges) {
    std::set<std::pair<std::string,std::string>> temp(edges.edges);
    this->edges = temp;
}

Edges &Edges::operator=(const Edges &edges) {
    if (this == &edges){
        return *this;
    }
    this->edges.operator=(edges.edges);
    return *this;
}

void Edges::addEdge(std::pair<std::string, std::string> edge) {
    edges.insert(edge);
}

void Edges::deleteEdge(std::pair<std::string, std::string> edge) {
    edges.erase(edge);
}

bool Edges::isContain(std::pair<std::string, std::string> edge) const{
    std::set<std::pair<std::string,std::string>>::iterator it;
    it = edges.find(edge);
    return it != edges.end();
}

std::set<std::pair<std::string, std::string>>::iterator Edges::begin() const {
    std::set<std::pair<std::string,std::string>>::iterator it = edges.begin();
    return it;
}

std::set<std::pair<std::string, std::string>>::iterator Edges::end() const {
    std::set<std::pair<std::string,std::string>>::iterator it = edges.end();
    return it;
}

void Edges::clearEdges() {
    edges.clear();
}

bool Edges::checkIfEmpty() {
    return edges.empty();
}


Edges operator+(const Edges &edges1, const Edges &edges2) {
    Edges result(edges1);
    std::set<std::pair<std::string,std::string>>::iterator it = edges2.begin();
    for (;it!=edges2.end();it++){
        result.addEdge(*it);
    }
    return result;
}

Edges operator^(const Edges &edges1, const Edges &edges2) {
    Edges result;
    std::set<std::pair<std::string,std::string>>::iterator it = edges1.begin();
    for (;it!=edges1.end();it++){
        if (edges2.isContain(*it)){
            result.addEdge(*it);
        }
    }
    return result;
}

Edges operator-(const Edges &edges1, const Edges &edges2) {
    Edges result(edges1);
    std::set<std::pair<std::string,std::string>>::iterator it = edges2.begin();
    for (;it!=edges2.end();it++){
        if (result.isContain(*it)){
            result.deleteEdge(*it);
        }
    }
    return result;}

Edges operator*(const Edges &edges1, const Edges &edges2) {
    Edges result;
    std::set<std::pair<std::string,std::string>>::iterator it1 = edges1.begin();
    for (; it1!=edges1.end(); ++it1) {
        std::set<std::pair<std::string,std::string>>::iterator it2 = edges2.begin();
        std::string first1 = it1->first;
        std::string second1 = it1->second;
        for (; it2!=edges2.end(); ++it2) {
            std::string first2 = it2->first;
            std::string second2 = it2->second;
            std::pair <std::string,std::string> p  ('[' +first1 +";" + first2 + ']', '[' + second1 + ";" +second2 + ']');
            result.addEdge(p);
        }
    }
    return result;


}

#pragma clang diagnostic pop