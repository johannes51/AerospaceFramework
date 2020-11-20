#include <gtest/gtest.h>

#include "time/tai.h"
#include "time/utc.h"
#include "time/conversions.h"

using namespace asf::time;

TEST(TaiTests, Construction)
{
  EXPECT_NO_THROW(TAI(););
}

TEST(TaiTests, Conversion1)
{
  UTC u({2020, 11, 20, 13, 33, 14});
  auto taiTp = convert<TAI>(u).timePoint();
  EXPECT_EQ(taiTp.year, 2020);
  EXPECT_EQ(taiTp.month, 11);
  EXPECT_EQ(taiTp.day, 20);
  EXPECT_EQ(taiTp.hour, 13);
  EXPECT_EQ(taiTp.minute, 32);
  EXPECT_EQ(taiTp.second, 41);
}

TEST(TaiTests, Conversion2)
{
  TAI t({2020, 11, 20, 13, 32, 41});
  auto uTp = convert<UTC>(t).timePoint();
  EXPECT_EQ(uTp.year, 2020);
  EXPECT_EQ(uTp.month, 11);
  EXPECT_EQ(uTp.day, 20);
  EXPECT_EQ(uTp.hour, 13);
  EXPECT_EQ(uTp.minute, 33);
  EXPECT_EQ(uTp.second, 14);
}

TEST(TaiTests, Conversion3)
{
  UTC u({1999, 9, 3, 7, 47, 53});
  auto taiTp = convert<TAI>(u).timePoint();
  EXPECT_EQ(taiTp.year, 1999);
  EXPECT_EQ(taiTp.month, 9);
  EXPECT_EQ(taiTp.day, 3);
  EXPECT_EQ(taiTp.hour, 7);
  EXPECT_EQ(taiTp.minute, 47);
  EXPECT_EQ(taiTp.second, 20);
}

TEST(TaiTests, Conversion4)
{
  TAI tai({1999, 9, 3, 7, 47, 20});
  auto uTp = convert<UTC>(tai).timePoint();
  EXPECT_EQ(uTp.year, 1999);
  EXPECT_EQ(uTp.month, 9);
  EXPECT_EQ(uTp.day, 3);
  EXPECT_EQ(uTp.hour, 7);
  EXPECT_EQ(uTp.minute, 47);
  EXPECT_EQ(uTp.second, 53);
}

