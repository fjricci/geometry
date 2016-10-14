//  main.cpp
//  Author: Francis Ricci
//
//  Main runner for quote computation program

#include <iostream>
#include <string>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "usage: geometry profile.json" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string filename(argv[1]);
  std::cout << "computing quote for " << filename << std::endl;
  return 0;
}
