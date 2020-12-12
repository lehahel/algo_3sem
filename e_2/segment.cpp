#include "segment.h"

CSegment::CSegment(CPoint start, CPoint end) : start(start), end(end){};

long double CSegment::get_y(long long x) const {
  if (start.x == end.x) {
    return start.y;
  }
  return static_cast<long double>(start.y) +
         static_cast<long double>((end.y - start.y) * (x - start.x)) /
             static_cast<long double>(end.x - start.x);
}

bool SegmentCmp::operator()(const CSegment &left, const CSegment &right) {
  long long x = std::max(std::min(left.start.x, left.end.x),
                         std::min(right.start.x, right.end.x));
  return left.get_y(x) < right.get_y(x) - EPSILON;
}

bool intersect(const CSegment &first, const CSegment &second) {
  return projection_intersect(first.start.x, first.end.x, second.start.x,
                              second.end.x) &&
         projection_intersect(first.start.y, first.end.y, second.start.y,
                              second.end.y) &&
         area_sign(first.start, first.end, second.start) *
                 area_sign(first.start, first.end, second.end) <= 0 &&
         area_sign(second.start, second.end, first.start) *
                 area_sign(second.start, second.end, first.end) <= 0;
}
