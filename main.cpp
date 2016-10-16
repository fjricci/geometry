//  main.cpp
//  Author: Francis Ricci
//
//  Main runner for quote computation program

#include "Geometry.h"
#include "Profile.h"
#include "json.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

using json = nlohmann::json;

static void parseJsonFile(std::string &filename,
                          std::vector<std::shared_ptr<Edge>> &edgeVec) {
  std::ifstream inputFile(filename);

  json jsonObj;
  inputFile >> jsonObj;

  json edges = jsonObj["Edges"];
  json vertices = jsonObj["Vertices"];

  std::unordered_map<size_t, Point> vertexMap;
  for (json::iterator it = vertices.begin(); it != vertices.end(); ++it) {
    size_t idx = std::stoul(it.key());
    json coords = it.value();
    Point p(coords["Position"]["X"], coords["Position"]["Y"]);

    vertexMap.emplace(idx, p);
  }

  for (auto const &edge : edges) {
    std::string type = edge["Type"];
    std::vector<size_t> vertices = edge["Vertices"];

    Point start = vertexMap.at(vertices[0]);
    Point end = (vertices.size() == 1) ? start : vertexMap.at(vertices[1]);

    if (type == "LineSegment") {
      edgeVec.emplace_back(std::make_shared<StraightEdge>(start, end));
    } else if (type == "CircularArc") {
      Point center(edge["Center"]["X"], edge["Center"]["Y"]);

      // ensure that the starting point of the arc is correct
      if (static_cast<size_t>(edge["ClockwiseFrom"]) != vertices[0]) {
        std::swap(start, end);
      }

      edgeVec.emplace_back(std::make_shared<CurvedEdge>(start, end, center));
    } else {
      throw std::invalid_argument("invalid edge type: " + type);
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

  std::vector<std::shared_ptr<Edge>> edgeVec;
  try {
    parseJsonFile(filename, edgeVec);
  } catch (const std::invalid_argument &e) {
    std::cerr << "error: invalid json file provided" << std::endl;
    exit(EXIT_FAILURE);
  }

  try {
    Profile profile(edgeVec);
    std::cout << "Cost: " << std::setprecision(2) << std::fixed
              << profile.getCost() << std::endl;
  } catch (const std::invalid_argument &e) {
    std::cerr << "error: geometry is invalid" << std::endl;
    exit(EXIT_FAILURE);
  }

  return 0;
}
