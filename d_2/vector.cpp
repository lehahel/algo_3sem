#include "vector.h"

CVector::CVector(double x, double y) : CPoint(x, y){};

CVector::CVector(const CPoint &first, const CPoint &second)
    : CPoint(second.x - first.x, second.y - first.y){};

CVector &CVector::operator+=(const CVector &other) {
  x += other.x;
  y += other.y;
  return *this;
}

bool operator<(const CVector &left, const CVector &right) {
  double tg1 = atan2(left.y, left.x);
  if (tg1 > M_PI / 2 + EPSILON) {
    tg1 -= 2 * M_PI;
  }
  double tg2 = atan2(right.y, right.x);
  if (tg2 > M_PI / 2 + EPSILON) {
    tg2 -= 2 * M_PI;
  }
  return tg1 < tg2;
}