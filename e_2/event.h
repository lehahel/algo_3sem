#pragma once

#include <algorithm>

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

bool event_cmp(const CSLEvent& left, const CSLEvent& right);
