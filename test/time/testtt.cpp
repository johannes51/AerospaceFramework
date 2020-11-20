#include <gtest/gtest.h>

#include "time/tt.h"
#include "time/utc.h"
#include "time/conversions.h"

using namespace asf::time;

TEST(TtTests, Construction)
{
  EXPECT_NO_THROW(TT(););
}

TEST(TtTests, Conversion1)
{
  UTC u({2020, 11, 20, 13, 33, 14});
  auto ttTp = convert<TT>(u).timePoint();
  EXPECT_EQ(ttTp.year, 2020);
  EXPECT_EQ(ttTp.month, 11);
  EXPECT_EQ(ttTp.day, 20);
  EXPECT_EQ(ttTp.hour, 13);
  EXPECT_EQ(ttTp.minute, 34);
  EXPECT_EQ(ttTp.second, 24);
}

TEST(TtTests, Conversion2)
{
  TT t({2020, 11, 20, 13, 34, 24});
  auto uTp = convert<UTC>(t).timePoint();
  EXPECT_EQ(uTp.year, 2020);
  EXPECT_EQ(uTp.month, 11);
  EXPECT_EQ(uTp.day, 20);
  EXPECT_EQ(uTp.hour, 13);
  EXPECT_EQ(uTp.minute, 33);
  EXPECT_EQ(uTp.second, 14);
}

TEST(TtTests, Conversion3)
{
  UTC u({1999, 9, 3, 7, 47, 53});
  auto ttTp = convert<TT>(u).timePoint();
  EXPECT_EQ(ttTp.year, 1999);
  EXPECT_EQ(ttTp.month, 9);
  EXPECT_EQ(ttTp.day, 3);
  EXPECT_EQ(ttTp.hour, 7);
  EXPECT_EQ(ttTp.minute, 48);
  EXPECT_EQ(ttTp.second, 57);
}

TEST(TtTests, Conversion4)
{
  TT tt({1999, 9, 3, 7, 48, 57});
  auto uTp = convert<UTC>(tt).timePoint();
  EXPECT_EQ(uTp.year, 1999);
  EXPECT_EQ(uTp.month, 9);
  EXPECT_EQ(uTp.day, 3);
  EXPECT_EQ(uTp.hour, 7);
  EXPECT_EQ(uTp.minute, 47);
  EXPECT_EQ(uTp.second, 53);
}

