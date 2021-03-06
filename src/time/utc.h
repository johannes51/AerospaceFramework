#ifndef UTC_H
#define UTC_H

#include <chrono>

#include "calendartime.h"

namespace asf {
namespace time {

class UTC : public CalendarTime {
public:
  UTC() = default;
  explicit UTC(const std::chrono::system_clock::time_point& utc);
  explicit UTC(const TimePoint& timePoint);
};

} // namespace time
} // namespace asf

#endif // UTC_H
