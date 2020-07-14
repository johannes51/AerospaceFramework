#ifndef TT_H
#define TT_H

#include "calendartime.h"

namespace asf {
namespace time {

class TT : public CalendarTime
{
public:
  TT();

  virtual int year() override;
};

} // namespace time
} // namespace asf

#endif // TT_H
