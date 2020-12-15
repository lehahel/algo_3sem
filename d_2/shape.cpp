#include "shape.h"

CShape::CShape(const std::vector<CPoint> &vertices) : vertices(vertices) {
  reorder();
}

std::vector<CPoint> CShape::get_vertices() const { return vertices; }

CShape CShape::operator-() const {
  CShape res;
  for (size_t i = 0; i < vertices.size(); ++i) {
    res.vertices.emplace_back(-vertices[i].x, -vertices[i].y);
  }
  return res;
}

void CShape::reorder() {
  size_t min_pt = 0;
  for (size_t i = 0; i < vertices.size(); ++i) {
    if (vertices[i].x < vertices[min_pt].x ||
        fabs(vertices[i].x - vertices[min_pt].x) < EPSILON &&
            vertices[i].y < vertices[min_pt].y) {
      min_pt = i;
    }
  }

  std::vector<CPoint> new_order;
  for (size_t i = 0; i < vertices.size(); ++i) {
    new_order.emplace_back(vertices[(i + min_pt) % vertices.size()]);
  }
  vertices = new_order;
}

CShape &CShape::operator+=(const CShape &other) {
  CShape res;
  size_t i = 0, j = 0;
  size_t n = vertices.size();
  size_t m = other.vertices.size();
  while (i < n || j < m) {

    res.vertices.emplace_back(vertices[i % n].x + other.vertices[j % m].x,
                              vertices[i % n].y + other.vertices[j % m].y);

    if (i >= n) {
      ++j;
      continue;
    }
    if (j >= m) {
      ++i;
      continue;
    }

    CVector v1(vertices[(i + 1) % n].x - vertices[i % n].x,
               vertices[(i + 1) % n].y - vertices[i % n].y);
    CVector v2(other.vertices[(j + 1) % m].x - other.vertices[j % m].x,
               other.vertices[(j + 1) % m].y - other.vertices[j % m].y);

    if (v1 < v2) {
      ++j;
    } else if (v2 < v1) {
      ++i;
    } else {
      ++i;
      ++j;
    }
  }
  *this = res;
  return *this;
}
