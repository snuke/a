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

const string comment = "Put your code here.";

void ReadCode(const char* filename, string* result);
string Escape(const string& code);

int main(int argc, char** argv) {
  if (argc != 2) {
    cerr << "Usage : " << argv[0] << " SOURCE_FILE" << endl;
    return 0;
  }
  string base, code;
  string dir(argv[0]);
  dir = dir.substr(0, (int)(dir.size() - string("compiler").size()));
  dir += "src/base.cc";
  ReadCode(dir.c_str(), &base);
  ReadCode(argv[1], &code);
  code = Escape(code);
  int pos = base.find(comment);
  base.erase(base.begin() + pos, base.begin() + pos + comment.size());
  base.insert(base.begin() + pos, code.begin(), code.end());
  cout << base;
  return 0;
}

void ReadCode(const char* filename, string* result) {
  ifstream ifs(filename);
  if (ifs.fail()) {
    cerr << "Error : FILE not found" << endl;
    exit(0);
  }
  string str;
  while (getline(ifs, str)) result->append(str + '\n');
}

string Escape(const string& code) {
  string result;
  for (int i = 0; i < (int)code.size(); ++i) {
    if (code[i] == '\n') result += "\\n";
    else if (code[i] == '\?') result += "\\\?";
    else if (code[i] == '\t') result += "\\t";
    else if (code[i] == '\'') result += "\\\'";
    else if (code[i] == '\"') result += "\\\"";
    else if (code[i] == '\\') result += "\\\\";
    else result += code[i];
  }
  return result;
}