#include <gtest/gtest.h>

#include "time/conversions.h"
#include "time/ut1.h"
#include "time/utc.h"

using namespace asf::time;

TEST(Ut1Tests, Construction)
{
  EXPECT_NO_THROW(UT1(););
}

TEST(Ut1Tests, Conversion1)
{
  UTC utc({ 2014, 1, 9, 20, 35, 34. });
  auto ut1Tp = convert<UT1>(utc).timePoint();
  EXPECT_EQ(ut1Tp.year, 2014);
  EXPECT_EQ(ut1Tp.month, 1);
  EXPECT_EQ(ut1Tp.day, 9);
  EXPECT_EQ(ut1Tp.hour, 20);
  EXPECT_EQ(ut1Tp.minute, 35);
  EXPECT_EQ(ut1Tp.second, 34.1071961);
}

TEST(Ut1Tests, Conversion2)
{
  UT1 ut1({ 2014, 1, 9, 20, 35, 34.1071961 });
  auto utcTp = convert<UTC>(ut1).timePoint();
  EXPECT_EQ(utcTp.year, 2014);
  EXPECT_EQ(utcTp.month, 1);
  EXPECT_EQ(utcTp.day, 9);
  EXPECT_EQ(utcTp.hour, 20);
  EXPECT_EQ(utcTp.minute, 35);
  EXPECT_EQ(utcTp.second, 34.);
}

TEST(Ut1Tests, Conversion3)
{
  UTC utc({ 2020, 12, 15, 16, 35, 34. });
  auto ut1Tp = convert<UT1>(utc).timePoint();
  EXPECT_EQ(ut1Tp.year, 2020);
  EXPECT_EQ(ut1Tp.month, 12);
  EXPECT_EQ(ut1Tp.day, 15);
  EXPECT_EQ(ut1Tp.hour, 16);
  EXPECT_EQ(ut1Tp.minute, 35);
  EXPECT_EQ(ut1Tp.second, 34.9);
}

TEST(Ut1Tests, Conversion4)
{
  UT1 ut1({ 2020, 12, 15, 16, 35, 34.9 });
  auto utcTp = convert<UTC>(ut1).timePoint();
  EXPECT_EQ(utcTp.year, 2020);
  EXPECT_EQ(utcTp.month, 12);
  EXPECT_EQ(utcTp.day, 15);
  EXPECT_EQ(utcTp.hour, 16);
  EXPECT_EQ(utcTp.minute, 35);
  EXPECT_EQ(utcTp.second, 34.);
}
