#ifndef TIMEPOINT_H
#define TIMEPOINT_H

#include <cstdint>

namespace asf {
namespace time {

struct TimePoint {
  int year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  double second;

  TimePoint()
      : TimePoint(0, 0, 0, 0, 0, 0.)
  {
  }
  TimePoint(int _year, uint8_t _month, uint8_t _day, uint8_t _hour, uint8_t _minute, double _second)
      : year(_year)
      , month(_month)
      , day(_day)
      , hour(_hour)
      , minute(_minute)
      , second(_second)
  {
  }
};

} // namespace time
} // namespace asf

#endif // TIMEPOINT_H
