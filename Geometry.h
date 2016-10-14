//  Geometry.h
//  Author: Francis Ricci
//
//  Classes which store and compute information about edges

#pragma once

// Represents a single point on a 2D grid
class Point {
public:
  Point(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}

public:
  bool operator==(Point const &other) const {
    return (x == other.x) && (y == other.y);
  }

  bool operator<(Point const &other) const {
    return (x == other.x) ? y < other.y : x < other.x;
  }

public:
  double computeLinearDistance(Point const &other) const;
  double computeArcDistance(Point const &other, Point const &center) const;

public:
  double getX() { return x; }
  double getY() { return y; }

protected:
  double x;
  double y;
};

// Represents an edge on a 2D grid
class Edge {
public:
  Edge(double xStart, double yStart, double xEnd, double yEnd)
      : start(xStart, yStart), end(xEnd, yEnd) {}

public:
  virtual double getRadius() = 0;
  virtual double getLength() = 0;

public:
  bool operator<(Edge const &other) const {
    return (start == other.start) ? (end < other.end) : (start < other.start);
  }

  bool operator==(Edge const &other) const {
    return (start == other.start) && (end == other.end);
  }

public:
  const Point &getStart() const { return start; }
  const Point &getEnd() const { return end; }

protected:
  Point start;
  Point end;
};

class StraightEdge : Edge {
public:
  StraightEdge(double xStart, double yStart, double xEnd, double yEnd)
      : Edge(xStart, yStart, xEnd, yEnd) {
    len = start.computeLinearDistance(end);
  }

public:
  double getRadius() { return 0; }
  double getLength() { return len; }

protected:
  double len;
};

class CurvedEdge : Edge {
public:
  CurvedEdge(double xStart, double yStart, double xEnd, double yEnd,
             double xCenter, double yCenter);

public:
  double getRadius() { return rad; }
  double getLength() { return len; }

protected:
  Point center;
  double len;
  double rad;
};
