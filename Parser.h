
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
    Edges edges;
    Vertex vertex;
    Graph* graph{};
public:
    explicit Parser( Gcalc gcalc) : gcalc(std::move(gcalc)){};
    void checkCmd(char str1[]);


    static bool CheckArgName(std::string basicString);

    static std::string extractFirstWord(std::string &str);
};


#endif //GCALC_PARSER_H
