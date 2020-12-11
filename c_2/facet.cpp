#include "facet.h"

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

double point_to_facet_distance(const CPoint &pt, const CPoint &first, const CPoint &second, const CPoint &third) {
    double k1 = first.y * second.z - first.y * third.z - second.y * first.z + second.y * third.z + third.y * first.z - third.y * second.z;
    double k2 = -first.x * second.z + first.x * third.z + second.x * first.z - second.x * third.z - third.x * first.z + third.x * second.z;
    double k3 = first.x * second.y - first.x * third.y - second.x * first.y + second.x * third.y + third.x * first.y - third.x * second.y;
    double k4 = -first.x * second.y * third.z + first.x * third.y  * second.z + second.x * first.y * third.z - second.x * third.y * first.z - third.x * first.y * second.z + third.x * second.y * first.z;

    return fabs((pt.x * k1 + pt.y * k2 + pt.z * k3 + k4)) / (std::sqrt(k1 * k1 + k2 * k2 + k3 * k3));
}

double find_min_distance(const std::vector<CPoint> &points, const std::vector<CFacet> &facets, const CPoint &pt) {
    double min_dist = DOUBLE_INF;
    double cur_dist;
    for (CFacet facet : facets) {
        cur_dist = point_to_facet_distance(pt, points[facet.first], points[facet.second], points[facet.third]);
        min_dist = std::min(cur_dist, min_dist);
    }
    return min_dist;
}
