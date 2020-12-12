#include "event.h"

CScanLineEvent::CScanLineEvent(long long x, CScanLineEventType type, size_t id)
    : x(x), type(type), id(id){};

bool event_cmp(const CScanLineEvent &left, const CScanLineEvent &right) {
  if (left.x == right.x) {
    return left.type == CScanLineEventType::SG_START &&
           right.type == CScanLineEventType::SG_END;
  }
  return left.x < right.x;
}
