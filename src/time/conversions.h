#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include "julianliketime.h"
#include "calendartime.h"
#include "modifiedjuliandate.h"
#include "tai.h"
#include "tt.h"
#include "ut1.h"
#include "utc.h"

namespace asf {
namespace time {

template<typename ToTime, typename FromTime>
ToTime convert(const FromTime& from);

template<typename ToTime>
ToTime convertCal(const CalendarTime& from)
{
  try {
    return convert<ToTime>(dynamic_cast<const TAI&>(from));
  } catch (...) {}
  try {
    return convert<ToTime>(dynamic_cast<const TT&>(from));
  } catch (...) {}
  try {
    return convert<ToTime>(dynamic_cast<const UT1&>(from));
  } catch (...) {}
  try {
    return convert<ToTime>(dynamic_cast<const UTC&>(from));
  } catch (...) {
    throw false;
  }
}

template<typename ToTime, typename FromTime>
ToTime convert(const FromTime& from)
{
  try {
    const auto& fromJulian = dynamic_cast<const JulianLikeTime&>(from);
    return convertCal<ToTime>(*fromJulian.toCal());
  } catch (...) {
  }
  try {
    const auto& fromCal = dynamic_cast<const CalendarTime&>(from);
    return convertCal<ToTime>(fromCal);
  } catch (...) {
    throw false;
  }
}

template<>
TAI convert(const UTC& from);

template<>
TT convert(const UTC& from);

template<>
UT1 convert(const UTC& from);

template<>
ModifiedJulianDate convert(const TAI& from);

template<>
ModifiedJulianDate convert(const TT& from);

template<>
ModifiedJulianDate convert(const UT1& from);

} // namespace time
} // namespace asf

#endif // CONVERSIONS_H
