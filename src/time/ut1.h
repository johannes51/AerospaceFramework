#ifndef UT1_H
#define UT1_H

#include "calendartime.h"

namespace asf {
namespace time {

class UT1 : public CalendarTime {
public:
  UT1() = default;
  explicit UT1(const TimePoint& timePoint);
};

} // namespace time
} // namespace asf

#endif // UT1_H
