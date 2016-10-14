//  main.cpp
//  Author: Francis Ricci
//
//  Main runner for quote computation program

#include "json.hpp"
#include "Geometry.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

using json = nlohmann::json;

static void parseJsonFile(std::string &filename, json &jsonObj) {
  std::ifstream inputFile(filename);
  inputFile >> jsonObj;

  assert(jsonObj.count("Edges") == 1);
  json edges = jsonObj["Edges"];

  assert(jsonObj.count("Vertices") == 1);
  json vertices = jsonObj["Vertices"];

  std::unordered_map<int, Point> vertexMap;
  for (json::iterator it = vertices.begin(); it != vertices.end(); ++it) {
    int idx = std::stoul(it.key());
    json coords = it.value();
    Point p(coords["Position"]["X"], coords["Position"]["Y"]);

    vertexMap.emplace(idx, p);
  }

  std::vector<std::shared_ptr<Edge>> edgeVec;
  for (auto const &edge : edges) {
    std::string type = edge["Type"];
    std::vector<unsigned long> vertices = edge["Vertices"];

    Point start = vertexMap.at(vertices[0]);
    Point end = (vertices.size() == 1) ? start : vertexMap.at(vertices[1]);

    if (type == "LineSegment") {
      edgeVec.emplace_back(std::make_shared<StraightEdge>(start, end));
    } else if (type == "CircularArc") {
      Point center(edge["Center"]["X"], edge["Center"]["Y"]);
      edgeVec.emplace_back(std::make_shared<CurvedEdge>(start, end, center));
    } else {
      assert(0);
    }
  }
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

  return 0;
}
