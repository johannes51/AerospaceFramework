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
  EXPECT_NO_THROW(UTC utc({ 2020, 12, 15, 16, 35, 34. }););
}

TEST(UtcTests, FromChrono)
{
  auto now = std::chrono::system_clock::now();
  auto utc = static_cast<TimePoint>(UTC { now });
  auto tt = std::chrono::system_clock::to_time_t(now);
  auto* tm = gmtime(&tt);
  EXPECT_EQ(utc.year, tm->tm_year);
  EXPECT_EQ(utc.month, tm->tm_mon);
  EXPECT_EQ(utc.day, tm->tm_mday);
  EXPECT_EQ(utc.hour, tm->tm_hour + 1);
  EXPECT_EQ(utc.minute, tm->tm_min);
  EXPECT_EQ(utc.second, tm->tm_sec);
}

TEST(UtcTests, FromTimePoint)
{
  auto utc = static_cast<TimePoint>(UTC { { 2020, 12, 15, 16, 35, 34. } });
  EXPECT_EQ(utc.year, 2020);
  EXPECT_EQ(utc.month, 12);
  EXPECT_EQ(utc.day, 15);
  EXPECT_EQ(utc.hour, 16);
  EXPECT_EQ(utc.minute, 35);
  EXPECT_EQ(utc.second, 34.);
}
