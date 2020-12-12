#pragma once

#include <algorithm>

enum class CScanLineEventType {
    SG_START,
    SG_END
};

struct CScanLineEvent {
    CScanLineEvent() = delete;
    CScanLineEvent(long long x, CScanLineEventType type, size_t id);
    long long x;
    size_t id;
    CScanLineEventType type;
};

bool event_cmp(const CScanLineEvent& left, const CScanLineEvent& right);
