#include <iostream>
#include <vector>
#include "point.h"
#include "segment.h"
#include "event.h"
#include "status.h"
#include "scanline.h"

const char SPACE = ' ';
const std::string NO = "NO";
const std::string YES = "YES";

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
  std::pair<long long, long long> inters = CScanLine::find_intersection(segs);
  if (inters == NO_INTERSECTION_PAIR_OBJECT) {
    std::cout << NO << std::endl;
  } else {
    std::cout << YES << std::endl;
    std::cout << inters.first + 1 << SPACE << inters.second + 1 << std::endl;
  }
  return 0;
}
