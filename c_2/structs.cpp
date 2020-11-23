#include "structs.h"

CPoint::CPoint(double x, double y, double z, int id = -1) : x(x), y(y), z(z), id(id), prev(nullptr), next(nullptr) {
    rotate(DBLEPS);
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
    double _x, _y, _z;

    _x = x * cos(angle) - y * sin(angle);
    _y = y * sin(angle) + y * cos(angle);
    x = _x, y = _y;

    _x = x * cos(angle) - z * sin(angle);
    _z = x * sin(angle) + z * cos(angle);
    x = _x, z = _z;

    _y = y * cos(angle) - z * sin(angle);
    _z = y * sin(angle) + z * cos(angle);
    y = _y, z = _z;
}

CFacet::CFacet(int first, int second, int third) : first(first), second(second), third(third) {};

void CFacet::normalize() {
    if (second < third && second < first) {
        std::swap(first, second);
        std::swap(second, third);
    } else if (third < first && third < second) {
        std::swap(first, third);
        std::swap(second, third);
    }
}

bool operator<(const CFacet& left, const CFacet& right) {
    if (left.first == right.first) {
        if (left.second == right.second) {
            return left.third < right.third;
        }
        return left.second < right.second;
    }
}
