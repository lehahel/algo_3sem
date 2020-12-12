#include "interchecker.h"

bool CIntersectionChecker::contains_zero(const CShape &shape) {
  std::vector<CPoint> vert = shape.get_vertices();

  bool result = false;
  int j = vert.size() - 1;

  for (size_t i = 0; i < vert.size(); ++i) {
    if ((vert[i].y < -EPSILON && vert[j].y >= -EPSILON ||
         vert[j].y < -EPSILON && vert[i].y >= -EPSILON) &&
        (vert[i].x -
             vert[i].y / (vert[j].y - vert[i].y) * (vert[j].x - vert[i].x) <
         -EPSILON)) {
      result = !result;
    }
    j = i;
  }
  return result;
}

bool CIntersectionChecker::intersect(const CShape &left, const CShape &right) {
  CShape shape = left;
  shape += (-right);
  return contains_zero(shape);
}
