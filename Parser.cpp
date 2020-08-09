
#include <cstring>
#include <sstream>
#include "Parser.h"
#include "Graph.h"
#include <algorithm>    // std::max


int Parser::checkCmd(std::string str1) {
    std::string temp = str1;
    str1 = str1.substr(str1.find(firstLetter(str1)));
    std::string token, token1, token2;
    std::stringstream str_temp(str1);
    std::getline(str_temp, token, ' ');
    std::stringstream str_temp2(token);
    std::getline(str_temp2, token1, '(');
    std::stringstream str_temp3(token1);
    std::getline(str_temp3, token2, '=');


    if (token2 == "print") {
        size_t firstB = temp.find('(');
        size_t lastB = temp.find(')') - firstB - 1;
        std::string var = temp.substr(firstB + 1, lastB);
        std::string operators = "+^-*!";
        char operand = '?';
        size_t find_operand = -2;
        for (char i :operators) {
            find_operand = var.find(i);
            if (find_operand != std::string::npos) {
                operand = i;
                break;
            }
        }
        if (operand != '?') {
            Graph g1 = multipleOperand(var);
            std::cout << g1;
            return 0;
        }
        bool valid = CheckArgName(var);
        if (valid) {
            std::string variable = extractFirstWord(var);
            Graph graph1 = gcalc.getGraph(variable);
            std::cout << graph1;
            return 0;
        } else {
            throw IllegalArgument();
        }
    } else if (token2 == "delete") {
        size_t firstB = temp.find('(');
        size_t lastB = temp.find(')') - firstB - 1;
        std::string var = temp.substr(firstB + 1, lastB);
        bool valid = CheckArgName(var);
        if (valid) {
            std::string variable = extractFirstWord(var);
            gcalc.removeGraph(variable);
            return 0;
        } else {
            throw IllegalArgument();
        }
    } else if (token2 == "who") {
        std::cout << gcalc;
        return 0;
    } else if (token2 == "reset") {
        gcalc.clearCalc();
        return 0;
    } else if (token2 == "quit") {
        gcalc.clearCalc();
        return 1;
    }
    size_t equal = temp.find_first_of('=');
    if (equal != std::string::npos) {
        dealWithEqual(token2, temp, equal);
        return 0;
    }
    std::cout << "Error: Undefined command " << "'" << temp << "'" << std::endl;
    return 0;
}


