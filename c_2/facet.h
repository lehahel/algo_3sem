#pragma once
#include <algorithm>
#include <vector>
#include "point.h"

struct CFacet {
    int first;
    int second;
    int third;

    CFacet(int first, int second, int third);
    void normalize();
};

bool operator<(const CFacet& left, const CFacet& right);

double point_to_facet_distance(const CPoint &pt, const CPoint &first, const CPoint &second, const CPoint &third);
double find_min_distance(const std::vector<CPoint> &points, const std::vector<CFacet> &facets, const CPoint &pt);
