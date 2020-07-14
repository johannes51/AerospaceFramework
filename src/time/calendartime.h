#ifndef CALENDERTIME_H
#define CALENDERTIME_H

#include "time.h"

namespace asf {
namespace time {

class CalendarTime : public Time {
public:
  virtual ~CalendarTime() = default;

  virtual int year() = 0;
protected:
  CalendarTime() = default;
};

} // namespace time
} // namespace asf

#endif // CALENDERTIME_H
