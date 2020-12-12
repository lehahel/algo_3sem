#pragma once

#include "shape.h"

class CIntersectionChecker {
public:
  bool intersect(const CShape &left, const CShape &right);

private:
  bool contains_zero(const CShape &shape);
};
