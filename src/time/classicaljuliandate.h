#ifndef CLASSICALJULIANDATE_H
#define CLASSICALJULIANDATE_H

#include "scaledjulianlike.h"

namespace asf {
namespace time {

template <typename Scale> class ClassicalJulianDate : public ScaledJulianLike<Scale> {
public:
  ClassicalJulianDate() = default;
  ClassicalJulianDate(const ClassicalJulianDate& other);

  virtual double dayFraction() const override;
  virtual int dayNumber() const override;

  virtual ClassicalJulianDate<Scale> toClassical() const override;
  virtual Scale toCalendar() const override;
};

template <typename Scale> ClassicalJulianDate<Scale>::ClassicalJulianDate(const ClassicalJulianDate& other)
{
  (void)other; // TODO: implement
}

template <typename Scale> double ClassicalJulianDate<Scale>::dayFraction() const
{
  return 0;
}

template <typename Scale> int ClassicalJulianDate<Scale>::dayNumber() const
{
  return 0;
}

template <typename Scale> ClassicalJulianDate<Scale> ClassicalJulianDate<Scale>::toClassical() const
{
  return *this;
}

template <typename Scale> Scale ClassicalJulianDate<Scale>::toCalendar() const
{
  return Scale(); // TODO: implement
}

} // namespace time
} // namespace asf

#endif // CLASSICALJULIANDATE_H
