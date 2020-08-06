#include <iostream>
#include <set>
#include <map>
#include <string>
#include "Vertex.h"
#include "Edges.h"
#include "Graph.h"
#include "Gcalc.h"
#include "Parser.h"
using namespace std;

int main() {

//    Vertex v1;
//    v1.addVertex("1");
//    v1.addVertex("2");
//    v1.addVertex("3");
//    Vertex v2;
//    v2 =v1;
//    v2.addVertex("4");
//    v1.addVertex("5");
//    v1.addVertex("6");
//    Edges e1, e2;
//    pair <string,string> p ("1","2");
//    pair <string,string> p1 ("3","2");
//    pair <string,string> p3 ("1","3");
//    pair <string,string> p4 ("3","4");
//    pair <string,string> p5 ("2","4");
//    e1.addEdge(p);
//    e1.addEdge(p1);
//    e1.addEdge(p3);
//    e2.addEdge(p4);
//    e2.addEdge(p5);
//    Graph G1(v1,e1);
//    Graph G2(v2,e2);
//    Graph G3 = G1 + G2;
//    G3 = !G1;
//    Graph *G4 = new Graph;
//    Graph *G5 = new Graph;
//    Graph *G6 = new Graph;
//    *G4 = G1;
//    *G5 = !G1;
//    *G6 = G2;
//    Gcalc mmm;
//    mmm.addGraph("G4",G4);
//    mmm.addGraph("G5",G5);
//    mmm.addGraph("G6",G6);
//    Parser j(mmm);
//
//    char cmd1[] ="G1 = {1x[[[[]]]],x2,x3 | <          ffffffx1,x2> , <x2,                x3> , <               x1,x3> }";
//    char cmd[] ="print (G1)";
//    int u = j.checkCmd(cmd1);
//
//   int y =j.checkCmd(cmd);

Gcalc gcalc;
Parser pars(gcalc);
int cmdResult = 0;
string command;
while (!cmdResult){
    cout << "Gcalc>";
    getline(cin,command);
    try {
        cmdResult = pars.checkCmd(command);
    } catch (const Exception & e) {
        cout << e.what() << endl;
    }
}






}
