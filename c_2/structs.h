#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include "const.h"

struct CPoint {
    double x;
    double y;
    double z;
    int id;
    CPoint *prev;
    CPoint *next;

    CPoint() = default;
    CPoint(double x, double y, double z, int id = -1);
    bool act();
    void rotate(double angle);
};

bool operator<(const CPoint &left, const CPoint &right);

struct CFacet {
    int first;
    int second;
    int third;

    CFacet(int first, int second, int third);
    void normalize();
};

bool operator<(const CFacet& left, const CFacet& right);
