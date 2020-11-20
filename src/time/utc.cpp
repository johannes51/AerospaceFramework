#include "utc.h"

using namespace asf::time;

UTC::UTC(const std::chrono::system_clock::time_point& utc)
{
}

UTC::UTC(const TimePoint& timePoint)
  : CalendarTime(timePoint)
{
}
