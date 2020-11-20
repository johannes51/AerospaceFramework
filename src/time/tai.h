#ifndef TAI_H
#define TAI_H

#include "calendartime.h"

namespace asf {
namespace time {

class TAI : public CalendarTime
{
public:
  TAI();
  explicit TAI(const TimePoint& timePoint);
};

} // namespace time
} // namespace asf

#endif // TAI_H
