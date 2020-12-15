#include "point.h"

CPoint::CPoint(long long x, long long y) : x(x), y(y){};

bool projection_intersect(long long start1, long long end1, long long start2,
                          long long end2) {
  if (start1 > end1) {
    std::swap(start1, end1);
  }
  if (start2 > end2) {
    std::swap(start2, end2);
  }
  return std::max(start1, start2) <= std::min(end1, end2);
}

Sign area_sign(CPoint pt1, CPoint pt2, CPoint pt3) {
  long long area =
      (pt2.x - pt1.x) * (pt3.y - pt1.y) - (pt2.y - pt1.y) * (pt3.x - pt1.x);
  if (area == 0) {
    return ZERO;
  }
  return area > 0 ? PLUS : MINUS;
};
