#include <iostream>
#include <vector>

struct CPoint {
    long long x;
    long long y;
};

inline long long oriented_area(CPoint pt1, CPoint pt2, CPoint pt3) {
    return (pt2.x - pt1.x) * (pt3.y - pt1.y) - (pt2.y - pt1.y) * (pt3.x - pt1.x);
}


inline bool projection_intersection(int start1, int end1, int start2, int end2) {
	if (start1 > end1) {
        std::swap(start1, end1);
    }
	if (start2 > end2) {
        std::swap(start2, end2);
    }
	return std::max(start1, start2) <= std::min(end1, end2);
}

bool are_crossed(CPoint pt1, CPoint pt2, CPoint pt3, CPoint pt4) {
	return projection_intersection(pt1.x, pt2.x, pt3.x, pt4.x)
		&& projection_intersection(pt1.y, pt2.y, pt3.y, pt4.y)
		&& oriented_area(pt1, pt2, pt3) * oriented_area(pt1, pt2, pt4) <= 0
		&& oriented_area(pt3, pt4, pt1) * oriented_area(pt3, pt4, pt2) <= 0;
}

size_t build_bridge(CPoint start, CPoint end, const std::vector<std::pair<CPoint, CPoint>>& rivers) {
    size_t res = 0;
    for (std::pair<CPoint, CPoint> river : rivers) {
        if (are_crossed(start, end, river.first, river.second)) {
            ++res;
        }
    }
    return res;
}


int main() {
    CPoint start, end;
    std::cin >> start.x >> start.y >> end.x >> end.y;
    
    size_t n;
    std::cin >> n;
    std::vector<std::pair<CPoint, CPoint>> rivers(n);
    
    for (int i = 0; i < n; ++i) {
        std::cin >> rivers[i].first.x 
                 >> rivers[i].first.y 
                 >> rivers[i].second.x 
                 >> rivers[i].second.y;
    }
    std::cout << build_bridge(start, end, rivers) << std::endl;
    return 0;
}
