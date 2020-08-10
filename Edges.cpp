


#include "Edges.h"
using namespace std;
Edges::Edges(set<pair<string, string>> edges):edges(edges){}

Edges::Edges() {}

Edges::Edges(const Edges &edges) {
    set<pair<string,string>> temp(edges.edges);
    this->edges = temp;
}

Edges &Edges::operator=(const Edges &edges) {
    if (this == &edges){
        return *this;
    }
    this->edges.operator=(edges.edges);
    return *this;
}

void Edges::addEdge(pair<string, string> edge) {
    edges.insert(edge);
}

void Edges::deleteEdge(pair<string, string> edge) {
    edges.erase(edge);
}

bool Edges::isContain(pair<string, string> edge) const{
    set<pair<string,string>>::iterator it;
    it = edges.find(edge);
    return it != edges.end();
}

set<pair<string, string>>::iterator Edges::begin() const {
    set<pair<string,string>>::iterator it = edges.begin();
    return it;
}

set<pair<string, string>>::iterator Edges::end() const {
    set<pair<string,string>>::iterator it = edges.end();
    return it;
}

void Edges::clearEdges() {
    edges.clear();
}

bool Edges::checkIfEmpty() {
    return edges.empty();
}

int Edges::size() {
    return edges.size();
}


Edges operator+(const Edges &edges1, const Edges &edges2) {
    Edges result(edges1);
    set<pair<string,string>>::iterator it = edges2.begin();
    for (;it!=edges2.end();it++){
        result.addEdge(*it);
    }
    return result;
}

Edges operator^(const Edges &edges1, const Edges &edges2) {
    Edges result;
    set<pair<string,string>>::iterator it = edges1.begin();
    for (;it!=edges1.end();it++){
        if (edges2.isContain(*it)){
            result.addEdge(*it);
        }
    }
    return result;
}

Edges operator-(const Edges &edges1, const Edges &edges2) {
    Edges result(edges1);
    set<pair<string,string>>::iterator it = edges2.begin();
    for (;it!=edges2.end();it++){
        if (result.isContain(*it)){
            result.deleteEdge(*it);
        }
    }
    return result;}

Edges operator*(const Edges &edges1, const Edges &edges2) {
    Edges result;
    set<pair<string,string>>::iterator it1 = edges1.begin();
    for (; it1!=edges1.end(); ++it1) {
        set<pair<string,string>>::iterator it2 = edges2.begin();
        string first1 = it1->first;
        string second1 = it1->second;
        for (; it2!=edges2.end(); ++it2) {
            string first2 = it2->first;
            string second2 = it2->second;
            pair <string,string> p  ('[' +first1 +";" + first2 + ']', '[' + second1 + ";" +second2 + ']');
            result.addEdge(p);
        }
    }
    return result;


}

