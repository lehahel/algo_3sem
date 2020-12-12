#include "status.h"

Status::iterator prev_it(const Status &status, Status::iterator it) {
  return it == status.begin() ? status.end() : --it;
}

Status::iterator next_it(const Status &status, Status::iterator it) {
  return ++it;
}
