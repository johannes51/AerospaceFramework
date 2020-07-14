#ifndef TAI_H
#define TAI_H

#include "calendartime.h"

namespace asf {
namespace time {

class TAI : public CalendarTime
{
public:
  TAI();

  virtual int year() override;
};

} // namespace time
} // namespace asf

#endif // TAI_H
