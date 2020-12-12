#pragma once

#include <set>
#include "segment.h"

typedef std::set<CSegment, SegmentCmp> Status;

Status::iterator prev_it(const Status &status, Status::iterator it);
Status::iterator next_it(const Status &status, Status::iterator it);
