#include "point.h"

CPoint::CPoint(long long x, long long y) : x(x), y(y){};

bool CPoint::operator==(const CPoint &other) const {
  return x == other.x && y == other.y;
}

bool polar_cmp(const CPoint &left, const CPoint &right) {
  long long area = left.x * right.y - right.x * left.y;
  if (area == 0) {
    return (left.x * left.x) + (left.y * left.y) <
           (right.x * right.x) + (right.y * right.y);
  }
  return area > 0;
}
