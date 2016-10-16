//  Geometry.h
//  Author: Francis Ricci
//
//  Classes which store and compute information about edges

#pragma once

#include <algorithm>
#include <memory>

// Represents a single point on a 2D grid
class Point {
public:
  Point(double x, double y) : _x(x), _y(y) {}

public:
  bool operator==(Point const &other) const {
    return (_x == other._x) && (_y == other._y);
  }

  bool operator!=(Point const &other) const {
    return (_x != other._x) || (_y != other._y);
  }

  bool operator<(Point const &other) const {
    return (_x == other._x) ? _y < other._y : _x < other._x;
  }

public:
  double computeLinearDistance(Point const &other) const;
  double computeArcDistance(Point const &other, Point const &center) const;
  Point computeArcPoint(Point const &other, Point const &center) const;

protected:
  double computeArcAngle(Point const &other, Point const &center) const;

public:
  double getX() const { return _x; }
  double getY() const { return _y; }

protected:
  double _x;
  double _y;
};

// Represents an edge on a 2D grid
class Edge {
public:
  Edge(Point start, Point end) : _start(start), _end(end) {}

public:
  virtual double getRadius() const = 0;
  virtual double getLength() const = 0;

public:
  bool operator==(Edge const &other) const {
    return (_start == other._start) && (_end == other._end);
  }

public:
  const Point &getStart() const { return _start; }
  const Point &getEnd() const { return _end; }

public:
  virtual double getMinX() const {
    return std::min(_start.getX(), _end.getX());
  }
  virtual double getMaxX() const {
    return std::max(_start.getX(), _end.getX());
  }
  virtual double getMinY() const {
    return std::min(_start.getY(), _end.getY());
  }
  virtual double getMaxY() const {
    return std::max(_start.getY(), _end.getY());
  }

protected:
  const Point _start;
  const Point _end;
};

// Represents a straight line
class StraightEdge : public Edge {
public:
  StraightEdge(Point start, Point end) : Edge(start, end) {
    _len = start.computeLinearDistance(end);
  }

public:
  double getRadius() const override { return 0; }
  double getLength() const override { return _len; }

protected:
  double _len;
};

// Represents an arc
class CurvedEdge : public Edge {
public:
  CurvedEdge(Point start, Point end, Point center);

public:
  double getRadius() const override { return _radius; }
  double getLength() const override { return _len; }

public:
  double getMinX() const override {
    return std::min(Edge::getMinX(), _arcPoint.getX());
  }
  double getMaxX() const override {
    return std::max(Edge::getMaxX(), _arcPoint.getX());
  }
  double getMinY() const override {
    return std::min(Edge::getMinY(), _arcPoint.getY());
  }
  double getMaxY() const override {
    return std::max(Edge::getMaxY(), _arcPoint.getY());
  }

protected:
  Point _center;   // the origin of the circle described by the arc
  Point _arcPoint; // the center point along the arc's circumference
  double _len;
  double _radius;
};
