//  Profile.cpp
//  Author: Francis Ricci

#include "Profile.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>
#include <vector>

#define PADDING_SIZE 0.1
#define MATERIAL_COST 0.75
#define MAX_SPEED 0.5
#define TIME_COST 0.07

Profile::Profile(std::vector<std::shared_ptr<Edge>> edges) : _profile(edges) {
  std::sort(_profile.begin(), _profile.end(), Edge::comparePtrs);
  assert(isValid());

  _cost = computeTimeCost() + computeAreaCost();
}

double Profile::computeTimeCost() const {
  double timeCost = 0;

  for (auto edge : _profile) {
    double r = edge->getRadius();
    double len = edge->getLength();

    double modLen = (r == 0) ? len : len * exp(-1 / r);

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

// returns whether point is less than the point at the start of the edge
static bool findPoint(std::shared_ptr<Edge> edge, Point const &point) {
  return edge->getStart() < point;
}

bool Profile::isValid() const {
  std::shared_ptr<Edge> current = _profile[0];
  std::shared_ptr<Edge> next = current;
  size_t numEdges = _profile.size();

  for (size_t i = 0; i < numEdges; ++i) {
    next = *std::lower_bound(_profile.begin(), _profile.end(),
                             current->getEnd(), findPoint);
    if (current->getEnd() != next->getStart()) {
      return false;
    }

    if (*next == *_profile[0]) {
      return (i == numEdges - 1) ? true : false;
    }

    current = next;
  }

  return false;
}
