
#ifndef GCALC_VERTEX_H
#define GCALC_VERTEX_H
#include <iostream>
#include <set>


class Vertex {
private:
    std::set<std::string> vertexes;
public:
    Vertex(std::set<std::string> vertexes);

    Vertex();

    Vertex( const Vertex &vertex);

    Vertex &operator=(const Vertex &vertex);

    void addVertex(std::string vertex);

    void deleteVertex(std::string vertex);

    bool isContain(std::string vertex) const;

    std::set<std::string>::iterator begin() const;

    std::set<std::string>::iterator end() const;

    void clearVertexes();



};

Vertex operator+(const Vertex &vertex1, const Vertex &vertex2);

Vertex operator^(const Vertex &vertex1,const Vertex &vertex2);

Vertex operator-(const Vertex &vertex1,const Vertex &vertex2);

Vertex operator*(const Vertex &vertex1,const Vertex &vertex2);





#endif //GCALC_VERTEX_H
