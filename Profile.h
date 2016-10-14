//  Profile.h
//  Author: Francis Ricci
//
//  Describes a 2D geometric profile

#pragma once

#include "Geometry.h"

class Profile {
public:
  Profile(std::vector<Edge> edges);

public:
  double getCost() const { return cost; }

protected:
  double computeTimeCost() const;
  double computeAreaCost() const;

protected:
  bool isValid() const;

protected:
  double cost;
  std::vector<Edge> profile;
};
