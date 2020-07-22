#ifndef MODIFIEDJULIANDATE_H
#define MODIFIEDJULIANDATE_H

#include "scaledjulianlike.h"
#include "classicaljuliandate.h"

namespace asf {
namespace time {

template<typename Scale>
class ModifiedJulianDate : public ScaledJulianLike<Scale>
{
public:
  virtual ~ModifiedJulianDate() = default;

  virtual double dayFraction() const override;
  virtual int dayNumber() const override;

  static constexpr long DayOffset = 2400000;
  static constexpr double FractionOffset = 0.5;

  virtual ClassicalJulianDate<Scale> toClassical() const override;
  virtual Scale toCalendar() const override;
};

template<typename Scale>
int ModifiedJulianDate<Scale>::dayNumber() const
{
  return 0;
}

template<typename Scale>
double ModifiedJulianDate<Scale>::dayFraction() const
{
  return 0;
}

template<typename Scale>
ClassicalJulianDate<Scale> ModifiedJulianDate<Scale>::toClassical() const
{
  return ClassicalJulianDate<Scale>();
}

template<typename Scale>
Scale ModifiedJulianDate<Scale>::toCalendar() const
{
  return toClassical().toCalendar();
}

} // namespace time
} // namespace asf

#endif // MODIFIEDJULIANDATE_H
