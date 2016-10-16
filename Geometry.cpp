//  Geometry.cpp
//  Author: Francis Ricci

#include "Geometry.h"

#include <cassert>
#include <cmath>

// Point

// sqrt((x1 - x2)^2 + (y1 - y2)^2)
double Point::computeLinearDistance(Point const &other) const {
  double xDiff = _x - other._x;
  double yDiff = _y - other._y;
  double squareDist = xDiff * xDiff + yDiff * yDiff;

  return sqrt(squareDist);
}

double Point::computeArcAngle(Point const &other,
                              Point const &center) const {
  double radius = computeLinearDistance(center);
  double startAngle = atan2(_y - center._y, _x - center._x);
  double endAngle = atan2(other._y - center._y, other._x - center._x);

  return startAngle - endAngle;
}

// r * acos((2r^2 - |p1 - p2|^2) / 2r^2)
double Point::computeArcDistance(Point const &other,
                                 Point const &center) const {
  double radius = computeLinearDistance(center);

  return std::abs(radius * computeArcAngle(other, center));
}

Point Point::computeArcPoint(Point const &other,
                             Point const &center) const {
  double radius = computeLinearDistance(center);
  double angle = computeArcAngle(other, center) / 2;

  double x = center._x + radius * sin(angle);
  double y = center._y - radius * (1 - cos(angle));

  return Point(x, y);
}

// CurvedEdge

CurvedEdge::CurvedEdge(Point start, Point end, Point center)
    : Edge(start, end), _center(center), _arcPoint(start.computeArcPoint(end, center)){
  _radius = start.computeLinearDistance(center);
  assert(_radius == end.computeLinearDistance(center));

  _len = start.computeArcDistance(end, center);
}
