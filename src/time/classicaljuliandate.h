#ifndef CLASSICALJULIANDATE_H
#define CLASSICALJULIANDATE_H

#include "julianliketime.h"

namespace asf {
namespace time {

class ClassicalJulianDate : public JulianLikeTime
{
public:
  ClassicalJulianDate() = default;
  ClassicalJulianDate(const ClassicalJulianDate& other);

  virtual double dayFraction() const override;

  virtual ClassicalJulianDate toClassical() const override;
  virtual std::unique_ptr<CalendarTime> toCal() const override;
};

} // namespace time
} // namespace asf

#endif // CLASSICALJULIANDATE_H
