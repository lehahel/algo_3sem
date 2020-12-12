#include <vector>
#include "point.h"
#include "segment.h"
#include "event.h"
#include "status.h"

const std::pair<long long, long long> NO_INTERSECTION_PAIR_OBJECT = {-1, -1};

class CScanLine {
public:
  static std::pair<long long, long long>
  find_intersection(std::vector<CSegment> &segs);
};
