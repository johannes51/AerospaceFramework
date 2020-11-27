#include <gtest/gtest.h>

#include "time/conversions.h"
#include "time/utc.h"

using namespace asf::time;

TEST(UtcTests, Construction1)
{
  EXPECT_NO_THROW(UTC(););
}

TEST(UtcTests, Construction2)
{
  EXPECT_NO_THROW(UTC utc(std::chrono::system_clock::now()););
}

TEST(UtcTests, Construction3)
{
  EXPECT_NO_THROW(UTC utc({2020, 12, 15, 16, 35, 34.}););
}

TEST(UtcTests, FromChrono)
{
  auto now = std::chrono::system_clock::now();
  UTC utc(now);
  auto tt = std::chrono::system_clock::to_time_t(now);
  auto* tm = gmtime(&tt);
  EXPECT_EQ(utc.timePoint().year, tm->tm_year);
  EXPECT_EQ(utc.timePoint().month, tm->tm_mon);
  EXPECT_EQ(utc.timePoint().day, tm->tm_mday);
  EXPECT_EQ(utc.timePoint().hour, tm->tm_hour + 1);
  EXPECT_EQ(utc.timePoint().minute, tm->tm_min);
  EXPECT_EQ(utc.timePoint().second, tm->tm_sec);
}

TEST(UtcTests, FromTimePoint)
{
  UTC utc({2020, 12, 15, 16, 35, 34.});
  EXPECT_EQ(utc.timePoint().year, 2020);
  EXPECT_EQ(utc.timePoint().month, 12);
  EXPECT_EQ(utc.timePoint().day, 15);
  EXPECT_EQ(utc.timePoint().hour, 16);
  EXPECT_EQ(utc.timePoint().minute, 35);
  EXPECT_EQ(utc.timePoint().second, 34.);
}
