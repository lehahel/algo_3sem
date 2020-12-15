#include <iostream>
#include "point.h"
#include "shape.h"
#include "interchecker.h"

const std::string YES = "YES";
const std::string NO = "NO";

int main() {
  size_t n;

  std::cin >> n;
  std::vector<CPoint> shape_v(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> shape_v[i].x >> shape_v[i].y;
  }
  CShape shape1(shape_v);

  std::cin >> n;
  shape_v.resize(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> shape_v[i].x >> shape_v[i].y;
  }
  CShape shape2(shape_v);

  std::cout << (CIntersectionChecker().intersect(shape1, shape2) ? YES : NO) << std::endl;

  return 0;
}
