

#include "Vertex.h"
#include <stack>
Vertex::Vertex(std::set<std::string> vertexes):vertexes(vertexes) {
}

Vertex::Vertex(const Vertex &vertex) {
    std::set<std::string> temp(vertex.vertexes);
    vertexes = temp;
}

Vertex &Vertex::operator=(const Vertex &vertex) {
    if (this == &vertex){
        return *this;
    }
    this->vertexes.operator=(vertex.vertexes);
    return *this;
}

Vertex::Vertex() {

}

void Vertex::addVertex(std::string vertex) {
    if (!checkVertexName(vertex)){
        throw WrongVertexName();
    }
    vertexes.insert(vertex);
}

void Vertex::deleteVertex(std::string vertex) {
    vertexes.erase(vertex);

}

bool Vertex::isContain(std::string vertex) const {
    std::set<std::string>::iterator it;
    it = vertexes.find(vertex);
    return it != vertexes.end();
}

std::set<std::string>::iterator Vertex::begin() const {
    std::set<std::string>::iterator it = vertexes.begin();
    return it;
}

std::set<std::string>::iterator Vertex::end() const {
    std::set<std::string>::iterator it  = vertexes.end();
    return it;
}

void Vertex::clearVertexes() {
    vertexes.clear();
}

bool Vertex::checkIfEmpty() {
    return vertexes.empty();
}

bool Vertex::checkVertexName(std::string vertex) {
    std::stack<char> stack;
    for (size_t i = 0; i < vertex.size(); ++i) {
        if(!isalnum(vertex.at(i)) && vertex.at(i) != '[' &&
        vertex.at(i) != ']' && vertex.at(i) != ';'){
            return false;
        }
        if(vertex.at(i) == '[') {
            stack.push('[');
        }
        if(vertex.at(i) == ';' && stack.size() == 0 ) return false;
        if(vertex.at(i) == ']' && stack.size() == 0) return false;
        if(vertex.at(i) == ']' && stack.size()!= 0) stack.pop();
    }
    return stack.empty();
}

int Vertex::size() {
    return vertexes.size();
}

Vertex operator+(const Vertex &vertex1, const Vertex &vertex2){
    Vertex result(vertex1);
    std::set<std::string>::iterator it = vertex2.begin();
    for (;it!=vertex2.end();it++){
            result.addVertex(*it);
    }
    return result;

}

Vertex operator^(const Vertex &vertex1,const Vertex &vertex2){
    Vertex result;
    std::set<std::string>::iterator it = vertex1.begin();
    for (;it!=vertex1.end();it++){
        if (vertex2.isContain(*it)){
            result.addVertex(*it);
        }
    }
    return result;
}

Vertex operator-(const Vertex &vertex1,const Vertex &vertex2){
    Vertex result(vertex1);
    std::set<std::string>::iterator it = vertex2.begin();
    for (;it!=vertex2.end();it++){
        if (result.isContain(*it)){
            result.deleteVertex(*it);
        }
    }
    return result;
}

Vertex operator*(const Vertex &vertex1,const Vertex &vertex2){
    Vertex result;
    std::set<std::string>::iterator it1 = vertex1.begin();
    for (; it1!=vertex1.end(); ++it1) {
        std::set<std::string>::iterator it2 = vertex2.begin();
        for (; it2!=vertex2.end(); ++it2) {
            std::string temp = ('['+ *it1 + ';' + *it2 + ']');
            result.addVertex(temp);
        }
    }
    return result;


}





