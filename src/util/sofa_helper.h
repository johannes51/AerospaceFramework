#ifndef SOFA_HELPER_H
#define SOFA_HELPER_H

#include <utility>

#include "time/calendartime.h"
#include "time/conversions.h"
#include "time/modifiedjuliandate.h"

namespace asf {
namespace util {

template <typename FromTime>
std::enable_if_t<std::is_base_of_v<time::CalendarTime, FromTime>, std::pair<double, double>> toSofaJd(
    const FromTime& from)
{
  auto mjd = time::convert<time::ModifiedJulianDate<FromTime>>(from);
  return std::pair<double, double>(time::ModifiedJulianDate<FromTime>::DayOffset,
      mjd.dayNumber() + mjd.dayFraction() + time::ModifiedJulianDate<FromTime>::DayOffset);
}

template <template <typename> typename FromTime, typename Scale>
std::pair<double, double> toSofaJd(const FromTime<Scale>& from)
{
  auto mjd = time::convert<time::ModifiedJulianDate<Scale>>(from);
  return std::pair<double, double>(time::ModifiedJulianDate<Scale>::DayOffset,
      mjd.dayNumber() + mjd.dayFraction() + time::ModifiedJulianDate<Scale>::DayOffset);
}

template <template <typename> typename ToTime, typename Scale>
ToTime<Scale> fromSofaJd(const double& from1, const double& from2)
{
  return {}; // TODO: implement
}

template <typename ToTime>
std::enable_if_t<std::is_base_of_v<time::CalendarTime, ToTime>, ToTime> fromSofaJd(
    const double& from1, const double& from2)
{
  (void)from1;
  (void)from2;
  return {}; // TODO: implementb
}

} // namespace util
} // namespace asf

#endif // SOFA_HELPER_H
