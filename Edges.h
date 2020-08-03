
#ifndef GCALC_EDGES_H
#define GCALC_EDGES_H
#include <iostream>
#include <utility>
#include <set>


class Edges {
private:
    std::set<std::pair<std::string,std::string>> edges;
public:
    Edges(std::set<std::pair<std::string,std::string>> edges);

    Edges();

    Edges( const Edges &edges);

    Edges &operator=(const Edges &edges);

    void addEdge(std::pair<std::string,std::string> edge);

    void deleteEdge(std::pair<std::string,std::string> edge);

    bool isContain(std::pair<std::string, std::string> edge) const ;

    std::set<std::pair<std::string,std::string>>::iterator begin() const;

    std::set<std::pair<std::string,std::string>>::iterator end() const;

};

Edges operator+(const Edges &edges1, const Edges &edges2);

Edges operator^(const Edges &edges1,const Edges &edges2);

Edges operator-(const Edges &edges1,const Edges &edges2);

Edges operator*(const Edges &edges1,const Edges &edges2);



#endif //GCALC_EDGES_H
