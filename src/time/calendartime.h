#ifndef CALENDERTIME_H
#define CALENDERTIME_H

#include <cstdint>

#include "time.h"

namespace asf {
namespace time {

struct TimePoint {
  int year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  double second;
};

class CalendarTime : public Time {
public:
  ~CalendarTime() override = 0;

  operator TimePoint() const { return timePoint_; }

protected:
  CalendarTime()
      : timePoint_()
  {
  }
  CalendarTime(const TimePoint& timePoint)
      : timePoint_(timePoint)
  {
  }

  TimePoint timePoint_;
};

inline CalendarTime::~CalendarTime() { }

} // namespace time
} // namespace asf

#endif // CALENDERTIME_H
