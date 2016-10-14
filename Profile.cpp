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
  std::vector<double> xVals;
  std::vector<double> yVals;
  for (auto edge : _profile) {
    xVals.push_back(edge->getStart().getX());
    xVals.push_back(edge->getEnd().getX());
    yVals.push_back(edge->getStart().getY());
    yVals.push_back(edge->getEnd().getY());
  }

  double xMin = *std::min(xVals.begin(), xVals.end()) + PADDING_SIZE;
  double yMin = *std::min(yVals.begin(), yVals.end()) + PADDING_SIZE;
  double xMax = *std::max(xVals.begin(), xVals.end()) + PADDING_SIZE;
  double yMax = *std::max(yVals.begin(), yVals.end()) + PADDING_SIZE;

  return (xMax - xMin) * (yMax - yMin) * MATERIAL_COST;
}

// returns whether point is less than the point at the start of the edge
static bool findPoint(std::shared_ptr<Edge> edge, Point const &point) {
  return point < edge->getStart();
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
