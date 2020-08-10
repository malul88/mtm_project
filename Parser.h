
#ifndef GCALC_PARSER_H
#define GCALC_PARSER_H
#include "Gcalc.h"
#include <cctype>
#include <string>
#include <utility>
#include <vector>
#include "Exeptions.h"


class Parser {
private:
    Gcalc gcalc;
    Gcalc gcalc_temp;
    int counter = 0;
public:
    explicit Parser( Gcalc gcalc) : gcalc(gcalc){};

    int checkCmd(std::string str1);

    static bool CheckArgName(std::string basicString);

    static std::string extractFirstWord(std::basic_string<char> str);

    Graph1* dealWithDefinition(const std::string& graph_name, std::string str, int equal);

    void dealWithEqual(std::string left_o, std::string basicString, int equal);

    static char firstLetter(std::string basicString);

    Edges makeSetOfEdge(Vertex vertex, std::vector<std::pair<std::string, std::string>> edge_result);

    Graph1 complement(std::string basicString);


    Graph1 multipleOperand(std::string basicString);

    Graph1 binaryExpression(std::vector<char> vec_operands, std::vector<std::string> vec_var); // create new func

    Graph1 gUnion(std::string left, std::string right);

    Graph1 gUnion(Graph1& g1, Graph1& g2);

    Graph1 gIntersection(std::string left, std::string right);

    Graph1 gIntersection(Graph1& g1, Graph1& g2);

    Graph1 gDifference(std::string left, std::string right);

    Graph1 gDifference(Graph1& g1, Graph1& g2);

    Graph1 gProduct(std::string basicString, std::string basicString1);

    Graph1 gProduct(Graph1& g1, Graph1& g2);

    void addGraph(std::string graph_name, Graph1* graph);

//    Graph1 stringToGraph(std::string string); //yoav_func
    void writeGraphToFile(Graph1 &graph, std::string basicString);

    Graph1 loadGraphFromFile(std::string basicString);
};


#endif //GCALC_PARSER_H
