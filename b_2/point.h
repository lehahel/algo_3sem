#pragma once

struct CPoint {
  long long x;
  long long y;
  CPoint() = default;
  CPoint(long long x, long long y);
  bool operator==(const CPoint &other) const;
};

bool polar_cmp(const CPoint &left, const CPoint &right);
