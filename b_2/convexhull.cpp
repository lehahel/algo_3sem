#include "convexhull.h"

CPoint CConvexHull::extract_lowest_point(std::vector<CPoint> &points) const {
  CPoint lowest = points[0];
  for (CPoint point : points) {
    if (lowest.y == point.y) {
      lowest = lowest.x > point.x ? lowest : point;
    } else {
      lowest = lowest.y < point.y ? lowest : point;
    }
  }
  long long cur_lowest = points.size();

  for (long long i = points.size() - 1; i >= 0; --i) {
    if (points[i] == lowest) {
      std::swap(points[i], points[--cur_lowest]);
    }
  }
  points.resize(cur_lowest);
  return lowest;
}

bool CConvexHull::is_left_rotation(const CPoint &point1, const CPoint &point2,
                                   const CPoint &point3) const {
  long long x_difference_1 = point2.x - point1.x;
  long long x_difference_2 = point3.x - point1.y;
  long long y_difference_1 = point2.y - point1.y;
  long long y_difference_2 = point3.y - point1.y;

  long long area =
      x_difference_1 * y_difference_2 - y_difference_1 * x_difference_2;

  if (area == 0) {
    return (x_difference_1 * x_difference_1) +
               (y_difference_1 * y_difference_1) >=
           (x_difference_2 * x_difference_2) +
               (y_difference_2 * y_difference_2);
  }
  return area > 0;
}

void CConvexHull::rebase(std::vector<CPoint> &points, const CPoint &base) const {
  for (size_t i = 0; i < points.size(); ++i) {
    points[i].x -= base.x;
    points[i].y -= base.y;
  }
}

double CConvexHull::points_distance(const CPoint &first,
                                    const CPoint &second) const {
  long long dif_x = first.x - second.x;
  long long dif_y = first.y - second.y;
  long long res_sqr = static_cast<unsigned long long>(dif_x * dif_x) +
                      static_cast<unsigned long long>(dif_y * dif_y);
  return sqrt(res_sqr);
}

double CConvexHull::perimeter() const {
  double res = points_distance(hull[0], hull[hull.size() - 1]);
  for (size_t i = 1; i < hull.size(); ++i) {
    res += points_distance(hull[i], hull[i - 1]);
  }
  return res;
}

CConvexHull::CConvexHull(const std::vector<CPoint> &points) {
  std::vector<CPoint> points_copy = points;
  CPoint lowest = extract_lowest_point(points_copy);
  rebase(points_copy, lowest);

  std::sort(points_copy.begin(), points_copy.end(), polar_cmp);
  hull.emplace_back(0, 0);

  for (size_t i = 0; i < points_copy.size(); ++i) {
    if (hull.size() < 2) {
      hull.push_back(points_copy[i]);
      continue;
    }
    if (points_copy[i] == points_copy[i - 1]) {
      continue;
    }
    while (!is_left_rotation(hull[hull.size() - 2], hull[hull.size() - 1],
                             points_copy[i])) {
      hull.pop_back();
      if (hull.size() == 1) {
        break;
      }
    }
    hull.push_back(points_copy[i]);
  }
}
