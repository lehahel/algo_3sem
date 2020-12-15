#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "hull_lib.h"

const int PRECISION = 8;

int main() {
    size_t n;
    std::cin >> n;
    std::vector<CPoint> points;
    double x, y, z;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> x >> y >> z;
        points.emplace_back(x, y, z, i);
    }
    std::vector<CFacet> hull = build_convex_hull(points);

    size_t m;
    std::cin >> m;
    std::cout.precision(PRECISION);
    for (size_t i = 0; i < m; ++i) {
        std::cin >> x >> y >> z;
        std::cout << std::fixed << find_min_distance(points, hull, CPoint(x, y, z)) << std::endl;
    }
    return 0;
}
