#include "structures.h"

long double CSegment::get_y(long long x) const {
    if (start.x == end.x) {
        return start.y;
    }
    return static_cast<long double>(start.y) + static_cast<long double>((end.y - start.y) * (x - start.x)) 
         / static_cast<long double>(end.x - start.x);
}

bool proj_intersect(long long start1, long long end1, long long start2, long long end2) {
    if (start1 > end1) {
        std::swap(start1, end1);
    }
    if (start2 > end2) {
        std::swap(start2, end2);
    }
    return std::max(start1, start2) <= std::min(end1, end2);
}

enum Sign {
    SG_MINUS = -1,
    SG_ZERO = 0,
    SG_PLUS = 1
};

Sign area_sign(CPoint pt1, CPoint pt2, CPoint pt3) {
    long long area = (pt2.x - pt1.x) * (pt3.y - pt1.y) - (pt2.y - pt1.y) * (pt3.x - pt1.x);
    if (area == 0) {
        return SG_ZERO;
    }
    return area > 0 ? SG_PLUS : SG_MINUS;
};

bool intersect(const CSegment& first, const CSegment& second) {
    return proj_intersect(first.start.x, first.end.x, second.start.x, second.end.x)
		&& proj_intersect(first.start.y, first.end.y, second.start.y, second.end.y)
		&& area_sign(first.start, first.end, second.start) * area_sign(first.start, first.end, second.end) <= 0
		&& area_sign(second.start, second.end, first.start) * area_sign(second.start, second.end, first.end) <= 0;
}

struct SegmentCmp {
    bool operator()(const CSegment& left, const CSegment& right) {
        long long x = std::max(std::min(left.start.x, left.end.x), std::min(right.start.x, right.end.x));
        return left.get_y(x) < right.get_y(x) - EPSILON;
    }
};

enum class CEventType {
    SG_START,
    SG_END
};

struct CSLEvent {
    CSLEvent() = delete;
    CSLEvent(long long x, CEventType type, size_t id);
    long long x;
    size_t id;
    CEventType type;
};

CSLEvent::CSLEvent(long long x, CEventType type, size_t id) : x(x), type(type), id(id) {};

bool event_cmp(const CSLEvent& left, const CSLEvent& right) {
    if (left.x == right.x) {
        return left.type == CEventType::SG_START && right.type == CEventType::SG_END;
    }
    return left.x < right.x;
}

typedef std::set<CSegment, SegmentCmp> Status;

Status::iterator prev_it(const Status& status, Status::iterator it) {
    return it == status.begin() ? status.end() : --it;
}

Status::iterator next_it(const Status& status, Status::iterator it) {
    return ++it;
}

std::pair<long long, long long> find_intersection(std::vector<CSegment>& segs) {
    Status status;
    std::vector<Status::iterator> seg_pos;
    std::vector<CSLEvent> events;

    for (size_t i = 0; i < segs.size(); ++i) {
        events.emplace_back(std::min(segs[i].start.x, segs[i].end.x), CEventType::SG_START, i);
        events.emplace_back(std::max(segs[i].start.x, segs[i].end.x), CEventType::SG_END, i);
        segs[i].id = i;
    }
    std::sort(events.begin(), events.end(), event_cmp);

    seg_pos.resize(segs.size());
    for (size_t i = 0; i < events.size(); ++i) {
        size_t cur_id = events[i].id;
        if (events[i].type == CEventType::SG_START) {
            
            auto next = status.lower_bound(segs[cur_id]);
            auto prev = prev_it(status, next);

            if (next != status.end() && intersect(*next, segs[cur_id])) {
                return std::make_pair(next->id, cur_id);
            } else if (prev != status.end() && intersect(*prev, segs[cur_id])) {
                return std::make_pair(prev->id, cur_id);
            }
            seg_pos[cur_id] = status.insert(next, segs[cur_id]);

        } else {
            
            auto next = next_it(status, seg_pos[cur_id]);
            auto prev = prev_it(status, seg_pos[cur_id]);
            
            if (next != status.end() && prev != status.end() && intersect(*next, *prev)) {
                return std::make_pair(prev->id, next->id);
            }
            status.erase(seg_pos[cur_id]);
        }
    }
    return std::make_pair(-1, -1);
}

int main() {
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios_base::sync_with_stdio(false);

    size_t n;
    std::cin >> n;
    std::vector<CSegment> segs;
    CPoint start, end;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> start.x >> start.y >> end.x >> end.y;
        segs.emplace_back(start, end);
    }
    std::pair<long long, long long> inters = find_intersection(segs);
    if (inters.first == -1 && inters.second == -1) {
        std::cout << NO << std::endl;
    } else {
        std::cout << YES << std::endl;
        std::cout << inters.first + 1 << SPACE << inters.second + 1 << std::endl;
    }
    return 0;
}
