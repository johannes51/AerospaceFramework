#ifndef CALENDERTIME_H
#define CALENDERTIME_H

#include "time.h"
#include "timepoint.h"

namespace asf {
namespace time {

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
