#include "Gcalc.h"

bool Gcalc::addGraph(const std::string &name, Graph *graph) {
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
    if (calc.find(name) == calc.end()) {
        not_exist = false;
    } else {
        Graph *temp = calc[name];
        delete temp;
        Graph g1;
        calc[name] = &g1;
        calc.erase(name);
    }
    return not_exist;
}

void Gcalc::clearCalc() {
    std::map<std::string, Graph *>::iterator it = calc.begin();
    for (; it != calc.end(); ++it) {
        removeGraph(it->first);
    }
}

Graph &Gcalc::getGraph(std::string &str) {
    Graph *result = calc[str];
    return *result;
}

bool Gcalc::isContain(const std::string &str) {
    std::map<std::string, Graph *>::iterator it;
    it = calc.find(str);
    return it != calc.end();
}

bool Gcalc::isGraphContain(Vertex vertex, std::string vertex1) {
    return vertex.isContain(vertex1);
}
