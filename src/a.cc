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

void ReadCode(char* filename, std::string* result);

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage : " << argv[0] << " SOURCE_FILE" << std::endl;
    return 0;
  }
  std::string code;
  ReadCode(argv[1], &code);
  Interpreter interpreter;
  interpreter.Run(code, &std::cin, &std::cout);
  return 0;
}

void ReadCode(char* filename, std::string* result) {
  std::ifstream ifs(filename);
  if (ifs.fail()) {
    std::cerr << "Error : SOURCE_FILE not found" << std::endl;
    exit(0);
  }
  std::string str;
  while (std::getline(ifs, str)) result->append(str + '\n');
}