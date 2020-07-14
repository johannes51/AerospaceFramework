#ifndef MODIFIEDJULIANDATE_H
#define MODIFIEDJULIANDATE_H

#include "julianliketime.h"
#include "classicaljuliandate.h"

namespace asf {
namespace time {

class ModifiedJulianDate : public JulianLikeTime
{
public:
  ModifiedJulianDate() = delete;
  ModifiedJulianDate(std::unique_ptr<CalendarTime> scale);
  virtual ~ModifiedJulianDate() = default;

  virtual double dayFraction() const override;

  static constexpr long DayOffset = 2400000;
  static constexpr double FractionOffset = 0.5;

  virtual std::unique_ptr<CalendarTime> toCal() const override;
  virtual ClassicalJulianDate toClassical() const override;
};

} // namespace time
} // namespace asf

#endif // MODIFIEDJULIANDATE_H
