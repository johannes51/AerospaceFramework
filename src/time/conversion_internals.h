#ifndef CONVERSION_INTERNALS_H
#define CONVERSION_INTERNALS_H

#include <type_traits>

#include "calendartime.h"
#include "conversion_helpers.h"
#include "julianliketime.h"
#include "modifiedjuliandate.h"
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

// (0b, unfortunately): Catch cases where both are the same
template <typename ToTime> ToTime convertInternal(const ToTime& from)
{
  return from;
}

// (1, partly): Catch unimplemented Cal->Cal
template <typename ToTime, typename FromTime>
typename std::enable_if_t<std::is_base_of_v<CalendarTime,
                              ToTime> & std::is_base_of_v<CalendarTime, FromTime> & !std::is_same_v<FromTime, ToTime>,
    ToTime>
convertInternal(const FromTime& from)
{
  return ToTime::unimplemented(from);
}

// (1, rest): Direct Cal -> Cal conversions
// TT -> TAI
template <> inline TAI convertInternal<TAI, TT>(const TT& from)
{
  return TAI { conv_helpers::ttToTai(from) };
}
// UT1 -> TAI
template <> inline TAI convertInternal<TAI, UT1>(const UT1& from)
{
  return TAI { conv_helpers::ut1ToTai(from) };
}
// UTC -> TAI
template <> inline TAI convertInternal<TAI, UTC>(const UTC& from)
{
  return TAI { conv_helpers::utcToTai(from) };
}
// TAI -> TT
template <> inline TT convertInternal<TT, TAI>(const TAI& from)
{
  return TT { conv_helpers::taiToTt(from) };
}
// UT1 -> TT
template <> inline TT convertInternal<TT, UT1>(const UT1& from)
{
  return TT { conv_helpers::ut1ToTt(from) };
}
// UTC -> TT
template <> inline TT convertInternal<TT, UTC>(const UTC& from)
{
  return TT { conv_helpers::utcToTt(from) };
}
// TAI -> UT1
template <> inline UT1 convertInternal<UT1, TAI>(const TAI& from)
{
  return UT1 { conv_helpers::taiToUt1(from) };
}
// TT -> UT1
template <> inline UT1 convertInternal<UT1, TT>(const TT& from)
{
  return UT1 { conv_helpers::ttToUt1(from) };
}
// UTC -> UT1
template <> inline UT1 convertInternal<UT1, UTC>(const UTC& from)
{
  return UT1 { conv_helpers::utcToUt1(from) };
}
// UT1 -> UTC
template <> inline UTC convertInternal<UTC, UT1>(const UT1& from)
{
  return UTC { conv_helpers::ut1ToUtc(from) };
}
// TAI -> UTC
template <> inline UTC convertInternal<UTC, TAI>(const TAI& from)
{
  return UTC { conv_helpers::taiToUtc(from) };
}
// TT -> UTC
template <> inline UTC convertInternal<UTC, TT>(const TT& from)
{
  return UTC { conv_helpers::ttToUtc(from) };
}

// (7): Cal -> Modified Julian (same scale)
template <typename ToTime, typename FromTime>
typename std::enable_if_t<
    is_instantiation_of_v<ToTime,
        ModifiedJulianDate> & std::is_base_of_v<CalendarTime, FromTime> & std::is_same_v<typename ToTime::scale_type, FromTime>,
    ToTime>
convertInternal(const FromTime& from)
{
  return ToTime::fromMjdDataYourResponsibility(conv_helpers::timePointToMjdData(from));
}

// (6): Direct Modified Julian -> general Julian Like conversions (same scale)
// Classical JD
template <typename ToTime, typename FromTime>
typename std::enable_if_t<
    is_instantiation_of_v<ToTime,
        ClassicalJulianDate> & is_instantiation_of_v<FromTime, ModifiedJulianDate> & std::is_same_v<typename ToTime::scale_type, typename FromTime::scale_type>,
    ToTime>
convertInternal(const FromTime& from)
{
  return ToTime::fromCjdDataYourResponsibility(conv_helpers::mjdToCjdData({ from.wholeDays(), from.dayFraction() }));
}

