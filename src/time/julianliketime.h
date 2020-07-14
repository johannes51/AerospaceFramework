#ifndef JULIANLIKETIME_H
#define JULIANLIKETIME_H

#include <type_traits>
#include <utility>
#include <memory>

#include "time.h"
#include "calendartime.h"

namespace asf {
namespace time {

class ClassicalJulianDate;

class JulianLikeTime : public Time {
public:
  virtual ~JulianLikeTime() = default;

  virtual double dayFraction() const = 0;

  virtual ClassicalJulianDate toClassical() const = 0;
  virtual std::unique_ptr<CalendarTime> toCal() const = 0;
protected:
  explicit JulianLikeTime(std::unique_ptr<CalendarTime> scale) : scale_(std::move(scale)) {}
  std::unique_ptr<CalendarTime> scale_;
};

} // namespace time
} // namespace asf

#endif // JULIANLIKETIME_H
