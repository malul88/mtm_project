#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

#include <cstring>
#include <sstream>
#include "Parser.h"
#include "Graph.h"


void Parser::checkCmd(char str1[]) {
    std::string temp = str1;
    char *token = std::strtok(str1, " ");
    char *token1 = std::strtok(token, "(");
    std::string str_token = token1;
    if (str_token == "print") {
        int firstB = temp.find('(');
        int lastB = temp.find(')') - firstB - 1;
        std::string var = temp.substr(firstB + 1, lastB);
        bool valid = CheckArgName(var);
        if (valid) {
            std::string variable = extractFirstWord(var);
            Graph graph1 = gcalc.getGraph(variable);
            std::cout << graph1;
        }
    }
    else if (str_token == "delete") {
        int firstB = temp.find('(');
        int lastB = temp.find(')') - firstB - 1;
        std::string var = temp.substr(firstB + 1, lastB);
        bool valid = CheckArgName(var);
        if (valid) {
            std::string variable = extractFirstWord(var);
            gcalc.removeGraph(variable);
        }
    }
    else if (str_token == "who") {
        std::cout << gcalc;
    }
    else if (str_token == "reset") {
        gcalc.clearCalc();
    }
    else if (str_token == "quit") {
        ///need to return some thing that will quit the loop
    }
    int equal = temp.find_first_of('=');
    if (equal != std::string::npos) {
        dealWithEqual(temp, equal);
    }

}


bool Parser::CheckArgName(std::string str) {
    int first_char = -1;
    bool valid = true;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != ' ' && first_char == -1) {
            first_char = i;
            if (!isalpha(str[i])) {
                valid = false;
            }
        }
        if (str[i] != ' ' && first_char != -1 && !isalnum(str[i])) {
            valid = false;
        }
        if (str[i] == ' ' && first_char != -1) {
            for (int j = i; j < str.size(); ++j) {
                if (str[j] != ' ') {
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
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != ' ') {
            first = i;
            for (int j = i; j < str.size(); ++j) {
                if (str[j] == ' ') {
                    last = j;
                    break;
                }
            }
            break;
        }
    }
    last = last - first;
    return str.substr(first, last);
}

void Parser::dealWithDefinition(std::string graph_name, std::string str, int equal) {
    std::string right_object = str.substr(str.find('{'));
    std::string vertexes = right_object.substr(1,right_object.find('|') -1);
    int first = right_object.find('|')+1;
    int last = right_object.find('}') - first;
    std::string edge = right_object.substr( first,last);
    Vertex vertex1;
    Edges edges1;
    std::vector<std::string> vertex_result;
    std::stringstream ssv (vertexes);
    while (ssv.good()){
        std::string substring;
        std::getline(ssv , substring, ',');
        vertex_result.push_back(substring);
    }
    vertex1 = makeSetOfVertex(vertex_result);

    std::vector<std::pair<std::string, std::string>> edge_result;
    std::vector<std::string> edge_temp;
    std::stringstream sse (edge);
    while (sse.good()){
        std::string substring;
        std::getline(sse , substring, '>');
        edge_temp.push_back(substring);
    }
    for (int i = 0; i <edge_temp.size() ; ++i) {
        std::string temp = edge_temp.at(i);
        std::string first1 = edge_temp.at(i).substr(0,temp.find(','));
        std::string second =edge_temp.at(i).substr(temp.find(',')+1);
        int j = 0;
        int l =0;
        while(temp[j] != ','){
            if(temp[j]  != ' ' && temp[j] != '<') {
                first1[l] = temp[j];
                l++;
            }
            j++;
        }
        first1 = first1.substr(0,(first1.size())/2);
        edge_result.emplace_back(first1,second);

    }

    edges1 = makeSetOfEdge(edge_result);
    Graph g1(vertex1,edges1);
    gcalc.addGraph(graph_name,&g1);
}

void Parser::dealWithEqual(std::string str, int equal) {
    std::string right_object = str.substr(equal + 1);
    std::string left_object = str.substr(0,equal -1);
    left_object = extractFirstWord(left_object);
    int first_letter = right_object.find_first_of('{');
    int last_letter = right_object.find_first_of(',');
    if (first_letter != std::string::npos) {
        dealWithDefinition(left_object, str, equal);
    } else {

        if (gcalc.isContain(left_object)){

        }
    }


}

size_t Parser::firstLetter(std::string str) {
    for (int i = 0; i < str.size() ; ++i) {
        if (str[i] != ' '){
            break;
        }
        return i;
    }

}

Vertex Parser::makeSetOfVertex(std::vector<std::string> vertex_result) {
    Vertex vertex1;
    std::vector<std::string>::iterator it = vertex_result.begin();
    for (; it != vertex_result.end() ; ++it) {
//        if (checkVertexName(*it)){
            vertex1.addVertex(*it);
//        }
    }
    return vertex1;


}

Edges Parser::makeSetOfEdge(std::vector<std::pair<std::string, std::string>> edge_result) {
    Edges edges1;
    std::vector<std::pair<std::string, std::string>>::iterator it = edge_result.begin();
    for (; it != edge_result.end() ; ++it) {
        edges1.addEdge(*it);
    }
}


#pragma clang diagnostic pop