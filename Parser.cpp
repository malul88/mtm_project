
#include <cstring>
#include <sstream>
#include "Parser.h"
#include <fstream>
#include <algorithm>// max

using namespace std;

int Parser::checkCmd(string str1) {
    string temp = str1;
    str1 = str1.substr(str1.find(firstLetter(str1)));
    string token, token1, token2;
    stringstream str_temp(str1);
    getline(str_temp, token, ' ');
    stringstream str_temp2(token);
    getline(str_temp2, token1, '(');
    stringstream str_temp3(token1);
    getline(str_temp3, token2, '=');


    if (token2 == "print") {
        size_t firstB = temp.find('(');
        size_t lastB = temp.find(')') - firstB - 1;
        string var = temp.substr(firstB + 1, lastB);
        string operators = "+^-*!";
        char operand = '?';
        size_t find_operand = -2;
        for (char i :operators) {
            find_operand = var.find(i);
            if (find_operand != string::npos) {
                operand = i;
                break;
            }
        }
        if (operand != '?') {
            Graph1 g1 = multipleOperand(var);
            gcalc_temp.clearCalc();
            cout << g1;
            return 0;
        }
        bool valid = CheckArgName(var);
        if (valid) {
            string variable = extractFirstWord(var);
            if (!gcalc.isContain(variable)){
                throw ArgumentNotFound();
            }
            Graph1 graph1 = gcalc.getGraph(variable);
            cout << graph1;
            return 0;
        } else {
            throw WrongGraphName();
        }
    } else if (token2 == "delete") {
        size_t firstB = temp.find('(');
        size_t lastB = temp.find(')') - firstB - 1;
        string var = temp.substr(firstB + 1, lastB);
        bool valid = CheckArgName(var);
        if (valid) {
            string variable = extractFirstWord(var);
            if (!gcalc.isContain(variable)){
                throw ArgumentNotFound();
            }
            gcalc.removeGraph(variable);
            return 0;
        } else {
            throw WrongGraphName();
        }
    } else if (token2 == "who") {
        if (temp.find_first_not_of(' ', temp.find('o') + 1) != string::npos) {
            cout << "Error: Undefined command " << "'" << temp << "'" << endl;
            return 0;
        }
        cout << gcalc;
        return 0;
    } else if (token2 == "reset") {
        if (temp.find_first_not_of(' ', temp.find('t') + 1) != string::npos) {
            cout << "Error: Undefined command " << "'" << temp << "'" << endl;
            return 0;
        }
        gcalc.clearCalc();
        return 0;
    } else if (token2 == "quit") {
        if (temp.find_first_not_of(' ', temp.find('t') + 1) != string::npos) {
            cout << "Error: Undefined command " << "'" << temp << "'" << endl;
            return 0;
        }
        gcalc.clearCalc();
        return 1;
    } else if (token2 == "save") {
        size_t first_S = temp.find_first_of('(');
        size_t last_S = temp.find_first_of(',') - first_S - 1;
        size_t first_F = temp.find_first_of(',');
        size_t last_F = temp.find_first_of(')');
        string object = temp.substr(first_S + 1, last_S);
        object = extractFirstWord(object);
        string file_name = temp.substr(first_F + 1, last_F);
        file_name = extractFirstWord(file_name);
        writeGraphToFile(gcalc.getGraph(object), file_name);
        return 0;
    } else if (temp.find_first_of('=') != string::npos && extractFirstWord(temp.substr(temp.find_first_of('=') + 1)) == "load") {
        size_t first_S = temp.find_first_of('(');
        size_t last_S = temp.find_first_of(')') - first_S - 1;
        string file_name = temp.substr(first_S + 1, last_S);
        file_name = extractFirstWord(file_name);
        Graph1 *g1 = new Graph1;
        *g1 = loadGraphFromFile(file_name);
        if (!CheckArgName(token2)) {
            delete g1;
            throw WrongGraphName();
        }
        if (gcalc.isContain(token2)) {
            gcalc.getGraph(token2) = *g1;
            delete g1;
        } else {
            gcalc.addGraph(token2, g1);
        }
        return 0;
    }
    size_t equal = temp.find_first_of('=');
    if (equal != string::npos) {
        if (temp.find("=", equal + 1) != string::npos) {
            cout << "Error: Undefined command " << "'" << temp << "'" << endl;
            return 0;
        }
        dealWithEqual(token2, temp, equal);
        return 0;
    }
    cout << "Error: Undefined command " << "'" << temp << "'" << endl;
    return 0;
}


