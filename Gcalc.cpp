#include "Gcalc.h"

bool Gcalc::addGraph(const std::string &name, Graph1 *graph) {
    bool not_exist = true;
    if (calc.find(name) != calc.end()) {
        not_exist = false;
    } else {
        calc[name] = graph;

    }
    return not_exist;
}

bool Gcalc::removeGraph(const std::string &name) {
    bool not_exist = true;
    if(calc.empty()) return not_exist;
    if (calc.find(name) == calc.end()) {
        not_exist = false;
    } else {
        Graph1 *temp = calc[name];
        delete temp;
        Graph1 g1;
        calc[name] = &g1;
        calc.erase(name);
    }
    return not_exist;
}

void Gcalc::clearCalc() {
    std::map<std::string, Graph1 *>::iterator it = calc.begin();
    for (; it != calc.end(); ++it) {
        removeGraph(it->first);
        if(calc.empty()) break;
    }
}

Graph1 &Gcalc::getGraph(std::string &str) {
    Graph1 *result = calc[str];
    return *result;
}

bool Gcalc::isContain(const std::string &str) {
    std::map<std::string, Graph1 *>::iterator it;
    it = calc.find(str);
    return it != calc.end();
}

bool Gcalc::isGraphContain(Vertex vertex, std::string vertex1) {
    return vertex.isContain(vertex1);
}

bool Gcalc::isEmpty() {
    return calc.empty();
}
