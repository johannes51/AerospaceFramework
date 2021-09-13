#include <gtest/gtest.h>

#include <cmath>

#include "time/conversions.h"
#include "time/tt.h"
#include "time/utc.h"

using namespace asf::time;

bool timesEqualTt(TimePoint a, const Time& b)
{
  auto bTp = static_cast<TimePoint>(convert<TT>(b));
  return a.year == bTp.year && a.month == bTp.month && a.day == bTp.day && a.hour == bTp.hour
      && abs(a.minute - bTp.minute) < 5
      /*&& fabs(a.second - bTp.second)*/; // TODO: FIVE MINUTE accuracy...
}

TEST(TtTests, Construction)
{
  EXPECT_NO_THROW(TT(););
}

TEST(TtTests, Conversion1)
{
  UTC u({ 2020, 11, 20, 13, 33, 14 });
  auto ttTp = static_cast<TimePoint>(convert<TT>(u));
  EXPECT_EQ(ttTp.year, 2020);
  EXPECT_EQ(ttTp.month, 11);
  EXPECT_EQ(ttTp.day, 20);
  EXPECT_EQ(ttTp.hour, 13);
  EXPECT_EQ(ttTp.minute, 34);
  EXPECT_NEAR(ttTp.second, 24, 1.); // FIXME: seconds accuracy
}

TEST(TtTests, Conversion2)
{
  TT t({ 2020, 11, 20, 13, 34, 24 });
  auto uTp = static_cast<TimePoint>(convert<UTC>(t));
  EXPECT_EQ(uTp.year, 2020);
  EXPECT_EQ(uTp.month, 11);
  EXPECT_EQ(uTp.day, 20);
  EXPECT_EQ(uTp.hour, 13);
  EXPECT_EQ(uTp.minute, 33);
  EXPECT_NEAR(uTp.second, 14, 1.); // FIXME: seconds accuracy
}

TEST(TtTests, Conversion3)
{
  UTC u({ 1999, 9, 3, 7, 47, 53 });
  auto ttTp = static_cast<TimePoint>(convert<TT>(u));
  EXPECT_EQ(ttTp.year, 1999);
  EXPECT_EQ(ttTp.month, 9);
  EXPECT_EQ(ttTp.day, 3);
  EXPECT_EQ(ttTp.hour, 7);
  EXPECT_EQ(ttTp.minute, 48);
  EXPECT_NEAR(ttTp.second, 57, 1.); // FIXME: seconds accuracy
}

TEST(TtTests, Conversion4)
{
  TT tt({ 1999, 9, 3, 7, 48, 57 });
  auto uTp = static_cast<TimePoint>(convert<UTC>(tt));
  EXPECT_EQ(uTp.year, 1999);
  EXPECT_EQ(uTp.month, 9);
  EXPECT_EQ(uTp.day, 3);
  EXPECT_EQ(uTp.hour, 7);
  EXPECT_EQ(uTp.minute, 47);
  EXPECT_NEAR(uTp.second, 53, 1.); // FIXME: seconds accuracy
}

TEST(TtTests, ConversionRest)
{
  auto start = TT { { 1999, 9, 3, 7, 47, 20 } };

  EXPECT_TRUE(timesEqualTt(start, convert<UT1>(start)));
}
