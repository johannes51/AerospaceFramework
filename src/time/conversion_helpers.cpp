#include "conversion_helpers.h"

#include "sofa.h"

#include "util/sofa_helper.h"

namespace a_t = asf::time;
namespace a_t_ch = a_t::conv_helpers;

static constexpr auto HoursPerDay = 24.L;
static constexpr auto MinutesPerHour = 60.L;
static constexpr auto SecondsPerMinute = 60.L;

static constexpr auto OneAsFloatingPoint = 1.L;

a_t::JulianLikeTimeData a_t_ch::cjdToMjdData(JulianLikeTimeData cjd)
{
  return { cjd.wholeDays - ModifiedJulianDate<TT>::DayOffset,
    cjd.dayFraction - ModifiedJulianDate<TT>::FractionOffset };
}

a_t::JulianLikeTimeData a_t_ch::mjdToCjdData(JulianLikeTimeData mjd)
{
  return { mjd.wholeDays + ModifiedJulianDate<TT>::DayOffset,
    mjd.dayFraction + ModifiedJulianDate<TT>::FractionOffset };
}

a_t::TimePoint a_t_ch::mjdDataToTimePoint(JulianLikeTimeData mjd)
{
  return sofaJdToTimePoint(mjdDataToSofaJd(mjd));
}

a_t::JulianLikeTimeData a_t_ch::timePointToMjdData(TimePoint cal)
{
  return sofaToMjdData(timePointToSofaJd(cal));
}

std::pair<double, double> a_t_ch::mjdDataToSofaJd(const JulianLikeTimeData& mjd)
{
  return { ModifiedJulianDate<TT>::DayOffset + ModifiedJulianDate<TT>::FractionOffset,
    mjd.wholeDays + mjd.dayFraction };
}

a_t::JulianLikeTimeData a_t_ch::sofaToMjdData(const std::pair<double, double>& mjd)
{
  auto first = JulianLikeTimeData { static_cast<int>(mjd.first), mjd.first - static_cast<int>(mjd.first) };
  auto second = JulianLikeTimeData { static_cast<int>(mjd.second), mjd.second - static_cast<int>(mjd.second) };
  return { first.wholeDays + second.wholeDays - ModifiedJulianDate<TT>::DayOffset,
    first.dayFraction + second.dayFraction - ModifiedJulianDate<TT>::FractionOffset };
}

double a_t_ch::decomposeDayFraction(const TimePoint& timePoint)
{
  return static_cast<double>(
      (timePoint.hour + (timePoint.minute + timePoint.second / SecondsPerMinute) / MinutesPerHour) / HoursPerDay);
}

void a_t_ch::reconstituteDayFraction(TimePoint& timePoint, double dayFraction)
{
  const auto hourFraction = static_cast<long double>(dayFraction) * HoursPerDay;
  timePoint.hour = static_cast<uint8_t>(hourFraction);
  auto minuteFraction = fmodl(hourFraction, OneAsFloatingPoint) * MinutesPerHour;
  timePoint.minute = static_cast<uint8_t>(minuteFraction);
  timePoint.second = static_cast<double>(fmodl(minuteFraction, OneAsFloatingPoint) * SecondsPerMinute);
}

std::pair<double, double> a_t_ch::timePointToSofaJd(const TimePoint& timePoint)
{
  auto result = std::pair<double, double> { 0., 0. };
  iauCal2jd(timePoint.year, timePoint.month, timePoint.day, &result.first, &result.second);
  result.second += decomposeDayFraction(timePoint);
  return result;
}

a_t::TimePoint a_t_ch::sofaJdToTimePoint(const std::pair<double, double>& sofaJd)
{
  auto result = TimePoint {};
  int month = 0;
  int day = 0;
  double dayFraction = 0.;
  iauJd2cal(sofaJd.first, sofaJd.second, &result.year, &month, &day, &dayFraction);
  result.month = static_cast<uint8_t>(month);
  result.day = static_cast<uint8_t>(day);
  reconstituteDayFraction(result, dayFraction);
  return result;
}

a_t::TimePoint a_t_ch::utcToTai(const TimePoint& utc)
{
  auto jdUtc = timePointToSofaJd(utc);
  double jdTai1 = 0.;
  double jdTai2 = 0.;
  iauUtctai(jdUtc.first, jdUtc.second, &jdTai1, &jdTai2);

  return util::fromSofaJd<TAI>(jdTai1, jdTai2);
}

a_t::TimePoint a_t_ch::ttToTai(const TimePoint& tt)
{
  auto jdTt = timePointToSofaJd(tt);
  double jdTai1 = 0.;
  double jdTai2 = 0.;
  iauUtctai(jdTt.first, jdTt.second, &jdTai1, &jdTai2);

  return util::fromSofaJd<TAI>(jdTai1, jdTai2);
}

