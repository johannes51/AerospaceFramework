#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include <stdexcept>
#include <type_traits>

#include "calendartime.h"
#include "classicaljuliandate.h"
#include "conversion_internals.h"
#include "julianliketime.h"
#include "tai.h"
#include "tt.h"
#include "ut1.h"
#include "utc.h"

namespace asf {
namespace time {

// (0): Catch cases where both are the same
template <typename ToTime> const ToTime& convert(const ToTime& from)
{
  return from;
}

// Switches on Time abstract type
template <typename ToTime, typename FromTime>
typename std::enable_if_t<std::is_same_v<FromTime, Time>, ToTime> convert(const FromTime& from)
{
  try {
    return convert<ToTime>(dynamic_cast<const CalendarTime&>(from));
  } catch (...) {
  }
  try {
    return convert<ToTime>(dynamic_cast<const JulianLikeTime&>(from));
  } catch (...) {
    throw std::invalid_argument("Should never reach");
  }
}

// Switches on CalendarTime abstract type
template <typename ToTime, typename FromTime>
typename std::enable_if_t<std::is_same_v<FromTime, CalendarTime>, ToTime> convert(const FromTime& from)
{
  try {
    return convert<ToTime>(dynamic_cast<const TAI&>(from));
  } catch (...) {
  }
  try {
    return convert<ToTime>(dynamic_cast<const TT&>(from));
  } catch (...) {
  }
  try {
    return convert<ToTime>(dynamic_cast<const UTC&>(from));
  } catch (...) {
  }
  try {
    return convert<ToTime>(dynamic_cast<const UT1&>(from));
  } catch (...) {
    throw std::invalid_argument("Should never reach");
  }
}

// Switches on JulianLikeTime abstract type
template <typename ToTime> ToTime convert(const JulianLikeTime& from)
{
  try {
    return convert<ToTime>(dynamic_cast<const JulianLikeTimeImp<TAI>&>(from));
  } catch (...) {
  }
  try {
    return convert<ToTime>(dynamic_cast<const JulianLikeTimeImp<TT>&>(from));
  } catch (...) {
  }
  try {
    return convert<ToTime>(dynamic_cast<const JulianLikeTimeImp<UTC>&>(from));
  } catch (...) {
  }
  try {
    return convert<ToTime>(dynamic_cast<const JulianLikeTimeImp<UT1>&>(from));
  } catch (...) {
    throw std::invalid_argument("Should never reach");
  }
}

// Switches on JulianLikeTimeImp abstract type
template <typename ToTime, typename Scale> ToTime convert(const JulianLikeTimeImp<Scale>& from)
{
  try {
    return convert<ToTime>(dynamic_cast<const ModifiedJulianDate<Scale>&>(from));
  } catch (...) {
  }
  try {
    return convert<ToTime>(dynamic_cast<const ClassicalJulianDate<Scale>&>(from));
  } catch (...) {
    throw std::invalid_argument("Should never reach");
  }
}

// Defers to internal function (templates)
template <typename ToTime, typename FromTime>
typename std::enable_if_t<
    !std::is_abstract_v<ToTime> & !std::is_abstract_v<FromTime> & !std::is_same_v<ToTime, FromTime>, ToTime>
convert(const FromTime& from)
{
  return internal::convertInternal<ToTime>(from);
}

} // namespace time
} // namespace asf

#endif // CONVERSIONS_H
