#include <iostream>
#include <string>
#include "Vertex.h"
#include "Edges.h"
#include "Graph1.h"
#include "Gcalc.h"
#include "Parser.h"
#include <fstream>

using std::ifstream;
using std::ofstream;
using namespace std;

int main(int argc, char *argv[]) {
    int cmdResult = 0;
    Gcalc gcalc;
    Parser pars(gcalc);
    if (argc == 3) {
        ifstream input;
        input.open(argv[1], ios_base::in);
        if (!input) {
            cout << "Error: cannot open input file" << endl;
            return 0;
        }
        streambuf *psbuf;
        ofstream filestr;
        filestr.open(argv[2]);
        psbuf = filestr.rdbuf(); // get file's streambuf
        cout.rdbuf(psbuf);       // assign streambuf to cout
        string command;
        while (!input.eof() && !cmdResult) {
            getline(input, command);
            if (command.size() == 0){
                continue;
            }
            try {
                cmdResult = pars.checkCmd(command);
            }
            catch (const Exception &e) {
                cout << e.what() << endl;
            }
        }
        filestr.close();
        input.close();
        return 0;
    } else if (argc == 1) {
        string command;
        while (!cmdResult) {
            cout << "Gcalc>";
            getline(cin, command);
            if (command.size() == 0){
                continue;
            }
            try {
                cmdResult = pars.checkCmd(command);
            }
            catch (const Exception &e) {
                cout << e.what() << endl;
            }
        }
    } else {
        cout << "Error: 1 or more than two arguments supplied" << endl;
        return 0;
    }
    return 0;
}
