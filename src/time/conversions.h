#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include <type_traits>

#include "julianliketime.h"
#include "calendartime.h"
#include "classicaljuliandate.h"
#include "modifiedjuliandate.h"
#include "tai.h"
#include "tt.h"
#include "ut1.h"
#include "utc.h"
#include "conversion_internals.h"

namespace asf {
namespace time {

// Switches on Time abstract type
template<typename ToTime>
ToTime convert(const Time& from)
{
  try {
    return convert<ToTime>(dynamic_cast<const CalendarTime&>(from));
  } catch (...) {
  }
  try {
    return convert<ToTime>(dynamic_cast<const JulianLikeTime&>(from));
  } catch (...) {
    throw false;
  }
}

// Switches on CalendarTime abstract type
template<typename ToTime>
ToTime convert(const CalendarTime& from)
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
    throw false;
  }
}

// Switches on JulianLikeTime abstract type
template<typename ToTime>
ToTime convert(const JulianLikeTime& from)
{
  try {
    return convert<ToTime>(dynamic_cast<const ScaledJulianLike<TAI>&>(from));
  } catch (...) {
  }
  try {
    return convert<ToTime>(dynamic_cast<const ScaledJulianLike<TT>&>(from));
  } catch (...) {
  }
  try {
    return convert<ToTime>(dynamic_cast<const ScaledJulianLike<UTC>&>(from));
  } catch (...) {
  }
  try {
    return convert<ToTime>(dynamic_cast<const ScaledJulianLike<UT1>&>(from));
  } catch (...) {
    throw false;
  }
}

// Defers to internal function (templates)
template<typename ToTime, typename FromTime>
ToTime convert(const FromTime& from)
{
  return internal::convertInternal<ToTime>(from);
}

} // namespace time
} // namespace asf

#endif // CONVERSIONS_H
