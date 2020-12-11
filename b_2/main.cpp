#include <iomanip>
#include <iostream>
#include "convexhull.h"

const int PRECISION = 15;

int main() {
  size_t n;
  std::cin >> n;

  double x, y;
  std::vector<CPoint> points;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> x >> y;
    points.emplace_back(x, y);
  }

  CConvexHull ch(points);
  std::cout.precision(PRECISION);
  std::cout << std::fixed << ch.perimeter() << std::endl;
  return 0;
}
