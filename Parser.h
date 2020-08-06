
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
public:
    explicit Parser( Gcalc gcalc) : gcalc(gcalc){};

    int checkCmd(std::string str1);

    static bool CheckArgName(std::string basicString);

    static std::string extractFirstWord(std::string &str);

    Graph* dealWithDefinition(const std::string& graph_name, std::string str, int equal);

    void dealWithEqual(std::string left_o, std::string basicString, int equal);

    static char firstLetter(std::string basicString);

    Edges makeSetOfEdge(Vertex vertex, std::vector<std::pair<std::string, std::string>> edge_result);

    Graph complement(std::string basicString);

    Graph multipleOperand(std::string basicString);

    Graph binaryExpression(std::vector<char> vec_operands,std::vector<std::string> vec_var); // create new func

    Graph gUnion(std::string left, std::string right);

    Graph gUnion(Graph& g1,Graph& g2);

    Graph gIntersection(std::string left, std::string right);

    Graph gIntersection(Graph& g1,Graph& g2);

    Graph gDifference(std::string left, std::string right);

    Graph gDifference(Graph& g1,Graph& g2);

    Graph gProduct(std::string basicString, std::string basicString1);

    Graph gProduct(Graph& g1,Graph& g2);
};


#endif //GCALC_PARSER_H
