//  main.cpp
//  Author: Francis Ricci
//
//  Main runner for quote computation program

#include "json.hpp"

#include <fstream>
#include <iostream>
#include <string>

using json = nlohmann::json;

static void parseJsonFile(std::string &filename, json &jsonObj) {
  std::ifstream inputFile(filename);
  inputFile >> jsonObj;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "usage: geometry profile.json" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string filename(argv[1]);
  std::cout << "computing quote for: " << filename << std::endl;

  json jsonObj;
  parseJsonFile(filename, jsonObj);

  std::cout << "using json data:" << std::endl;
  std::cout << jsonObj.dump(4) << std::endl;

  return 0;
}
