#include "hull_lib.h"

void set_next_times(std::vector<double> next_time, const CPoint *point1, const CPoint *point2) {
    next_time[2] = time(point1, point2, point2->next);
    next_time[3] = time(point1, point2->prev, point2);
    next_time[4] = time(point1->prev, point1, point2);
    next_time[5] = time(point1, point1->next, point2);
}

void find_points(CPoint *point1, CPoint *point2) {
    while (true) {
        if (turn(point1, point2, point2->next) < 0) {
            point2 = point2->next;
        } else if (turn(point1->prev, point1, point2) < 0) {
            point1 = point1->prev;
        } else {
            break;
        }
    }
}

void result_emplace(int idx, std::vector<CPoint *> &res, CPoint *point1, CPoint *point2, CPoint *l, CPoint *r, size_t &pos1, size_t &pos2) {
        if (idx == 0) {
            if (l->x < point1->x) {
                res.emplace_back(l);
            }
            l->act();
            ++pos1;
        } else if (idx == 1) {
            if (r->x > point2->x) {
                res.emplace_back(r);
            }
            r->act();
            ++pos2;
        } else if (idx == 2) {
            res.emplace_back(point2);
            point2 = point2->next;
        } else if (idx == 3) {
            point2 = point2->prev;
            res.emplace_back(point2);
        } else if (idx == 4) {
            res.emplace_back(point1);
            point1 = point1->prev;
        } else if (idx == 5) {
            point1 = point1->prev;
            res.emplace_back(point1);
        }
}

std::vector<CPoint *> find_hull(std::vector<CPoint> &points, size_t left, size_t right) {
    if (right - left == 1) {
        return std::vector<CPoint *>();
    }
    size_t mid = left + (right - left) / 2;
    
    std::vector<CPoint *> event1 = find_hull(points, left, mid);
    std::vector<CPoint *> event2 = find_hull(points, mid, right);
    std::vector<CPoint *> res;

    CPoint *point1 = &points[mid - 1];
    CPoint *point2 = &points[mid];

    find_points(point1, point2);

    size_t pos1 = 0;
    size_t pos2 = 0;
    double cur_time = -DOUBLE_INF;

    while (true) {
        CPoint *l = nullptr;
        CPoint *r = nullptr;
        std::vector<double> next_time(TIMES_SIZE, DOUBLE_INF);

        if (pos1 < event1.size()) {
            l = event1[pos1];
            next_time[0] = time(l->prev, l, l->next);
        }
        if (pos2 < event2.size()) {
            r = event2[pos2];
            next_time[1] = time(r->prev, r, r->next);
        }

        set_next_times(next_time, point1, point2);

        int min_idx = -1;
        double min_time = DOUBLE_INF;
        for (int i = 0; i < TIMES_SIZE; ++i) {
            if (next_time[i] > cur_time && next_time[i] < min_time) {
                min_time = next_time[i];
                min_idx = i;
            }
        }
        if (min_idx == -1 || min_time >= DOUBLE_INF) {
            break;
        }
        result_emplace(min_idx, res, point1, point2, l, r, pos1, pos2);
        cur_time = min_time;
    }

    point1->next = point2;
    point2->prev = point1;
    
    for (int i = res.size() - 1; i >= 0; --i) {
        CPoint *cur = res[i];
        if (cur->x > point1->x && cur->x < point2->x) {
            point1->next = point2->prev = cur;
            cur->prev = point1;
            cur->next = point2;
            if (cur->x <= points[mid - 1].x) {
                point1 = cur;
            } else {
                point2 = cur;
            }
        } else {
            cur->act();
            if (cur == point1) {
                point1 = point1->prev;
            } else if (cur == point2) {
                point2 = point2->next;
            }
        }
    }
    return res;
}

std::vector<CFacet> build_convex_hull(std::vector<CPoint> points) {
    size_t n = points.size();
    std::vector<CFacet> res;
    std::sort(points.begin(), points.end());
    
    for (CPoint &pt : points) {
        pt.next = nullptr;
        pt.prev = nullptr;
        pt.z = -pt.z;
    }
    std::vector<CPoint *> events = find_hull(points, 0, n);

    for (CPoint *ev : events) {
        CFacet cur(ev->prev->id, ev->id, ev->next->id);
        if (!ev->act()) {
            std::swap(cur.first, cur.second);
        }
        cur.normalize();
        res.emplace_back(cur);
    }

    for (CPoint &pt : points) {
        pt.next = nullptr;
        pt.prev = nullptr;
        pt.z = -pt.z;
    }

    events = find_hull(points, 0, n);
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
