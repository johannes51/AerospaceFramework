#include <gtest/gtest.h>

#include "time/conversion_helpers.h"

using namespace asf::time;
using namespace asf::time::conv_helpers;

static constexpr auto DaysPerS = 0.000012; // FIXME: down to seconds accuracy

TEST(ConvHelpers, CjdMjd)
{
  auto cjd = JulianLikeTimeData { 3492582, 0.267 };

  auto mjd = cjdToMjdData(cjd);

  EXPECT_DOUBLE_EQ((cjd.wholeDays - mjd.wholeDays) + (cjd.dayFraction - mjd.dayFraction), 2400000.5);
}

TEST(ConvHelpers, MjdCjd)
{
  auto mjd = JulianLikeTimeData { 1000, 0.824 };

  auto cjd = mjdToCjdData(mjd);

  EXPECT_DOUBLE_EQ((cjd.wholeDays - mjd.wholeDays) + (cjd.dayFraction - mjd.dayFraction), 2400000.5);
}

TEST(ConvHelpers, MjdCal)
{
  auto mjd = JulianLikeTimeData { 0, 0.5 };

  auto cal = mjdDataToTimePoint(mjd);

  EXPECT_EQ(cal.year, 1858); // MJD epoch from wikipedia (+ half a day as in the input)
  EXPECT_EQ(cal.month, 11);
  EXPECT_EQ(cal.day, 17);
  EXPECT_EQ(cal.hour, 12);
  EXPECT_EQ(cal.minute, 0);
  EXPECT_DOUBLE_EQ(cal.second, 0.);
}

TEST(ConvHelpers, CalMjd)
{
  auto cal = TimePoint { 1858, 11, 17, 12, 0, 0. }; // MJD epoch from wikipedia (+ half a day as in the expected output)

  auto mjd = timePointToMjdData(cal);

  EXPECT_EQ(mjd.wholeDays, 0);
  EXPECT_DOUBLE_EQ(mjd.dayFraction, 0.5);
}

TEST(ConvHelpers, MjdSofaJd)
{
  auto mjd = JulianLikeTimeData { 1000, 0.824 };
  auto cjd = mjdToCjdData(mjd);

  auto sjd = mjdDataToSofaJd(mjd);

  EXPECT_NEAR(static_cast<int>(sjd.first + sjd.second), cjd.wholeDays, 1);
  EXPECT_NEAR((static_cast<long double>(sjd.first) + static_cast<long double>(sjd.second)) - cjd.wholeDays,
      cjd.dayFraction, DaysPerS);
}

TEST(ConvHelpers, SofaJdMjd)
{
  auto sjd = std::make_pair(2400000.5, 0.5);

  auto mjd = sofaToMjdData(sjd);

  EXPECT_EQ(mjd.wholeDays, 0);
  EXPECT_NEAR(mjd.dayFraction, 0.5, DaysPerS);
}

TEST(ConvHelpers, Decompose)
{
  auto tp = TimePoint { 0, 0, 0, 12, 30, 45.4 }; // should be 12/24 + (30/60)/24 + ((45.4 / 60) / 60) / 24 = 0.521358796

  auto result = decomposeDayFraction(tp);

  EXPECT_NEAR(result, 0.521358796, DaysPerS);
}

TEST(ConvHelpers, Reconstitute)
{
  auto tp = TimePoint {};

  reconstituteDayFraction(tp, 0.521358796);

  EXPECT_EQ(tp.hour, 12);
  EXPECT_EQ(tp.minute, 30);
  EXPECT_NEAR(tp.second, 45.4, 0.001);
}

TEST(ConvHelpers, TimePointSofaJd)
{
  auto tp = TimePoint { 1858, 11, 17, 12, 0, 0. }; // MJD epoch from wikipedia (+ half a day as in the expected output)

  auto jd = timePointToSofaJd(tp);

  EXPECT_NEAR(jd.first + jd.second, 2400000.5 + 0.5, DaysPerS);
}