// (2): Cal -> Julian Like (different scales or non-MJD)
template <typename ToTime, typename FromTime>
typename std::enable_if_t<
    std::is_base_of_v<JulianLikeTime,
        ToTime> & std::is_base_of_v<CalendarTime, FromTime>&(!std::is_same_v<typename ToTime::scale_type, FromTime> | !is_instantiation_of_v<ToTime, ModifiedJulianDate>),
    ToTime>
convertInternal(const FromTime& from)
{
  typedef typename ToTime::scale_type ToScale;
  return convertInternal<ToTime>(convertInternal<ModifiedJulianDate<ToScale>>(convertInternal<ToScale>(from)));
}

// (5, partly): Catch unimplemented general Julian Like -> Modified Julian (same scale)
template <typename ToTime, typename FromTime>
typename std::enable_if_t<
    is_instantiation_of_v<ToTime,
        ModifiedJulianDate> & !is_instantiation_of_v<FromTime, ModifiedJulianDate> & std::is_base_of_v<JulianLikeTime, FromTime> & std::is_same_v<typename ToTime::scale_type, typename FromTime::scale_type>,
    ToTime>
convertInternal(const FromTime& from)
{
  return ToTime::unimplemented(from);
}

// (5, rest): Direct general Julian Like -> Modified Julian conversions (same scale)
// CJD -> MJD
template <typename ToTime>
typename std::enable_if_t<is_instantiation_of_v<ToTime, ModifiedJulianDate>, ToTime> convertInternal(
    const ClassicalJulianDate<typename ToTime::scale_type>& from)
{
  return ToTime::fromMjdDataYourResponsibility(conv_helpers::cjdToMjdData({ from.wholeDays(), from.dayFraction() }));
}

// (8): Modified Julian -> Cal (same scale)
template <typename ToTime, typename FromTime>
typename std::enable_if_t<
    std::is_base_of_v<CalendarTime,
        ToTime> & is_instantiation_of_v<FromTime, ModifiedJulianDate> & std::is_same_v<ToTime, typename FromTime::scale_type>,
    ToTime>
convertInternal(const FromTime& from)
{
  return ToTime { conv_helpers::mjdDataToTimePoint({ from.wholeDays(), from.dayFraction() }) };
}

// (3): Julian Like -> Cal (different scales or non-MJD)
template <typename ToTime, typename FromTime>
typename std::enable_if_t<
    std::is_base_of_v<CalendarTime,
        ToTime> & std::is_base_of_v<JulianLikeTime, FromTime>&(!std::is_same_v<ToTime, typename FromTime::scale_type> | !is_instantiation_of_v<FromTime, ModifiedJulianDate>),
    ToTime>
convertInternal(const FromTime& from)
{
  return convertInternal<ToTime>(convertInternal<typename FromTime::scale_type>(
      convertInternal<ModifiedJulianDate<typename FromTime::scale_type>>(from)));
}

// (4): Julian Like -> Julian Like (different types or different scales)
template <typename ToTime, typename FromTime>
typename std::enable_if_t<
    std::is_base_of_v<JulianLikeTime,
        ToTime> & std::is_base_of_v<JulianLikeTime, FromTime>&(!std::is_same_v<typename ToTime::scale_type, typename FromTime::scale_type> | !std::is_same_v<typename ToTime::base_type, typename FromTime::base_type>),
    ToTime>
convertInternal(const FromTime& from)
{
  return convertInternal<ToTime>(convertInternal<ModifiedJulianDate<typename ToTime::scale_type>>(
      convertInternal<ModifiedJulianDate<typename FromTime::scale_type>>(from)));
}

// (9): Modified Julian -> Modified Julian (different scales)
template <typename ToTime, typename FromTime>
typename std::enable_if_t<
    is_instantiation_of_v<ToTime,
        ModifiedJulianDate> & is_instantiation_of_v<FromTime, ModifiedJulianDate> & !std::is_same_v<typename ToTime::scale_type, typename FromTime::scale_type>,
    ToTime>
convertInternal(const FromTime& from)
{
  return convertInternal<ToTime>(
      convertInternal<typename ToTime::scale_type>(convertInternal<typename FromTime::scale_type>(from)));
}

} // namespace internal
} // namespace time
} // namespace asf

#endif // CONVERSION_INTERNALS_H
