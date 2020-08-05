
#include <cstring>
#include "Parser.h"
#include "Graph.h"


void Parser::checkCmd(char str1[]) {
    std::string temp = str1;
    char *token = std::strtok(str1, " ");
    char *token1 = std::strtok(token, "(");
    std::string str_token = token1;
    if (str_token == "print") {
        int firstB = temp.find('(');
        int lastB = temp.find(')') - firstB -1;
        std::string var = temp.substr(firstB + 1,lastB);
        bool valid = CheckArgName(var);
        if (valid){
            std::string variable = extractFirstWord(var);
                    Graph graph1 = gcalc.getGraph(variable);
                    std::cout << graph1;
        }
    }
    if (str_token == "delete"){
        int firstB = temp.find('(');
        int lastB = temp.find(')') - firstB -1;
        std::string var = temp.substr(firstB + 1,lastB);
        bool valid = CheckArgName(var);
        if (valid) {
            std::string variable = extractFirstWord(var);
            gcalc.removeGraph(variable);
        }
    }
    if (str_token == "who"){
        std::cout << gcalc ;
    }
    if (str_token == "reset"){
        gcalc.clearCalc();
    }
    if (str_token == "quit"){
        ///need to return some thing that will quit the loop
    }
    int equal = temp.find_first_of('=');
    if (equal != std::string::npos){
        std::string right_object = temp.substr(equal+1);
        int first_letter = right_object.find_first_of('{');
        int last_letter = right_object.find_first_of(',');
        if (first_letter != std::string::npos){
            Vertex vertex1;
            Edges edges1;
            size_t pos = 0;
            int i = 0;
            pos = right_object.find(',') != std::string::npos;
            while (pos){
                std::string junction = right_object.substr(first_letter+1,pos);
//                if(CheckJunctiobnName(junction)){
//                    std::string junction1 = extractFirstWord(junction);
//                    vertex1.addVertex(junction1);
//                }


                pos = right_object.find('|') != std::string::npos;
            }
        }
    }
}


bool Parser::CheckArgName(std::string str) {
    int first_char = -1;
    bool valid = true;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != ' ' && first_char == -1) {
            first_char = i;
            if (!isalpha(str[i])){
                valid = false;
            }
        }
        if (str[i] != ' ' && first_char != -1 && !isalnum(str[i])){
            valid = false;
        }
        if (str[i] == ' ' && first_char != -1) {
            for (int j = i; j <str.size() ; ++j) {
                if (str[j] != ' '){
                    valid = false;
                    break;
                }
            }
        }
    }
    return valid;
}

std::string Parser::extractFirstWord(std::string &str) {
    int first, last;
    for (int i = 0; i <str.size() ; ++i) {
        if (str[i] != ' '){
            first = i;
            for (int j = i; j <str.size() ; ++j) {
                if (str[j] == ' '){
                    last = j;
                    break;
                }
            }
            break;
        }
    }
    last = last -first;
    return str.substr(first,last);
}

