#include <iostream>
#include <set>
#include <map>
#include "Vertex.h"
#include "Edges.h"
#include "Graph.h"

int main() {
    using namespace std;
    Vertex v1;
    v1.addVertex("1");
    v1.addVertex("2");
    v1.addVertex("3");
    Vertex v2;
    v2 =v1;
    v2.addVertex("4");
    v1.addVertex("5");
    v1.addVertex("6");
    Edges e1, e2;
    pair <string,string> p ("1","2");
    pair <string,string> p1 ("3","2");
    pair <string,string> p3 ("1","3");
    pair <string,string> p4 ("3","4");
    pair <string,string> p5 ("2","4");
    e1.addEdge(p);
    e1.addEdge(p1);
    e1.addEdge(p3);
    e2.addEdge(p4);
    e2.addEdge(p5);
    Graph G1(v1,e1);
    Graph G2(v2,e2);
    Graph G3 = G1 + G2;
    G3 = !G1;
    G3 = !G1;





}
