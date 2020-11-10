#include "convexhull.h"

int main() {
    size_t n;
    std::cin >> n;
    
    double x, y;
    std::vector<CPoint> pts;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> x >> y;
        pts.emplace_back(x, y);
    }

    CConvexHull ch(pts);
    std::cout.precision(15);
    std::cout << std::fixed << ch.perimeter() << std::endl;
    return 0;
}