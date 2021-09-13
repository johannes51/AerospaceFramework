#include <gtest/gtest.h>

#include <cmath> // for fabs

#include "time/conversions.h"

using namespace asf::time;

bool timesEqual(TimePoint a, const Time& b)
{
  auto bTp = static_cast<TimePoint>(convert<UTC>(b));
  return a.year == bTp.year && a.month == bTp.month && a.day == bTp.day && a.hour == bTp.hour && a.minute == bTp.minute
      && fabs(a.second - bTp.second) < 0.001;
}

TEST(Conversion, Same)
{
  auto orig = UTC { std::chrono::system_clock::now() };
  const auto& conv = convert<UTC>(orig);
  EXPECT_EQ(&conv, &orig);
}

TEST(Conversion, JulianLikes)
{
  auto orig = UTC { std::chrono::system_clock::now() };
  EXPECT_TRUE(timesEqual(orig, convert<ClassicalJulianDate<TAI>>(orig)));
  EXPECT_TRUE(timesEqual(orig, convert<ClassicalJulianDate<TT>>(orig)));
  EXPECT_TRUE(timesEqual(orig, convert<ClassicalJulianDate<UT1>>(orig)));
  EXPECT_TRUE(timesEqual(orig, convert<ClassicalJulianDate<UTC>>(orig)));
  EXPECT_TRUE(timesEqual(orig, convert<ModifiedJulianDate<TAI>>(orig)));
  EXPECT_TRUE(timesEqual(orig, convert<ModifiedJulianDate<TT>>(orig)));
  EXPECT_TRUE(timesEqual(orig, convert<ModifiedJulianDate<UT1>>(orig)));
  EXPECT_TRUE(timesEqual(orig, convert<ModifiedJulianDate<UTC>>(orig)));
}

TEST(Conversion, Calendar)
{
  auto orig = UTC { std::chrono::system_clock::now() };
  EXPECT_TRUE(timesEqual(orig, convert<TAI>(orig)));
  EXPECT_TRUE(timesEqual(orig, convert<TT>(orig)));
  EXPECT_TRUE(timesEqual(orig, convert<UT1>(orig)));
  EXPECT_TRUE(timesEqual(orig, convert<UTC>(orig)));
}

TEST(Conversion, Throws)
{
  class MockTime : public Time {
  };
  class MockCalTime : public CalendarTime {
  };
  class MockJd : public JulianLikeTimeImp<UTC> {
  };
  EXPECT_ANY_THROW(convert<UTC>((const Time&)MockTime {}));
  EXPECT_ANY_THROW(convert<UTC>((const Time&)MockCalTime {}));
  EXPECT_ANY_THROW(convert<UTC>((const Time&)MockJd {}));
  EXPECT_ANY_THROW(convert<UTC>((const Time&)ClassicalJulianDate<MockCalTime> {}));
}
