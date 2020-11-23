#include "structs.h"

double turn(const CPoint *pt1, const CPoint *pt2, const CPoint *pt3) {
    if (pt1 == nullptr || pt2 == nullptr || pt3 == nullptr) {
        return DBLINF;
    }
    return (pt2->x - pt1->x) * (pt3->y - pt2->y) - (pt2->y - pt1->y) * (pt3->x - pt2->x);
}

double time(const CPoint *pt1, const CPoint *pt2, const CPoint *pt3) {
    if (pt1 == nullptr || pt2 == nullptr || pt3 == nullptr) {
        return DBLINF;
    }
    return ((pt2->x - pt1->x) * (pt3->z - pt2->z) - (pt2->z - pt1->z) * (pt3->x - pt2->x)) / turn(pt1, pt2, pt3);
}

std::vector<CPoint *> find_hull(std::vector<CPoint> &pts, size_t left, size_t right) {
    if (right - left == 1) {
        return std::vector<CPoint *>();
    }
    size_t mid = left + (right - left) / 2;
    
    std::vector<CPoint *> event1 = find_hull(pts, left, mid);
    std::vector<CPoint *> event2 = find_hull(pts, mid, right);
    std::vector<CPoint *> res;

    CPoint *pt1 = &pts[mid - 1];
    CPoint *pt2 = &pts[mid];

    while (true) {
        if (turn(pt1, pt2, pt2->next) < 0) {
            pt2 = pt2->next;
        } else if (turn(pt1->prev, pt1, pt2) < 0) {
            pt1 = pt1->prev;
        } else {
            break;
        }
    }

    size_t pos1 = 0;
    size_t pos2 = 0;
    double cur_time = -DBLINF;

    while (true) {
        CPoint *l = nullptr;
        CPoint *r = nullptr;
        std::vector<double> next_time(6, DBLINF);

        if (pos1 < event1.size()) {
            l = event1[pos1];
            next_time[0] = time(l->prev, l, l->next);
        }
        if (pos2 < event2.size()) {
            r = event2[pos2];
            next_time[1] = time(r->prev, r, r->next);
        }
        next_time[2] = time(pt1, pt2, pt2->next);
        next_time[3] = time(pt1, pt2->prev, pt2);
        next_time[4] = time(pt1->prev, pt1, pt2);
        next_time[5] = time(pt1, pt1->next, pt2);

        int min_idx = -1;
        double min_time = DBLINF;
        for (int i = 0; i < 6; ++i) {
            if (next_time[i] > cur_time && next_time[i] < min_time) {
                min_time = next_time[i];
                min_idx = i;
            }
        }
        if (min_idx == -1 || min_time >= DBLINF) {
            break;
        }

        switch (min_idx) {
            case 0:
                if (l->x < pt1->x) {
                    res.emplace_back(l);
                }
                l->act();
                ++pos1;
                break;

            case 1:
                if (r->x > pt2->x) {
                    res.emplace_back(r);
                }
                r->act();
                ++pos2;
                break;

            case 2:
                res.emplace_back(pt2);
                pt2 = pt2->next;
                break;

            case 3:
                pt2 = pt2->prev;
                res.emplace_back(pt2);
                break;

            case 4:
                res.emplace_back(pt1);
                pt1 = pt1->prev;
                break;
            
            case 5:
                pt1 = pt1->next;
                res.emplace_back(pt1);
                break;
            
            default:
                break;
            
        }
        cur_time = min_time;
    }

    pt1->next = pt2;
    pt2->prev = pt1;
    
    for (int i = res.size() - 1; i >= 0; --i) {
        CPoint *cur = res[i];
        if (cur->x > pt1->x && cur->x < pt2->x) {
            pt1->next = pt2->prev = cur;
            cur->prev = pt1;
            cur->next = pt2;
            if (cur->x <= pts[mid - 1].x) {
                pt1 = cur;
            } else {
                pt2 = cur;
            }
        } else {
            cur->act();
            if (cur == pt1) {
                pt1 = pt1->prev;
            } else if (cur == pt2) {
                pt2 = pt2->next;
            }
        }
    }
    return res;
}

std::vector<CFacet> build_convex_hull(std::vector<CPoint> pts) {
    size_t n = pts.size();
    std::vector<CFacet> res;
    std::sort(pts.begin(), pts.end());
    
    for (CPoint &pt : pts) {
        pt.next = nullptr;
        pt.prev = nullptr;
        pt.z = -pt.z;
    }
    std::vector<CPoint *> events = find_hull(pts, 0, n);

    for (CPoint *ev : events) {
        CFacet cur(ev->prev->id, ev->id, ev->next->id);
        if (!ev->act()) {
            std::swap(cur.first, cur.second);
        }
        cur.normalize();
        res.emplace_back(cur);
    }

    for (CPoint &pt : pts) {
        pt.next = nullptr;
        pt.prev = nullptr;
        pt.z = -pt.z;
    }

    events = find_hull(pts, 0, n);
    for (CPoint *ev : events) {
        CFacet cur(ev->prev->id, ev->id, ev->next->id);
        if (ev->act()) {
            std::swap(cur.first, cur.second);
        }
        cur.normalize();
        res.emplace_back(cur);
    }
    return res;
}

double point_to_facet_distance(const CPoint &pt, const CPoint &first, const CPoint &second, const CPoint &third) {
    double k1 = first.y * second.z - first.y * third.z - second.y * first.z + second.y * third.z + third.y * first.z - third.y * second.z;
    double k2 = -first.x * second.z + first.x * third.z + second.x * first.z - second.x * third.z - third.x * first.z + third.x * second.z;
    double k3 = first.x * second.y - first.x * third.y - second.x * first.y + second.x * third.y + third.x * first.y - third.x * second.y;
    double k4 = -first.x * second.y * third.z + first.x * third.y  * second.z + second.x * first.y * third.z - second.x * third.y * first.z - third.x * first.y * second.z + third.x * second.y * first.z;

    return fabs((pt.x * k1 + pt.y * k2 + pt.z * k3 + k4)) / (std::sqrt(k1 * k1 + k2 * k2 + k3 * k3));
}

double find_min_distance(const std::vector<CPoint> &pts, const std::vector<CFacet> &fcs, const CPoint &pt) {
    double min_dist = DBLINF;
    double cur_dist;
    for (CFacet facet : fcs) {
        cur_dist = point_to_facet_distance(pt, pts[facet.first], pts[facet.second], pts[facet.third]);
        min_dist = std::min(cur_dist, min_dist);
    }
    return min_dist;
}

int main() {
    size_t n;
    std::cin >> n;
    std::vector<CPoint> pts;
    double x, y, z;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> x >> y >> z;
        pts.emplace_back(x, y, z, i);
    }
    std::vector<CFacet> hull = build_convex_hull(pts);

    size_t m;
    std::cin >> m;
    std::cout.precision(8);
    for (size_t i = 0; i < m; ++i) {
        std::cin >> x >> y >> z;
        std::cout << std::fixed << find_min_distance(pts, hull, CPoint(x, y, z)) << std::endl;
    }
    return 0;
}
