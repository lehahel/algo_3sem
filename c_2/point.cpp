#include "point.h"

CPoint::CPoint(double x, double y, double z, int id = -1) : x(x), y(y), z(z), id(id), prev(nullptr), next(nullptr) {
    rotate(DOUBLE_EPS);
};

bool CPoint::act() {
    if (prev->next != this) {
        prev->next = this;
        next->prev = this;
        return true;
    } else {
        prev->next = next;
        next->prev = prev;
        return false;
    }
}

bool operator<(const CPoint &left, const CPoint &right) {
    return left.x < right.x;
}

void CPoint::rotate(double angle) {
    double tmp_x, tmp_y, tmp_z;

    tmp_x = x * cos(angle) - y * sin(angle);
    tmp_y = y * sin(angle) + y * cos(angle);
    x = tmp_x, y = tmp_y;

    tmp_x = x * cos(angle) - z * sin(angle);
    tmp_z = x * sin(angle) + z * cos(angle);
    x = tmp_x, z = tmp_z;

    tmp_y = y * cos(angle) - z * sin(angle);
    tmp_z = y * sin(angle) + z * cos(angle);
    y = tmp_y, z = tmp_z;
}

double turn(const CPoint *point1, const CPoint *point2, const CPoint *pt3) {
    if (point1 == nullptr || point2 == nullptr || pt3 == nullptr) {
        return DOUBLE_INF;
    }
    return (point2->x - point1->x) * (pt3->y - point2->y) - (point2->y - point1->y) * (pt3->x - point2->x);
}

double time(const CPoint *point1, const CPoint *point2, const CPoint *pt3) {
    if (point1 == nullptr || point2 == nullptr || pt3 == nullptr) {
        return DOUBLE_INF;
    }
    return ((point2->x - point1->x) * (pt3->z - point2->z) - (point2->z - point1->z) * (pt3->x - point2->x)) / turn(point1, point2, pt3);
}