bool Parser::CheckArgName(string str) {
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

string Parser::extractFirstWord(basic_string<char> str) {
    size_t first = 0, last = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] != ' ') {
            first = i;
            for (size_t j = i; j < str.size(); ++j) {
                last = j + 1;
                if (str[j] == ' ' || str[j] == '=' || str[j] == '{' || str[j] == '}' || str[j] == '(' || str[j] == ')') {
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

Graph1 *Parser::dealWithDefinition(const string &graph_name, string str, int equal) {
    string right_object = str.substr(str.find('{'));
    size_t last_pos = right_object.find('|') - 1;
    if (last_pos == string::npos - 1) {
        last_pos = right_object.find('}') - 1;
    }
    string vertexes = right_object.substr(1, last_pos);
    size_t first = right_object.find('|') + 1;
    size_t last = right_object.find('}') - first;
    string edge = right_object.substr(first, last);
    Vertex vertex1;
    Edges edges1;
    vector<string> vertex_result;
    stringstream ssv(vertexes);
    int counter2 = 0;
    int counter1 = 0;
    while (ssv.good()) {
        string substring;
        getline(ssv, substring, ',');
        counter2 = 0;
        counter1 = 0;
        while (substring[counter2]) {
            if (substring[counter2] != ' ') {
                substring[counter1] = substring[counter2];
                counter1++;
            }
            counter2++;
        }
        substring = substring.substr(0, counter1);
        if (!vertex1.checkVertexName(substring)) throw WrongVertexName();
        vertex1.addVertex(substring);
    }
    vector<pair<string, string>> edge_result;
    vector<string> edge_temp;
    stringstream sse(edge);
    while (sse.good()) {
        string substring;
        getline(sse, substring, '>');
        edge_temp.push_back(substring);
    }

    for (size_t i = 0; i < edge_temp.size() - 1; ++i) {
        string temp = edge_temp.at(i).substr(edge_temp.at(i).find('<'));
        string first1 = temp.substr(0, temp.find(',') + 1);
        string second = temp.substr(temp.find(',') + 1);
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
    Graph1 g1(vertex1, edges1);
    Graph1 *g2 = new Graph1;
    *g2 = g1;
    return g2;
}

void Parser::dealWithEqual(string left_o, string str, int equal) {
    Graph1 *g1 = new Graph1;
    string right_object = str.substr(equal + 1);
    string left_object = str.substr(0, equal - 1);
    left_object = extractFirstWord(left_object);
    if (!CheckArgName(left_object)) {
        delete g1;
        throw WrongGraphName();
    }
    *g1 = multipleOperand(right_object);
    gcalc_temp.clearCalc();
    if (gcalc.isContain(left_object)) {
        gcalc.getGraph(left_object) = *g1;
        delete g1;
    } else {
        gcalc.addGraph(left_object, g1);
    }
}

char Parser::firstLetter(string str) {
    size_t i = 0;
    for (; i < str.size(); i++) {
        if (str[i] != ' ') {
            break;
        }
    }

    return str[i];
}


Edges Parser::makeSetOfEdge(Vertex vertex, vector<pair<string, string>> edge_result) {
    Edges edges1;
    vector<pair<string, string>>::iterator it = edge_result.begin();
    for (; it != edge_result.end(); ++it) {
        if (gcalc.isGraphContain(vertex, it->first) && gcalc.isGraphContain(vertex, it->second)) {
            edges1.addEdge(*it);
        } else {
            throw VertexNotFound();
        }
    }
    return edges1;
}

Graph1 Parser::complement(string str) {
    str = str.substr(str.find_first_of('!') + 1);
    str = str.substr(str.find(firstLetter(str)));
    if (!CheckArgName(str)) {
        throw WrongGraphName();
    }
    size_t last = str.find(' ');
    str = str.substr(0, last);
    Graph1 g1 = gcalc.getGraph(str);
    return !g1;
}



Graph1 Parser::multipleOperand(string basicString) {
    vector<char> vec_operands;
    vector<string> vec_var;
    string var = basicString;
    basicString += '+';
    int length = 0;
    int first_index = -1;
    size_t next = basicString.size() + 1;
    bool visit = true;
    for (size_t i = 0; i < basicString.size(); ++i) {
        if (basicString[i] == '{') {
            string temp = to_string(counter++);
            Graph1 *g_temp = dealWithDefinition(temp, basicString.substr(i), 0); // add delete to end
            gcalc_temp.addGraph(temp, g_temp);
            if (basicString.find_first_of('+', i) != string::npos && basicString.find_first_of('+', i) != basicString.size())
                next = basicString.find_first_of('+', i);
            if (basicString.find_first_of('*', i) != string::npos) next = min<int>(next, basicString.find_first_of('*', i));
            if (basicString.find_first_of('^', i) != string::npos) next = min<int>(next, basicString.find_first_of('^', i));
            if (basicString.find_first_of('-', i) != string::npos)next = min<int>(next, basicString.find_first_of('-', i));
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
    return binaryExpression(vec_operands, vec_var);
}


Graph1 Parser::binaryExpression(vector<char> vec_operands, vector<string> vec_var) {
    Graph1 g1;
    Graph1 g_temp_com;
    string operands = "+^-*!";
    char operand;
    int var_index = 0;
    bool com = false;
    bool first_com = false;
    bool is_temp = false;
    string graph_name;
    Graph1 graph_temp;
    if (vec_operands.empty()&& !gcalc_temp.isEmpty()) {
        g1 = gcalc_temp.getGraph(vec_var[0]);
        return g1;
    }
    if (vec_operands.empty()&& gcalc_temp.isEmpty()) {
        g1 =  gcalc.getGraph(vec_var[0]);
        return g1;

    }
    for (size_t i = 0; i < vec_operands.size(); ++i) {
        operand = vec_operands.at(i);
        Graph1 gtemp;
        is_temp = isdigit((vec_var[var_index])[0]);
        if (is_temp) {
            graph_temp = gcalc_temp.getGraph(vec_var[var_index]);
        }

        if (!is_temp && !CheckArgName(vec_var[var_index])) {
            throw WrongGraphName();
        }
        if (i + 1 < vec_operands.size() && vec_operands.at(i + 1) == '!') {
            if (is_temp) {
                if (i != 0) g_temp_com = !graph_temp;
                if (i == 0) {
                    graph_temp = gcalc_temp.getGraph(vec_var[var_index + 1]);
                    g_temp_com = !graph_temp;
                }
            } else {
                if (i == 0) g_temp_com = complement(vec_var[var_index + 1]);
                if (i != 0) g_temp_com = complement(vec_var[var_index]);
            }
            com = true;
            i++;
        }
        if (operand == '+') {
            if (com && gcalc.isContain(vec_var[var_index])) { // +!
                if (i - 1 == 0 && gcalc.isContain(vec_var[var_index]) && gcalc.isContain(vec_var[var_index + 1])) {
                    g1 = gUnion(gcalc.getGraph(vec_var[var_index]), g_temp_com);
                    var_index += 2;
                } else {
                    g1 = gUnion(g1, g_temp_com);
                    var_index++;
                }
                com =false;
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
                is_temp = isdigit((vec_var[var_index + 1])[0]);
                if (!is_temp) {
                    gtemp = gUnion(graph_temp, gcalc.getGraph(vec_var[var_index + 1])); // first iter
                } else {
                    gtemp = gUnion(graph_temp, gcalc_temp.getGraph(vec_var[var_index + 1])); // first iter
                }
                g1 = gtemp;
                var_index += 2;
            } else if (i == 0 && isdigit((vec_var[var_index + 1])[0]) && gcalc.isContain(vec_var[var_index])) {
                g1 = gUnion(gcalc.getGraph(vec_var[var_index]), gcalc_temp.getGraph(vec_var[var_index + 1])); // first iter
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
                if (i - 1 == 0 && gcalc.isContain(vec_var[var_index]) && gcalc.isContain(vec_var[var_index + 1])) {
                    g1 = gIntersection(gcalc.getGraph(vec_var[var_index]), g_temp_com);
                    var_index += 2;
                } else {
                    g1 = gIntersection(g1, g_temp_com);
                    var_index++;
                }
                com =false;

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
                is_temp = isdigit((vec_var[var_index + 1])[0]);
                if (!is_temp) {
                    gtemp = gIntersection(graph_temp, gcalc.getGraph(vec_var[var_index + 1])); // first iter
                } else {
                    gtemp = gIntersection(graph_temp, gcalc_temp.getGraph(vec_var[var_index + 1])); // first iter
                }
                g1 = gtemp;
                var_index += 2;
            } else if (i == 0 && isdigit((vec_var[var_index + 1])[0]) && gcalc.isContain(vec_var[var_index])) {
                g1 = gIntersection(gcalc.getGraph(vec_var[var_index]), gcalc_temp.getGraph(vec_var[var_index + 1])); // first iter
                var_index += 2;

            } else if (gcalc.isContain(vec_var[var_index])) { // some iter
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
                if (i - 1 == 0 && gcalc.isContain(vec_var[var_index]) && gcalc.isContain(vec_var[var_index + 1])) {
                    g1 = gDifference(gcalc.getGraph(vec_var[var_index]), g_temp_com);
                    var_index += 2;
                } else {
                    g1 = gDifference(g1, g_temp_com);
                    var_index++;
                }
                com =false;

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
                is_temp = isdigit((vec_var[var_index + 1])[0]);
                if (!is_temp) {
                    gtemp = gDifference(graph_temp, gcalc.getGraph(vec_var[var_index + 1])); // first iter
                } else {
                    gtemp = gDifference(graph_temp, gcalc_temp.getGraph(vec_var[var_index + 1])); // first iter
                }
                g1 = gtemp;
                var_index += 2;
            } else if (i == 0 && isdigit((vec_var[var_index + 1])[0]) && gcalc.isContain(vec_var[var_index])) {
                g1 = gDifference(gcalc.getGraph(vec_var[var_index]), gcalc_temp.getGraph(vec_var[var_index + 1])); // first iter
                var_index += 2;

            } else if (gcalc.isContain(vec_var[var_index])) { // some iter
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
                if (i - 1 == 0 && gcalc.isContain(vec_var[var_index]) && gcalc.isContain(vec_var[var_index + 1])) {
                    g1 = gProduct(gcalc.getGraph(vec_var[var_index]), g_temp_com);
                    var_index += 2;
                } else {
                    g1 = gProduct(g1, g_temp_com);
                    var_index++;
                }
                com =false;

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
                is_temp = isdigit((vec_var[var_index + 1])[0]);
                if (!is_temp) {
                    gtemp = gProduct(graph_temp, gcalc.getGraph(vec_var[var_index + 1])); // first iter
                } else {
                    gtemp = gProduct(graph_temp, gcalc_temp.getGraph(vec_var[var_index + 1])); // first iter
                }
                g1 = gtemp;
                var_index += 2;
            } else if (i == 0 && isdigit((vec_var[var_index + 1])[0]) && gcalc.isContain(vec_var[var_index])) {
                g1 = gProduct(gcalc.getGraph(vec_var[var_index]), gcalc_temp.getGraph(vec_var[var_index + 1])); // first iter
                var_index += 2;

            } else if (gcalc.isContain(vec_var[var_index])) { // some iter
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


Graph1 Parser::gUnion(string left, string right) {
    Graph1 g1 = gcalc.getGraph(left);
    Graph1 g2 = gcalc.getGraph(right);
    Graph1 g3 = g1 + g2;
    return g3;

}

Graph1 Parser::gUnion(Graph1 &g1, Graph1 &g2) {
    Graph1 g3 = g1 + g2;
    return g3;

}

Graph1 Parser::gIntersection(string left, string right) {
    Graph1 g1 = gcalc.getGraph(left);
    Graph1 g2 = gcalc.getGraph(right);
    Graph1 g3 = g1 ^g2;
    return g3;
}

Graph1 Parser::gIntersection(Graph1 &g1, Graph1 &g2) {
    Graph1 g3 = g1 ^g2;
    return g3;
}

Graph1 Parser::gDifference(string left, string right) {
    Graph1 g1 = gcalc.getGraph(left);
    Graph1 g2 = gcalc.getGraph(right);
    Graph1 g3 = g1 - g2;
    return g3;
}

Graph1 Parser::gDifference(Graph1 &g1, Graph1 &g2) {
    Graph1 g3 = g1 - g2;
    return g3;
}

Graph1 Parser::gProduct(string left, string right) {
    Graph1 g1 = gcalc.getGraph(left);
    Graph1 g2 = gcalc.getGraph(right);
    Graph1 g3 = g1 * g2;
    return g3;
}

Graph1 Parser::gProduct(Graph1 &g1, Graph1 &g2) {
    Graph1 g3 = g1 * g2;
    return g3;
}

void Parser::addGraph(string graph_name, Graph1 *graph) {
    gcalc.addGraph(graph_name, graph);
}

void Parser::writeGraphToFile(Graph1 &graph, string file_name) {
    graph.WriteGraphToFile(graph, file_name);

}

Graph1 Parser::loadGraphFromFile(string file_name) {
    ifstream infile(file_name, ios_base::binary);
    if (!infile) {
        throw CantOpenFile();
    }
    int num_vertex, num_edge, size;
    infile.read((char *) &num_vertex, sizeof(int));
    infile.read((char *) &num_edge, sizeof(int));
    Vertex vertex;
    Edges edges;
    for (int i = 0; i < num_vertex; ++i) {
        infile.read((char *) &size, sizeof(int));
        char *buffer1 = new char[size + 1];
        infile.read(buffer1, size * sizeof(char));
        buffer1[size] = '\0';
        vertex.addVertex(string(buffer1));
        delete[] buffer1;
    }
    for (int i = 0; i < num_edge; ++i) {
        pair<string, string> edge;
        infile.read((char *) &size, sizeof(int));
        char *buffer1 = new char[size + 1];
        infile.read(buffer1, size);
        buffer1[size] = '\0';
        edge.first = string(buffer1);
        infile.read((char *) &size, sizeof(int));
        char *buffer2 = new char[size + 1];
        infile.read(buffer2, size);
        buffer2[size] = '\0';
        edge.second = string(buffer2);
        edges.addEdge(edge);
        delete[] buffer1;
        delete[] buffer2;
    }
    Graph1 g1(vertex, edges);
    return g1;
}


