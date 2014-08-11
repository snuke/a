/*
 Interpreter of a programming language "A" (not APL)
 Author: snuke
*/

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "interpreter.h"
using namespace std;

void ReadCode(char* filename, string* result);

int main(int argc, char** argv) {
  if (argc != 2) {
    cerr << "Usage : " << argv[0] << " SOURCE_FILE" << endl;
    return 0;
  }
  string code;
  ReadCode(argv[1], &code);
  Interpreter interpreter;
  interpreter.Run(code, &cin, &cout);
  return 0;
}

void ReadCode(char* filename, string* result) {
  ifstream ifs(filename);
  if (ifs.fail()) {
    cerr << "Error : SOURCE_FILE not found" << endl;
    exit(0);
  }
  string str;
  while (getline(ifs, str)) result->append(str + '\n');
}
