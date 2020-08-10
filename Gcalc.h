

#ifndef GCALC_GCALC_H
#define GCALC_GCALC_H
#include "Graph1.h"
#include <map>

class Gcalc {
private:
    std::map<std::string,Graph1*> calc;
public:
    bool addGraph(const std::string& name, Graph1 *graph);

    bool isEmpty();

    bool removeGraph(const std::string& name);

    friend std::ostream &operator<<(std::ostream &os, const Gcalc &gcalc){
        std::map<std::string,Graph1*>::const_iterator it = gcalc.calc.begin();
        for (;it!=gcalc.calc.end();it++){
            os << it->first <<std::endl;
        }
        return os;
    }
    Graph1& getGraph(std::string &str);

    bool isContain(const std::string& str);

    void clearCalc();


    bool isGraphContain(Vertex vertex, std::string basicString);
};


#endif //GCALC_GCALC_H

