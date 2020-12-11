#pragma once
#include <cmath>

const double DOUBLE_EPS = 1e-6;
const double DOUBLE_INF = 1e9;

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

double turn(const CPoint *point1, const CPoint *point2, const CPoint *pt3);
double time(const CPoint *point1, const CPoint *point2, const CPoint *pt3);
