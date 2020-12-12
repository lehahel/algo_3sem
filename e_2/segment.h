#pragma once

#include "point.h"

const long double EPSILON = 1e-9;

struct CSegment {
  CSegment() = default;
  CSegment(CPoint start, CPoint end);
  CPoint start;
  CPoint end;
  long long id;
  long double get_y(long long x) const;
};

class SegmentCmp {
public:
  bool operator()(const CSegment &left, const CSegment &right);
};

bool intersect(const CSegment &first, const CSegment &second);
