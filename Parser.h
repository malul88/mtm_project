
#ifndef GCALC_PARSER_H
#define GCALC_PARSER_H
#include "Gcalc.h"
#include <cctype>
#include <string>
#include <utility>
#include <vector>


class Parser {
private:
    Gcalc gcalc;
public:
    explicit Parser( Gcalc gcalc) : gcalc(std::move(gcalc)){};
    void checkCmd(char str1[]);


    static bool CheckArgName(std::string basicString);

    static std::string extractFirstWord(std::string &str);

    void dealWithDefinition(std::string graph_name, std::string str, int equal);

    void dealWithEqual(std::string basicString, int equal);

    static size_t firstLetter(std::string basicString);

    static Vertex makeSetOfVertex(std::vector<std::string> vertex_result);

    static Edges makeSetOfEdge(std::vector<std::pair<std::string, std::string>> edge_result);
};


#endif //GCALC_PARSER_H
