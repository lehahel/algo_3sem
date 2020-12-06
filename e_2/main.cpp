#include <iostream>
#include <vector>
#include "point.h"
#include "segment.h"
#include "event.h"
#include "status.h"

const char SPACE = ' ';
const std::string NO = "NO";
const std::string YES = "YES";

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
