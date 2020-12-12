#pragma once

#define _USE_MATH_DEFINES

#include <cmath>

const double EPSILON = 0.000001;

struct CPoint {
  double x;
  double y;
  CPoint() = default;
  CPoint(double x, double y);
  bool operator==(const CPoint &other) const;
};