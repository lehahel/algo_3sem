#include "point.h"

CPoint::CPoint(double x, double y) : x(x), y(y){};

bool CPoint::operator==(const CPoint &other) const {
  return fabs(x - other.x) < EPSILON && fabs(y - other.y) < EPSILON;
}