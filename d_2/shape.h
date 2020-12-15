#pragma once

#include <vector>
#include <cmath>
#include <algorithm>
#include "point.h"
#include "vector.h"

const double EPSILON = 0.000001;

class CShape {
public:
  CShape() = default;
  CShape(const std::vector<CPoint> &vertices);
  CShape &operator+=(const CShape &other);
  CShape operator-() const;
  std::vector<CPoint> get_vertices() const;

private:
  std::vector<CPoint> vertices;
  void reorder();
};
