#include "Gcalc.h"

bool Gcalc::addGraph(const std::string& name,  Graph* graph) {
    bool not_exist = true;
    if (calc.find(name)!= calc.end()){
        not_exist = false;
    }else{
//        calc.insert(std::pair<std::string ,Graph*>(name,graph));
            calc[name] = graph;

    }
    return not_exist;
}

bool Gcalc::removeGraph(const std::string &name) {
    bool not_exist = true;
    if (calc.find(name)== calc.end()){
        not_exist = false;
    }else{
        Graph* temp = calc[name];
        delete temp;
        calc.erase(name);

    }
    return not_exist;
}

void Gcalc::clearCalc() {
    calc.clear();
}

Graph &Gcalc::getGraph(std::string &str) {
    Graph* result =  calc[str];
    return *result;
}

bool Gcalc::isContain(const std::string& str) {
    std::map<std::string,Graph*>::iterator it;
    it = calc.find(str);
    return it != calc.end();
}
