#include "utc.h"

namespace a_t = asf::time;

a_t::UTC::UTC(const std::chrono::system_clock::time_point& utc)
{
  auto tt = std::chrono::system_clock::to_time_t(utc);
  auto* tm = gmtime(&tt);
  timePoint_ = { tm->tm_year, static_cast<uint8_t>(tm->tm_mon), static_cast<uint8_t>(tm->tm_mday),
    static_cast<uint8_t>(tm->tm_hour + 1), static_cast<uint8_t>(tm->tm_min), static_cast<double>(tm->tm_sec) };
}

a_t::UTC::UTC(const TimePoint& timePoint)
    : CalendarTime(timePoint)
{
}
