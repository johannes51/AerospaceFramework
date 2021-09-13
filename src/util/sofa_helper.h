#ifndef SOFA_HELPER_H
#define SOFA_HELPER_H

#include "time/calendartime.h"
#include "time/conversions.h"
#include "time/modifiedjuliandate.h"

namespace asf {
namespace util {

// given MJD, actually solve it
template <typename Scale> std::pair<double, double> toSofaJd(const time::ModifiedJulianDate<Scale>& from)
{
  return { time::ModifiedJulianDate<Scale>::DayOffset + time::ModifiedJulianDate<Scale>::FractionOffset,
    from.wholeDays() + from.dayFraction() };
}

// given general JD, convert to MJD
template <typename FromTime>
std::enable_if_t<!std::is_base_of_v<time::CalendarTime, FromTime>, std::pair<double, double>> toSofaJd(
    const FromTime& from)
{
  typedef typename FromTime::scale_type Scale;
  return toSofaJd(time::convert<time::ModifiedJulianDate<Scale>>(from));
}

// given Calendar time, convert to MJD
template <typename FromTime>
std::enable_if_t<std::is_base_of_v<time::CalendarTime, FromTime>, std::pair<double, double>> toSofaJd(
    const FromTime& from)
{
  return toSofaJd(time::convert<time::ModifiedJulianDate<FromTime>>(from));
}

template <typename ToTime>
std::enable_if_t<std::is_same_v<time::ModifiedJulianDate<typename ToTime::scale_type>, ToTime>, ToTime> fromSofaJd(
    const double& from1, const double& from2)
{
  return ToTime::fromSofaJd(from1, from2);
}

template <typename ToTime>
std::enable_if_t<!std::is_same_v<time::ModifiedJulianDate<typename ToTime::scale_type>, ToTime>, ToTime> fromSofaJd(
    const double& from1, const double& from2)
{
  return time::convert<ToTime>(fromSofaJd<time::ModifiedJulianDate<typename ToTime::scale_type>>(from1, from2));
}

template <typename ToTime>
std::enable_if_t<std::is_base_of_v<time::CalendarTime, ToTime>, ToTime> fromSofaJd(
    const double& from1, const double& from2)
{
  return time::convert<ToTime>(fromSofaJd<time::ModifiedJulianDate<ToTime>>(from1, from2));
}

} // namespace util
} // namespace asf

#endif // SOFA_HELPER_H