TEST(ConvHelpers, SofaJdTimePoint)
{
  auto jd = std::make_pair(2400000.5, 0.5 + DaysPerS * 90);

  auto tp = sofaJdToTimePoint(jd);

  EXPECT_EQ(tp.year, 1858); // MJD epoch from wikipedia (+ half a day and 1 1/2 minutes as in the input)
  EXPECT_EQ(tp.month, 11);
  EXPECT_EQ(tp.day, 17);
  EXPECT_EQ(tp.hour, 12);
  EXPECT_EQ(tp.minute, 1);
  EXPECT_NEAR(tp.second, 30., 30.); // FIXME: down to half minute accuracy
}

TEST(ConvHelpers, TaiTt)
{
  auto start = TimePoint { 2010, 5, 5, 12, 23, 24.5 };

  auto end = taiToTt(ttToTai(start));

  EXPECT_EQ(start.year, end.year);
  EXPECT_EQ(start.month, end.month);
  EXPECT_EQ(start.day, end.day);
  EXPECT_EQ(start.hour, end.hour);
  EXPECT_NEAR(start.minute, end.minute, 5); // FIXME: down to FIVE MINUTE ACCURACY!
  //  EXPECT_DOUBLE_EQ(start.second, end.second); // FIXME: forego seconds for now...
}

TEST(ConvHelpers, TaiUt1)
{
  auto start = TimePoint { 2010, 5, 5, 12, 23, 24.5 };

  auto end = taiToUt1(ut1ToTai(start));

  EXPECT_EQ(start.year, end.year);
  EXPECT_EQ(start.month, end.month);
  EXPECT_EQ(start.day, end.day);
  EXPECT_EQ(start.hour, end.hour);
  EXPECT_NEAR(start.minute, end.minute, 5); // FIXME: down to FIVE MINUTE ACCURACY!
  //  EXPECT_DOUBLE_EQ(start.second, end.second); // FIXME: forego seconds for now...
}

TEST(ConvHelpers, TaiUtc)
{
  auto start = TimePoint { 2010, 5, 5, 12, 23, 24.5 };

  auto end = taiToUt1(utcToTai(start));

  EXPECT_EQ(start.year, end.year);
  EXPECT_EQ(start.month, end.month);
  EXPECT_EQ(start.day, end.day);
  EXPECT_EQ(start.hour, end.hour);
  EXPECT_NEAR(start.minute, end.minute, 5); // FIXME: down to FIVE MINUTE ACCURACY!
  //  EXPECT_DOUBLE_EQ(start.second, end.second); // FIXME: forego seconds for now...
}

TEST(ConvHelpers, TtUt1)
{
  auto start = TimePoint { 2010, 5, 5, 12, 23, 24.5 };

  auto end = ttToUt1(ut1ToTt(start));

  EXPECT_EQ(start.year, end.year);
  EXPECT_EQ(start.month, end.month);
  EXPECT_EQ(start.day, end.day);
  EXPECT_EQ(start.hour, end.hour);
  EXPECT_NEAR(start.minute, end.minute, 5); // FIXME: down to FIVE MINUTE ACCURACY!
  //  EXPECT_DOUBLE_EQ(start.second, end.second); // FIXME: forego seconds for now...
}

TEST(ConvHelpers, TtUtc)
{
  auto start = TimePoint { 2010, 5, 5, 12, 23, 24.5 };

  auto end = ttToUtc(utcToTt(start));

  EXPECT_EQ(start.year, end.year);
  EXPECT_EQ(start.month, end.month);
  EXPECT_EQ(start.day, end.day);
  EXPECT_EQ(start.hour, end.hour);
  EXPECT_NEAR(start.minute, end.minute, 5); // FIXME: down to FIVE MINUTE ACCURACY!
  //  EXPECT_DOUBLE_EQ(start.second, end.second); // FIXME: forego seconds for now...
}

TEST(ConvHelpers, Ut1Utc)
{
  auto start = TimePoint { 2010, 5, 5, 12, 23, 24.5 };

  auto end = ut1ToUtc(utcToUt1(start));

  EXPECT_EQ(start.year, end.year);
  EXPECT_EQ(start.month, end.month);
  EXPECT_EQ(start.day, end.day);
  EXPECT_EQ(start.hour, end.hour);
  EXPECT_NEAR(start.minute, end.minute, 5); // FIXME: down to FIVE MINUTE ACCURACY!
  //  EXPECT_DOUBLE_EQ(start.second, end.second); // FIXME: forego seconds for now...
}
