//  Profile.h
//  Author: Francis Ricci
//
//  Describes a 2D geometric profile

#pragma once

#include "Geometry.h"

#include <vector>

class Profile {
public:
  Profile(std::vector<std::shared_ptr<Edge>> edges);

public:
  double getCost() const { return _cost; }

protected:
  double computeTimeCost() const;
  double computeAreaCost() const;

protected:
  bool isValid() const;

protected:
  double _cost;
  std::vector<std::shared_ptr<Edge>> _profile;
};
