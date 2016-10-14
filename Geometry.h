//  Geometry.h
//  Author: Francis Ricci
//
//  Classes which store and compute information about edges

#pragma once

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
  static bool comparePtrs(std::shared_ptr<Edge> a, std::shared_ptr<Edge> b) {
    return (a->_start == b->_start) ? (a->_end < b->_end)
                                    : (a->_start < b->_start);
  }

  bool operator==(Edge const &other) const {
    return (_start == other._start) && (_end == other._end);
  }

public:
  const Point &getStart() const { return _start; }
  const Point &getEnd() const { return _end; }

protected:
  const Point _start;
  const Point _end;
};

class StraightEdge : public Edge {
public:
  StraightEdge(Point start, Point end) : Edge(start, end) {
    _len = start.computeLinearDistance(end);
  }

public:
  double getRadius() const { return 0; }
  double getLength() const { return _len; }

protected:
  double _len;
};

class CurvedEdge : public Edge {
public:
  CurvedEdge(Point start, Point end, Point center);

public:
  double getRadius() const { return _radius; }
  double getLength() const { return _len; }

protected:
  Point _center;
  double _len;
  double _radius;
};
