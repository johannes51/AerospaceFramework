#include <gtest/gtest.h>

#include "util/sofa_helper.h"

#include "mock/mockcjd.h"

using namespace asf::time;
using namespace asf::util;

TEST(SofaHelpers, MjdSofaJd)
{
  auto mjd = ModifiedJulianDate<UTC>::fromMjdDataYourResponsibility({ 0, 0.5 });

  auto sjd = toSofaJd(mjd);

  EXPECT_DOUBLE_EQ(sjd.first + sjd.second, 2400001.);
}

TEST(SofaHelpers, generalJdSofaJd)
{
  auto mjd = MockCjd({ 2400000, 1. });

  auto sjd = toSofaJd(static_cast<a_t::ClassicalJulianDate<UTC>&>(mjd));

  EXPECT_DOUBLE_EQ(sjd.first + sjd.second, 2400001.);
}

TEST(SofaHelpers, calSofaJd)
{
  auto utc = UTC { { 1858, 11, 17, 12, 0, 0. } }; // MJD epoch from wikipedia (+ half a day as in the expected output)

  auto sjd = toSofaJd(utc);

  EXPECT_DOUBLE_EQ(sjd.first + sjd.second, 2400001.);
}

TEST(SofaHelpers, SofaJdMjd)
{
  auto mjd = fromSofaJd<ModifiedJulianDate<UTC>>(2400000.5, 0.5);

  EXPECT_EQ(mjd.wholeDays(), 0);
  EXPECT_DOUBLE_EQ(mjd.dayFraction(), 0.5);
}
