//  Profile.cpp
//  Author: Francis Ricci

#include "Profile.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

#define PADDING_SIZE 0.1
#define MATERIAL_COST 0.75
#define MAX_SPEED 0.5
#define TIME_COST 0.07

Profile::Profile(std::vector<std::shared_ptr<Edge>> edges) : _profile(edges) {
  if (!isValid()) {
    throw std::invalid_argument("invalid geometry provided");
  }

  _cost = computeTimeCost() + computeAreaCost();
}

double Profile::computeTimeCost() const {
  double timeCost = 0;

  for (auto edge : _profile) {
    double r = edge->getRadius();
    double len = edge->getLength();

    double modLen = (r == 0) ? len : len / exp(-1 / r);

    timeCost += (TIME_COST / MAX_SPEED) * modLen;
  }

  return timeCost;
}

double Profile::computeAreaCost() const {
  std::vector<double> xMinVals;
  std::vector<double> yMinVals;
  std::vector<double> xMaxVals;
  std::vector<double> yMaxVals;

  for (auto edge : _profile) {
    xMinVals.push_back(edge->getMinX());
    yMinVals.push_back(edge->getMinY());
    xMaxVals.push_back(edge->getMaxX());
    yMaxVals.push_back(edge->getMaxY());
  }

  double xMin = *std::min_element(xMinVals.begin(), xMinVals.end());
  double yMin = *std::min_element(yMinVals.begin(), yMinVals.end());
  double xMax =
      *std::max_element(xMaxVals.begin(), xMaxVals.end()) + PADDING_SIZE;
  double yMax =
      *std::max_element(yMaxVals.begin(), yMaxVals.end()) + PADDING_SIZE;

  return (xMax - xMin) * (yMax - yMin) * MATERIAL_COST;
}

bool Profile::isValid() const {
  Point start = _profile[0]->getStart();
  Point current = _profile[0]->getEnd();

  std::vector<std::shared_ptr<Edge>> edges(_profile.begin() + 1,
                                           _profile.end());
  while (!edges.empty()) {
    bool found = false;

    for (auto it = edges.begin(); it != edges.end(); ++it) {
      if (current == (*it)->getStart()) {
        current = (*it)->getEnd();
        edges.erase(it);
        found = true;
        break;
      } else if (current == (*it)->getEnd()) {
        current = (*it)->getStart();
        edges.erase(it);
        found = true;
        break;
      }
    }

    if (!found) {
      return false;
    }
  }

  return (start == current);
}
