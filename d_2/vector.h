#pragma once

#include "point.h"

const double EPSILON = 0.000001;

struct CVector : public CPoint {
  CVector() = default;
  CVector(double x, double y);
  CVector(const CPoint &first, const CPoint &second);
  CVector &operator+=(const CVector &other);
};

bool operator<(const CVector &left, const CVector &right);
