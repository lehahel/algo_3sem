#include "convexhull.h"

CPoint::CPoint(long long x, long long y) : x(x), y(y) {};

bool CPoint::operator==(const CPoint& other) const {
    return x == other.x && y == other.y;
}

CPoint CConvexHull::extract_lowest_pt(std::vector<CPoint>& pts) const {
    CPoint lowest = pts[0];
    for (CPoint pt : pts) {
        if (lowest.y == pt.y) {
            lowest = lowest.x > pt.x ? lowest : pt;
        } else {
            lowest = lowest.y < pt.y ? lowest : pt;
        }
    }
    long long cur_lowest = pts.size();

    for (long long i = pts.size() - 1; i >= 0; --i) {
        if (pts[i] == lowest) {
            std::swap(pts[i], pts[--cur_lowest]);
        }
    }
    pts.resize(cur_lowest);
    return lowest;
}

bool polar_cmp(const CPoint& left, const CPoint& right) {
    long long area = left.x * right.y - right.x * left.y;
    if (area == 0) {
        return (left.x * left.x) + (left.y * left.y) < (right.x * right.x) + (right.y * right.y);
    }
    return area > 0;
}

bool CConvexHull::is_left_rotation(const CPoint& pt1, const CPoint& pt2, const CPoint& pt3) const {
    long long dif_x1 = pt2.x - pt1.x;
    long long dif_x2 = pt3.x - pt1.y;
    long long dif_y1 = pt2.y - pt1.y;
    long long dif_y2 = pt3.y - pt1.y;

    long long area = dif_x1 * dif_y2 - dif_y1 * dif_x2;
    if (area == 0) {    
        return (dif_x1 * dif_x1) + (dif_y1 + dif_y1) >= (dif_x2 * dif_x2) + (dif_y2 + dif_y2); 
    }
    return area > 0;
}

void CConvexHull::rebase(std::vector<CPoint>& pts, const CPoint& base) const {
    for (size_t i = 0; i < pts.size(); ++i) {
        pts[i].x -= base.x;
        pts[i].y -= base.y;
    }
}

double CConvexHull::distance_pts(const CPoint& first, const CPoint& second) const {
    long long dif_x = first.x - second.x;
    long long dif_y = first.y - second.y;
    long long res_sqr = static_cast<unsigned long long>(dif_x * dif_x) + static_cast<unsigned long long>(dif_y * dif_y);
    return sqrt(res_sqr);
}

double CConvexHull::perimeter() const {
    double res = distance_pts(hull[0], hull[hull.size() - 1]);
    for (size_t i = 1; i < hull.size(); ++i) {
        res += distance_pts(hull[i], hull[i - 1]);
    }
    return res;
}


CConvexHull::CConvexHull(const std::vector<CPoint>& points) {
    std::vector<CPoint> pts = points;
    CPoint lowest = extract_lowest_pt(pts);
    rebase(pts, lowest);

    std::sort(pts.begin(), pts.end(), polar_cmp);
    hull.emplace_back(0, 0);

    for (size_t i = 0; i < pts.size(); ++i) {
        if (hull.size() < 2) {
            hull.push_back(pts[i]);
            continue;
        }
        if (pts[i] == pts[i - 1]) {
            continue;
        }
        while (!is_left_rotation(hull[hull.size() - 2], hull[hull.size() - 1], pts[i])) {
            hull.pop_back();
            if (hull.size() == 1) {
                break;
            }
        }
        hull.push_back(pts[i]);
    }
}