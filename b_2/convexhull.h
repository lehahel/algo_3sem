#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

struct CPoint {
    long long x;
    long long y;
    CPoint() = default;
    CPoint(long long x, long long y);
    bool operator==(const CPoint& other) const;
};

class CConvexHull {
public:
    CConvexHull() = default;
    explicit CConvexHull(const std::vector<CPoint>& points);
    double perimeter() const;

private:
    std::vector<CPoint> hull;
    
    CPoint extract_lowest_pt(std::vector<CPoint>& pts) const;
    bool is_left_rotation(const CPoint& pt1, const CPoint& pt2, const CPoint& pt3) const;    
    void rebase(std::vector<CPoint>& pts, const CPoint& base) const;
    double distance_pts(const CPoint& first, const CPoint& second) const;
};
