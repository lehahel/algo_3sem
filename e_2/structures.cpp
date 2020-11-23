#include "structures.h"

CPoint::CPoint(long long x, long long y) : x(x), y(y) {};

CSegment::CSegment(CPoint start, CPoint end) : start(start), end(end) {};
