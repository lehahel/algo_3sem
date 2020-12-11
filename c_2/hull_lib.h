#pragma once
#include <vector>
#include "point.h"
#include "facet.h"

const int TIMES_SIZE = 6;

void set_next_times(std::vector<double> next_time, const CPoint *point1, const CPoint *point2);
void find_points(CPoint *point1, CPoint *point2);
void result_emplace(int idx, std::vector<CPoint *> &res,
                    CPoint *point1, CPoint *point2, CPoint *l, CPoint *r,
                    size_t &pos1, size_t &pos2);

std::vector<CPoint *> find_hull(std::vector<CPoint> &points, size_t left, size_t right);
std::vector<CFacet> build_convex_hull(std::vector<CPoint> points);
