
#ifndef GCALC_GCALC_H
#define GCALC_GCALC_H
#include "Graph.h"
#include <map>

class Gcalc {
private:
    std::map<std::string,Graph*> calc;
public:
    bool addGraph(const std::string& name, Graph *graph);

    bool removeGraph(const std::string& name);

    friend std::ostream &operator<<(std::ostream &os, const Gcalc &gcalc){
        std::map<std::string,Graph*>::const_iterator it = gcalc.calc.begin();
        for (;it!=gcalc.calc.end();it++){
            os << it->first <<std::endl;
        }
        return os;
    }
    Graph& getGraph(std::string &str);

    void clearCalc();









    };


#endif //GCALC_GCALC_H
