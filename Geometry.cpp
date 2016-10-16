//  Geometry.cpp
//  Author: Francis Ricci

#include "Geometry.h"

#include <cmath>
#include <stdexcept>

// Point

// sqrt((x1 - x2)^2 + (y1 - y2)^2)
double Point::computeLinearDistance(Point const &other) const {
  double xDiff = _x - other._x;
  double yDiff = _y - other._y;
  double squareDist = xDiff * xDiff + yDiff * yDiff;

  return sqrt(squareDist);
}

// The angle between this point and other, as described by a circled with an
// origin at center
double Point::computeArcAngle(Point const &other, Point const &center) const {
  double startAngle = atan2(_y - center._y, _x - center._x);
  double endAngle = atan2(other._y - center._y, other._x - center._x);

  return startAngle - endAngle;
}

double Point::computeArcDistance(Point const &other,
                                 Point const &center) const {
  double radius = computeLinearDistance(center);

  return std::abs(radius * computeArcAngle(other, center));
}

// The point in the center of the arc described by this point, and other,
// with its origin at center
Point Point::computeArcPoint(Point const &other, Point const &center) const {
  double radius = computeLinearDistance(center);
  double angle = computeArcAngle(other, center) / 2;

  double x = center._x + radius * sin(angle);
  double y = center._y - radius * (1 - cos(angle));

  return Point(x, y);
}

// CurvedEdge

CurvedEdge::CurvedEdge(Point start, Point end, Point center)
    : Edge(start, end), _center(center),
      _arcPoint(start.computeArcPoint(end, center)) {
  _radius = start.computeLinearDistance(center);
  if (_radius != end.computeLinearDistance(center)) {
    throw std::invalid_argument("Circular coordinates are invalid");
  }

  _len = start.computeArcDistance(end, center);
}
