#pragma once

#include "const.h"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

struct CPoint {
    CPoint() = default;
    CPoint(long long x, long long y);
    long long x;
    long long y;
};

struct CSegment {
    CSegment() = default;
    CSegment(CPoint start, CPoint end);
    CPoint start;
    CPoint end;
    long long id;
    long double get_y(long long x) const;
};