a_t::TimePoint a_t_ch::ut1ToTai(const TimePoint& ut1)
{
  const auto jdUt1 = timePointToSofaJd(ut1);
  double jdTai1 = 0.;
  double jdTai2 = 0.;
  iauUt1tai(jdUt1.first, jdUt1.second, 0, &jdTai1, &jdTai2); // TODO: fix dt (IERS table)

  return util::fromSofaJd<TAI>(jdTai1, jdTai2);
}

a_t::TimePoint a_t_ch::taiToTt(const TimePoint& tai)
{
  const auto jdTai = timePointToSofaJd(tai);
  double jdTt1 = 0.;
  double jdTt2 = 0.;
  iauTaitt(jdTai.first, jdTai.second, &jdTt1, &jdTt2);

  return util::fromSofaJd<TT>(jdTt1, jdTt2);
}

a_t::TimePoint a_t_ch::ut1ToTt(const TimePoint& ut1)
{
  const auto jdUt1 = timePointToSofaJd(ut1);
  double jdTt1 = 0.;
  double jdTt2 = 0.;
  iauUt1tt(jdUt1.first, jdUt1.second, 0, &jdTt1, &jdTt2); // TODO: fix dt (IERS table)

  return util::fromSofaJd<TT>(jdTt1, jdTt2);
}

a_t::TimePoint a_t_ch::utcToTt(const TimePoint& utc)
{
  const auto jdUtc = timePointToSofaJd(utc);
  double jdTai1 = 0.;
  double jdTai2 = 0.;
  double jdTt1 = 0.;
  double jdTt2 = 0.;
  iauUtctai(jdUtc.first, jdUtc.second, &jdTai1, &jdTai2);
  iauTaitt(jdTai1, jdTai2, &jdTt1, &jdTt2);

  return util::fromSofaJd<TT>(jdTt1, jdTt2);
}

a_t::TimePoint a_t_ch::taiToUt1(const TimePoint& tai)
{
  const auto jdTai = timePointToSofaJd(tai);
  double jdUt1_1 = 0.;
  double jdUt1_2 = 0.;
  iauTaiut1(jdTai.first, jdTai.second, 0, &jdUt1_1, &jdUt1_1); // TODO: fix dt (IERS table)

  return util::fromSofaJd<UT1>(jdUt1_1, jdUt1_2);
}

a_t::TimePoint a_t_ch::ttToUt1(const TimePoint& tt)
{
  const auto jdTt = timePointToSofaJd(tt);
  double jdUt1_1 = 0.;
  double jdUt1_2 = 0.;
  iauTtut1(jdTt.first, jdTt.second, 0, &jdUt1_1, &jdUt1_2);

  return util::fromSofaJd<UT1>(jdUt1_1, jdUt1_2);
}

a_t::TimePoint a_t_ch::utcToUt1(const TimePoint& utc)
{
  const auto jdUtc = timePointToSofaJd(utc);
  double jdUt1_1 = 0.;
  double jdUt1_2 = 0.;
  iauUtcut1(jdUtc.first, jdUtc.second, 0, &jdUt1_1, &jdUt1_2);

  return util::fromSofaJd<UT1>(jdUt1_1, jdUt1_2);
}

a_t::TimePoint a_t_ch::ut1ToUtc(const TimePoint& ut1)
{
  const auto jdUt1 = timePointToSofaJd(ut1);
  double jdUtc1 = 0.;
  double jdUtc2 = 0.;
  iauUt1utc(jdUt1.first, jdUt1.second, 0, &jdUtc1, &jdUtc2);

  return util::fromSofaJd<UTC>(jdUtc1, jdUtc2);
}

a_t::TimePoint a_t_ch::taiToUtc(const TimePoint& tai)
{
  const auto jdTai = timePointToSofaJd(tai);
  double jdUtc1 = 0.;
  double jdUtc2 = 0.;
  iauTaiutc(jdTai.first, jdTai.second, &jdUtc1, &jdUtc2);

  return util::fromSofaJd<UTC>(jdUtc1, jdUtc2);
}

a_t::TimePoint a_t_ch::ttToUtc(const TimePoint& tt)
{
  const auto jdTt = timePointToSofaJd(tt);
  double jdTai1 = 0.;
  double jdTai2 = 0.;
  double jdUtc1 = 0.;
  double jdUtc2 = 0.;
  iauTttai(jdTt.first, jdTt.second, &jdTai1, &jdTai2);
  iauTaiutc(jdTai1, jdTai2, &jdUtc1, &jdUtc2);

  return util::fromSofaJd<UTC>(jdUtc1, jdUtc2);
}
