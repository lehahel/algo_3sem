#include "scanline.h"

static std::pair<long long, long long>
find_intersection(std::vector<CSegment> &segs) {
  Status status;
  std::vector<Status::iterator> seg_pos;
  std::vector<CScanLineEvent> events;

  for (size_t i = 0; i < segs.size(); ++i) {
    events.emplace_back(std::min(segs[i].start.x, segs[i].end.x),
                        CScanLineEventType::SG_START, i);
    events.emplace_back(std::max(segs[i].start.x, segs[i].end.x),
                        CScanLineEventType::SG_END, i);
    segs[i].id = i;
  }
  std::sort(events.begin(), events.end(), event_cmp);

  seg_pos.resize(segs.size());
  for (size_t i = 0; i < events.size(); ++i) {
    size_t cur_id = events[i].id;
    if (events[i].type == CScanLineEventType::SG_START) {

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

      if (next != status.end() && prev != status.end() &&
          intersect(*next, *prev)) {
        return std::make_pair(prev->id, next->id);
      }
      status.erase(seg_pos[cur_id]);
    }
  }
  return NO_INTERSECTION_PAIR_OBJECT;
}
