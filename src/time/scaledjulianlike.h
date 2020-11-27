#ifndef SCALEDJULIANLIKE_H
#define SCALEDJULIANLIKE_H

#include <type_traits>

#include "calendartime.h"
#include "julianliketime.h"

namespace asf {
namespace time {

template <typename Scale> class ClassicalJulianDate;

template <typename Scale> class ScaledJulianLike : public JulianLikeTime {
public:
  typedef std::enable_if_t<std::is_base_of_v<CalendarTime, Scale>, Scale> scale_type;
  virtual ~ScaledJulianLike() = default;

  virtual ClassicalJulianDate<Scale> toClassical() const = 0;
  virtual Scale toCalendar() const = 0;
};

} // namespace time
} // namespace asf

#endif // SCALEDJULIANLIKE_H
