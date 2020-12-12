#pragma once

#include <algorithm>

struct CPoint {
  CPoint() = default;
  CPoint(long long x, long long y);
  long long x;
  long long y;
};

enum Sign { MINUS = -1, ZERO = 0, PLUS = 1 };

bool projection_intersect(long long start1, long long end1, long long start2,
                          long long end2);
Sign area_sign(CPoint pt1, CPoint pt2, CPoint pt3);
