//  Geometry.cpp
//  Author: Francis Ricci

#include "Geometry.h"

#include <cassert>
#include <cmath>

// Point

// sqrt((x1 - x2)^2 + (y1 - y2)^2)
double Point::computeLinearDistance(Point const &other) const {
  double xDiff = x - other.x;
  double yDiff = y - other.y;
  double squareDist = xDiff * xDiff + yDiff * yDiff;

  return sqrt(squareDist);
}

// r * acos((2r^2 - |p1 - p2|^2) / 2r^2)
double Point::computeArcDistance(Point const &other,
                                 Point const &center) const {
  double radius = computeLinearDistance(center);
  double linearDist = computeLinearDistance(other);

  double radiusSq = 2 * radius * radius;
  double distSq = linearDist * linearDist;

  double angle = acos((radiusSq - distSq) / radiusSq);

  return radius * angle;
}

// CurvedEdge

CurvedEdge::CurvedEdge(double xStart, double yStart, double xEnd, double yEnd,
                       double xCenter, double yCenter)
    : Edge(xStart, yStart, xEnd, yEnd), center(xCenter, yCenter) {
  rad = start.computeLinearDistance(center);
  assert(rad == end.computeLinearDistance(center));

  len = start.computeArcDistance(end, center);
}