bool Parser::CheckArgName(std::string str) {
    int first_char = -1;
    bool valid = true;
    for (size_t i = 0; i < str.size(); ++i) {
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
            for (size_t j = i; j < str.size(); ++j) {
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
    size_t first = 0, last = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] != ' ') {
            first = i;
            for (size_t j = i; j < str.size(); ++j) {
                last = j + 1;
                if (str[j] == ' ' || str[j] == '=' || str[j] == '{') {
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

Graph *Parser::dealWithDefinition(const std::string &graph_name, std::string str, int equal) {
//    if (!CheckArgName(graph_name)) {
//        throw WrongGraphName();
//    }
    std::string right_object = str.substr(str.find('{'));
    size_t last_pos = right_object.find('|') - 1;
    if (last_pos == std::string::npos - 1) {
        last_pos = right_object.find('}') - 1;
    }
    std::string vertexes = right_object.substr(1, last_pos);
    size_t first = right_object.find('|') + 1;
    size_t last = right_object.find('}') - first;
    std::string edge = right_object.substr(first, last);
    Vertex vertex1;
    Edges edges1;
    std::vector<std::string> vertex_result;
    std::stringstream ssv(vertexes);
    int counter = 0;
    int counter1 = 0;
    while (ssv.good()) {
        std::string substring;
        std::getline(ssv, substring, ',');
        counter = 0;
        counter1 = 0;
        while (substring[counter]) {
            if (substring[counter] != ' ') {
                substring[counter1] = substring[counter];
                counter1++;
            }
            counter++;
        }
        substring = substring.substr(0, counter1);
        if (!vertex1.checkVertexName(substring)) throw WrongVertexName();
        vertex1.addVertex(substring);
    }
    std::vector<std::pair<std::string, std::string>> edge_result;
    std::vector<std::string> edge_temp;
    std::stringstream sse(edge);
    while (sse.good()) {
        std::string substring;
        std::getline(sse, substring, '>');
        edge_temp.push_back(substring);
    }

    for (size_t i = 0; i < edge_temp.size() - 1; ++i) {
        std::string temp = edge_temp.at(i).substr(edge_temp.at(i).find('<'));
        std::string first1 = temp.substr(0, temp.find(',') + 1);
        std::string second = temp.substr(temp.find(',') + 1);
        int j = 0;
        int l = 0;
        while (temp[j] != ',') {
            if (temp[j] != ' ' && temp[j] != '<') {
                first1[l] = temp[j];
                l++;
            }
            j++;
        }
        first1 = first1.substr(0, l);
        j = 0;
        l = 0;
        while (second[j]) {
            if (second[j] != ' ') {
                second[l] = second[j];
                l++;
            }
            j++;
        }
        second = second.substr(0, l);
        edge_result.emplace_back(first1, second);
    }
    edges1 = makeSetOfEdge(vertex1, edge_result);
    Graph g1(vertex1, edges1);
    Graph *g2 = new Graph;
    *g2 = g1;
    return g2;
}

void Parser::dealWithEqual(std::string left_o, std::string str, int equal) {
    Graph *g1 = new Graph;
    std::string right_object = str.substr(equal + 1);
    std::string left_object = str.substr(0, equal - 1);
    left_object = extractFirstWord(left_object);
    if (!CheckArgName(left_object)) {
        delete g1;
        throw WrongGraphName();
    }
    // size_t first_letter = right_object.find_first_of('{');
    *g1 = multipleOperand(right_object);
    if (gcalc.isContain(left_object)) {
        gcalc.getGraph(left_object) = *g1;
        delete g1;
    } else {
        gcalc.addGraph(left_object, g1);
    }
}

char Parser::firstLetter(std::string str) {
    size_t i = 0;
    for (; i < str.size(); i++) {
        if (str[i] != ' ') {
            break;
        }
    }

    return str[i];
}


Edges Parser::makeSetOfEdge(Vertex vertex, std::vector<std::pair<std::string, std::string>> edge_result) {
    Edges edges1;
    std::vector<std::pair<std::string, std::string>>::iterator it = edge_result.begin();
    for (; it != edge_result.end(); ++it) {
        if (gcalc.isGraphContain(vertex, it->first) && gcalc.isGraphContain(vertex, it->second)) {
            edges1.addEdge(*it);
        }
    }
    return edges1;
}

Graph Parser::complement(std::string str) {
    str = str.substr(str.find_first_of('!') + 1);
    str = str.substr(str.find(firstLetter(str)));
    if (!CheckArgName(str)) {
        throw WrongGraphName();
    }
    size_t last = str.find(' ');
    str = str.substr(0, last);
    Graph g1 = gcalc.getGraph(str);
    return !g1;
}


//Graph Parser::stringToGraph(std::string string){
//
//}



Graph Parser::multipleOperand(std::string basicString) {
    std::vector<char> vec_operands;
    std::vector<std::string> vec_var;
    std::string var = basicString;
    basicString += '+';
    int length = 0;
    int first_index = -1;
    size_t next = basicString.size() + 1;
    bool visit = true;
    for (size_t i = 0; i < basicString.size(); ++i) {
        if (basicString[i] == '{') {
            std::string temp = std::to_string(counter++);
            Graph *g_temp = dealWithDefinition(temp, basicString.substr(i), 0); // add delete to end
            gcalc_temp.addGraph(temp, g_temp);
            if (basicString.find_first_of('+', i) != std::string::npos && basicString.find_first_of('+', i) != basicString.size())
                next = basicString.find_first_of('+', i);
            if (basicString.find_first_of('*', i) != std::string::npos) next = std::min<int>(next, basicString.find_first_of('*', i));
            if (basicString.find_first_of('^', i) != std::string::npos) next = std::min<int>(next, basicString.find_first_of('^', i));
            if (basicString.find_first_of('-', i) != std::string::npos)next = std::min<int>(next, basicString.find_first_of('-', i));
            vec_var.push_back(temp);
            i = next - 1;
            visit = false;
            continue;
        }
        if (basicString[i] != '+' && basicString[i] != '-' && basicString[i] != '^' && basicString[i] != '!'
            && basicString[i] != '*' && basicString[i] != ' ') {
            if (first_index == -1) first_index = i;
            length++;
            visit = true;
            continue;
        }
        if (basicString[i] == '+' || basicString[i] == '-' || basicString[i] == '^'
            || basicString[i] == '*') {
            if (i != basicString.size() - 1) vec_operands.push_back(basicString[i]);
            if (visit) {
                var = var.substr(first_index, length);
                first_index = -1;
                vec_var.push_back(var);
                var = basicString;
                length = 0;
            }
            continue;

        }
        if (basicString[i] == '!') vec_operands.push_back(basicString[i]);;
    }
    return binaryExpression(vec_operands, vec_var);//todo add temp_vec
}


Graph Parser::binaryExpression(std::vector<char> vec_operands, std::vector<std::string> vec_var) {
    Graph g1;
    Graph g_temp_com;
    std::string operands = "+^-*!";
    char operand;
    int var_index = 0;
    bool com = false;
    bool first_com = false;
    bool is_temp = false;
    std::string graph_name;
    Graph graph_temp;
    if (vec_operands.empty()) {
        return gcalc_temp.getGraph(vec_var[0]);
    }
    for (size_t i = 0; i < vec_operands.size(); ++i) {
        operand = vec_operands.at(i);
        Graph gtemp;
        is_temp = std::isdigit((vec_var[var_index])[0]); // need to check TODO 
        if (is_temp) {
            graph_temp = gcalc_temp.getGraph(vec_var[var_index]);
        }

        if (!is_temp && !CheckArgName(vec_var[var_index])) {
            throw WrongGraphName();
        }
        if (i + 1 < vec_operands.size() && vec_operands.at(i + 1) == '!') {
            if (is_temp) {
                g_temp_com = !graph_temp;
            } else {
                g_temp_com = complement(vec_var[var_index]);
            }
            com = true;
            i++;
        }
        if (operand == '+') {
            if (com && gcalc.isContain(vec_var[var_index])) { // +!
                g1 = gUnion(g1, g_temp_com);
                var_index++;
            } else if (com && is_temp) {
                g1 = gUnion(g1, g_temp_com);
                var_index++;
            } else if (first_com && gcalc.isContain(vec_var[var_index])) { // ! first operator
                g1 = gUnion(gcalc.getGraph(vec_var[var_index]), g1);
                var_index++;
            } else if (first_com && is_temp) {
                g1 = gUnion(graph_temp, g1);
                var_index++;
            } else if (i == 0 && gcalc.isContain(vec_var[var_index]) && gcalc.isContain(vec_var[var_index + 1])) {
                gtemp = gUnion(vec_var[var_index], vec_var[var_index + 1]); // first iter
                g1 = gtemp;
                var_index += 2;
            }//add first not temp second temp
            else if (i == 0 && is_temp) {
                is_temp = std::isdigit((vec_var[var_index + 1])[0]);
                if (!is_temp) {
                    gtemp = gUnion(graph_temp, gcalc.getGraph(vec_var[var_index + 1])); // first iter
                } else {
                    gtemp = gUnion(graph_temp, gcalc_temp.getGraph(vec_var[var_index + 1])); // first iter
                }
                g1 = gtemp;
                var_index += 2;
            } else if (i == 0 && std::isdigit((vec_var[var_index + 1])[0]) && gcalc.isContain(vec_var[var_index])) {
                gtemp = gUnion(gcalc.getGraph(vec_var[var_index]), gcalc_temp.getGraph(vec_var[var_index + 1])); // first iter
                var_index += 2;

            } else if (gcalc.isContain(vec_var[var_index])) { // some iter
                gtemp = gUnion(gcalc.getGraph(vec_var[var_index]), g1);
                g1 = gtemp;
                var_index++;
            } else if (is_temp) {
                gtemp = gUnion(graph_temp, g1);
                g1 = gtemp;
                var_index++;
            } else {
                throw ArgumentNotFound();
            }
        } else if (operand == '^') {
            if (com && gcalc.isContain(vec_var[var_index])) { // +!
                g1 = gIntersection(g1, g_temp_com);
                var_index++;
            } else if (com && is_temp) {
                g1 = gIntersection(g1, g_temp_com);
                var_index++;
            } else if (first_com && gcalc.isContain(vec_var[var_index])) { // ! first operator
                g1 = gIntersection(gcalc.getGraph(vec_var[var_index]), g1);
                var_index++;
            } else if (first_com && is_temp) {
                g1 = gIntersection(graph_temp, g1);
                var_index++;
            } else if (i == 0 && gcalc.isContain(vec_var[var_index]) && gcalc.isContain(vec_var[var_index + 1])) {
                gtemp = gIntersection(vec_var[var_index], vec_var[var_index + 1]); // first iter
                g1 = gtemp;
                var_index += 2;
            } else if (i == 0 && is_temp) {
                is_temp = std::isdigit((vec_var[var_index + 1])[0]);
                if (!is_temp) {
                    gtemp = gIntersection(graph_temp, gcalc.getGraph(vec_var[var_index + 1])); // first iter
                } else {
                    gtemp = gIntersection(graph_temp, gcalc_temp.getGraph(vec_var[var_index + 1])); // first iter
                }
                g1 = gtemp;
                var_index += 2;
            } else if (i == 0 && std::isdigit((vec_var[var_index + 1])[0]) && gcalc.isContain(vec_var[var_index])) {
                gtemp = gIntersection(gcalc.getGraph(vec_var[var_index]), gcalc_temp.getGraph(vec_var[var_index + 1])); // first iter
                var_index += 2;

            }else if (gcalc.isContain(vec_var[var_index])) { // some iter
                gtemp = gIntersection(gcalc.getGraph(vec_var[var_index]), g1);
                g1 = gtemp;
                var_index++;
            } else if (is_temp) {
                gtemp = gIntersection(graph_temp, g1);
                g1 = gtemp;
                var_index++;
            } else {
                throw ArgumentNotFound();
            }
        } else if (operand == '-') {
            if (com && gcalc.isContain(vec_var[var_index])) { // +!
                g1 = gDifference(g1, g_temp_com);
                var_index++;
            } else if (com && is_temp) {
                g1 = gDifference(g1, g_temp_com);
                var_index++;
            } else if (first_com && gcalc.isContain(vec_var[var_index])) { // ! first operator
                g1 = gDifference(g1, gcalc.getGraph(vec_var[var_index]));
                var_index++;
            } else if (first_com && is_temp) {
                g1 = gDifference(g1, graph_temp);
                var_index++;
            } else if (i == 0 && gcalc.isContain(vec_var[var_index]) && gcalc.isContain(vec_var[var_index + 1])) {
                gtemp = gDifference(vec_var[var_index], vec_var[var_index + 1]); // first iter
                g1 = gtemp;
                var_index += 2;
            } else if (i == 0 && is_temp) {
                is_temp = std::isdigit((vec_var[var_index + 1])[0]);
                if (!is_temp) {
                    gtemp = gDifference(graph_temp, gcalc.getGraph(vec_var[var_index + 1])); // first iter
                } else {
                    gtemp = gDifference(graph_temp, gcalc_temp.getGraph(vec_var[var_index + 1])); // first iter
                }
                g1 = gtemp;
                var_index += 2;
            } else if (i == 0 && std::isdigit((vec_var[var_index + 1])[0]) && gcalc.isContain(vec_var[var_index])) {
                gtemp = gDifference(gcalc.getGraph(vec_var[var_index]), gcalc_temp.getGraph(vec_var[var_index + 1])); // first iter
                var_index += 2;

            }else if (gcalc.isContain(vec_var[var_index])) { // some iter
                gtemp = gDifference(g1, gcalc.getGraph(vec_var[var_index]));
                g1 = gtemp;
                var_index++;
            } else if (is_temp) {
                gtemp = gDifference(g1, graph_temp);
                g1 = gtemp;
                var_index++;
            } else {
                throw ArgumentNotFound();
            }
        } else if (operand == '*') {
            if (com && gcalc.isContain(vec_var[var_index])) { // +!
                g1 = gProduct(g1, g_temp_com);
                var_index++;
            } else if (com && is_temp) {
                g1 = gProduct(g1, g_temp_com);
                var_index++;
            } else if (first_com && gcalc.isContain(vec_var[var_index])) { // ! first operator
                g1 = gProduct(g1, gcalc.getGraph(vec_var[var_index]));
                var_index++;
            } else if (first_com && is_temp) {
                g1 = gProduct(g1, graph_temp);
                var_index++;
            } else if (i == 0 && gcalc.isContain(vec_var[var_index]) && gcalc.isContain(vec_var[var_index + 1])) {
                gtemp = gProduct(vec_var[var_index], vec_var[var_index + 1]); // first iter
                g1 = gtemp;
                var_index += 2;
            } else if (i == 0 && is_temp) {
                is_temp = std::isdigit((vec_var[var_index + 1])[0]);
                if (!is_temp) {
                    gtemp = gProduct(graph_temp, gcalc.getGraph(vec_var[var_index + 1])); // first iter
                } else {
                    gtemp = gProduct(graph_temp, gcalc_temp.getGraph(vec_var[var_index + 1])); // first iter
                }
                g1 = gtemp;
                var_index += 2;
            } else if (i == 0 && std::isdigit((vec_var[var_index + 1])[0]) && gcalc.isContain(vec_var[var_index])) {
                gtemp = gProduct(gcalc.getGraph(vec_var[var_index]), gcalc_temp.getGraph(vec_var[var_index + 1])); // first iter
                var_index += 2;

            }else if (gcalc.isContain(vec_var[var_index])) { // some iter
                gtemp = gProduct(g1, gcalc.getGraph(vec_var[var_index]));
                g1 = gtemp;
                var_index++;
            } else if (is_temp) {
                gtemp = gProduct(g1, graph_temp);
                g1 = gtemp;
                var_index++;
            } else {
                throw ArgumentNotFound();
            }
        } else if (operand == '!') {
            if (gcalc.isContain(vec_var[var_index])) {
                gtemp = complement(vec_var[var_index]);
                g1 = g1 + gtemp;
                var_index++;
                first_com = true;

            } else if (is_temp) {
                g1 = g1 + !graph_temp; // check if we need +g1 or not
                var_index++;
                first_com = true;

            } else {
                throw ArgumentNotFound();
            }
        }
    }


    return
            g1;
}










//Graph Parser::binaryExpression(std::string str) {
//    std::string operands ="+^-*";
//    char operand;
//   for (char i :operands) {
//         int find_operand = str.find(i);
//        if (find_operand != std::string::npos ){
//            operand = i;
//            break;
//        }
//    }
//    Graph g1  ;
//    std::string temp = str;
//    str = str.substr(str.find(firstLetter(str)));
//    std::string left_o = str.substr(0,str.find(operand)-1);
//    int first = str.find(operand) + 1;
//    std::string right_o = str.substr(first);
//    right_o = right_o.substr(right_o.find(firstLetter(right_o)));
//    if (!CheckArgName(right_o) || !CheckArgName(left_o)){
//        throw WrongGraphName();
//    }
//    if (operand == '+'){
//        if (gcalc.isContain(left_o) && gcalc.isContain(right_o)) {
//            g1 = gUnion(left_o, right_o);
//            return g1;
//        } else {
//            throw ArgumentNotFound();
//        }
//    }else if (operand == '^'){
//        if (gcalc.isContain(left_o) && gcalc.isContain(right_o)) {
//            g1 = gIntersection(left_o, right_o);
//            return g1;
//        } else{
//            throw ArgumentNotFound();
//        }
//    } else if (operand == '-'){
//        if (gcalc.isContain(left_o) && gcalc.isContain(right_o)) {
//            g1 = gDifference(left_o, right_o);
//            return g1;
//        } else{
//            throw ArgumentNotFound();
//        }
//    } else if (operand == '*'){
//        if (gcalc.isContain(left_o) && gcalc.isContain(right_o)) {
//            g1 = gProduct(left_o, right_o);
//            return g1;
//        } else{
//            throw ArgumentNotFound();
//        }
//    }
//    else if(operand == '!') return complement(str);
//
//
//    throw Exception();
//}

Graph Parser::gUnion(std::string left, std::string right) {
    Graph g1 = gcalc.getGraph(left);
    Graph g2 = gcalc.getGraph(right);
    Graph g3 = g1 + g2;
    return g3;

}

Graph Parser::gUnion(Graph &g1, Graph &g2) {
    Graph g3 = g1 + g2;
    return g3;

}

Graph Parser::gIntersection(std::string left, std::string right) {
    Graph g1 = gcalc.getGraph(left);
    Graph g2 = gcalc.getGraph(right);
    Graph g3 = g1 ^g2;
    return g3;
}

Graph Parser::gIntersection(Graph &g1, Graph &g2) {
    Graph g3 = g1 ^g2;
    return g3;
}

Graph Parser::gDifference(std::string left, std::string right) {
    Graph g1 = gcalc.getGraph(left);
    Graph g2 = gcalc.getGraph(right);
    Graph g3 = g1 - g2;
    return g3;
}

Graph Parser::gDifference(Graph &g1, Graph &g2) {
    Graph g3 = g1 - g2;
    return g3;
}

Graph Parser::gProduct(std::string left, std::string right) {
    Graph g1 = gcalc.getGraph(left);
    Graph g2 = gcalc.getGraph(right);
    Graph g3 = g1 * g2;
    return g3;
}

Graph Parser::gProduct(Graph &g1, Graph &g2) {
    Graph g3 = g1 * g2;
    return g3;
}

void Parser::addGraph(std::string graph_name, Graph *graph) {
    gcalc.addGraph(graph_name, graph);
}


