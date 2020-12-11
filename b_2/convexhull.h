#pragma once

#include <vector>
#include <cmath>
#include <algorithm>
#include "point.h"

class CConvexHull {
public:
  CConvexHull() = default;
  explicit CConvexHull(const std::vector<CPoint> &points);
  double perimeter() const;

private:
  std::vector<CPoint> hull;

  CPoint extract_lowest_point(std::vector<CPoint> &points) const;
  bool is_left_rotation(const CPoint &point1, const CPoint &point2,
                        const CPoint &point3) const;
  void rebase(std::vector<CPoint> &pts, const CPoint &base) const;
  double points_distance(const CPoint &first, const CPoint &second) const;
};
