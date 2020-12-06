#include "event.h"

CSLEvent::CSLEvent(long long x, CEventType type, size_t id) : x(x), type(type), id(id) {};

bool event_cmp(const CSLEvent& left, const CSLEvent& right) {
    if (left.x == right.x) {
        return left.type == CEventType::SG_START && right.type == CEventType::SG_END;
    }
    return left.x < right.x;
}
