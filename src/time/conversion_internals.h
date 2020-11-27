#ifndef CONVERSION_INTERNALS_H
#define CONVERSION_INTERNALS_H

#include <type_traits>

#include "calendartime.h"
#include "classicaljuliandate.h"
#include "julianliketime.h"
#include "modifiedjuliandate.h"
#include "scaledjulianlike.h"
#include "tai.h"
#include "tt.h"
#include "ut1.h"
#include "utc.h"

template <typename T, template <typename> class TT> struct is_instantiation_of : std::false_type {
};

template <typename T, template <typename> class TT> struct is_instantiation_of<TT<T>, TT> : std::true_type {
};

template <typename T, template <typename> class TT>
constexpr bool is_instantiation_of_v = is_instantiation_of<T, TT>::value;

namespace asf {
namespace time {
namespace internal {

// Catch cases where both are the same
template <typename ToTime, typename FromTime>
typename std::enable_if_t<std::is_same_v<FromTime, ToTime>, ToTime> convertInternal(const FromTime& from)
{
  return from;
}

// Catch unimplemented Cal->Cal
template <typename ToTime, typename FromTime>
typename std::enable_if_t<std::is_base_of_v<CalendarTime,
                              ToTime> & std::is_base_of_v<CalendarTime, FromTime> & !std::is_same_v<FromTime, ToTime>,
    ToTime>
convertInternal(const FromTime& from)
{
  return ToTime::unimplemented(from);
}

// General Julian to general Julian (same scale) -> ClassicalJulian to general
// Julian (same scale)
template <typename ToTime>
typename std::enable_if_t<std::is_base_of_v<JulianLikeTime, ToTime>, ToTime> convertInternal(
    const ScaledJulianLike<typename ToTime::scale_type>& from)
{
  return convertInternal<ToTime>(from.toClassical());
}

// General Julian to general Julian (different scales) -> ClassicalJulian to
// general Julian (different scales)
template <typename ToTime, typename FromScale>
typename std::enable_if_t<std::is_base_of_v<JulianLikeTime, ToTime>, ToTime> convertInternal(
    const ScaledJulianLike<FromScale>& from)
{
  auto a = from.toCalendar();
  auto b = convertInternal<typename ToTime::scale_type>(a);
  auto c = convertInternal<ClassicalJulianDate<typename ToTime::scale_type>>(b);
  return convertInternal<ToTime>(c);
}

// General Julian to Calendar -> Calendar to Calendar
template <typename ToTime, typename FromScale>
typename std::enable_if_t<std::is_base_of_v<CalendarTime, ToTime>, ToTime> convertInternal(
    const ScaledJulianLike<FromScale>& from)
{
  return convertInternal<ToTime>(from.toCalendar());
}

// Cal -> Julian
template <typename ToTime, typename FromTime>
typename std::enable_if_t<std::is_base_of_v<JulianLikeTime, ToTime> & std::is_base_of_v<CalendarTime, FromTime>, ToTime>
convertInternal(const FromTime& from)
{
  auto a = convertInternal<typename ToTime::scale_type>(from);
  auto b = convertInternal<ClassicalJulianDate<typename ToTime::scale_type>>(a);
  return convertInternal<ToTime>(b);
}

// Calender to ClassicalJulian (same scale)
template <typename ToTime>
typename std::enable_if_t<std::is_base_of_v<JulianLikeTime, ToTime>, ToTime> convertInternal(
    const typename ToTime::scale_type& from)
{
  (void)from;
  return ToTime(); // TODO: implement
}

// Classical to Modified Julian (same scale)
template <typename ToTime>
typename std::enable_if_t<is_instantiation_of_v<ToTime, ModifiedJulianDate>, ToTime> convertInternal(
    const ClassicalJulianDate<typename ToTime::scale_type>& from)
{
  return ToTime(); // TODO: implement
}

// Direct Cal -> Cal conversions

template <> TAI convertInternal<TAI, TT>(const TT& from);

template <> TAI convertInternal<TAI, UT1>(const UT1& from);

template <> TAI convertInternal<TAI, UTC>(const UTC& from);

template <> TT convertInternal<TT, TAI>(const TAI& from);

template <> TT convertInternal<TT, UT1>(const UT1& from);

template <> TT convertInternal<TT, UTC>(const UTC& from);

template <> UT1 convertInternal<UT1, TAI>(const TAI& from);

template <> UT1 convertInternal<UT1, TT>(const TT& from);

template <> UT1 convertInternal<UT1, UTC>(const UTC& from);

template <> UTC convertInternal<UTC, UT1>(const UT1& from);

template <> UTC convertInternal<UTC, TAI>(const TAI& from);

template <> UTC convertInternal<UTC, TT>(const TT& from);

} // namespace internal
} // namespace time
} // namespace asf

#endif // CONVERSION_INTERNALS_H
