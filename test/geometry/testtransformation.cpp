#include <gtest/gtest.h>

#include "geometry/tensor.h"
#include "geometry/transformations.h"
#include "time/utc.h"

using namespace asf::geometry;
using namespace asf::time;

TEST(TransformationTests, EcefMatrices)
{
  UTC t { { 2014, 1, 9, 2, 35, 34. } };

  auto [m1, m2] = calculateEcefMatrices(t, nullptr, nullptr);

  EXPECT_NEAR(m1->element(0, 0), -0.8412, 0.002);
  EXPECT_NEAR(m1->element(0, 1), +0.5407, 0.002);
  EXPECT_NEAR(m1->element(0, 2), +0.0012, 0.002);
  EXPECT_NEAR(m1->element(1, 0), -0.5406, 0.002);
  EXPECT_NEAR(m1->element(1, 1), -0.8412, 0.002);
  EXPECT_NEAR(m1->element(1, 2), +0.0007, 0.002);
  EXPECT_NEAR(m1->element(2, 0), -0.0014, 0.002);
  EXPECT_NEAR(m1->element(2, 1), -0.0000, 0.002);
  EXPECT_NEAR(m1->element(2, 2), +1.0000, 0.002);

  EXPECT_NEAR(m2->element(0, 0), -0.8412, 0.002);
  EXPECT_NEAR(m2->element(0, 1), -0.5406, 0.002);
  EXPECT_NEAR(m2->element(0, 2), -0.0014, 0.002);
  EXPECT_NEAR(m2->element(1, 0), +0.5407, 0.002);
  EXPECT_NEAR(m2->element(1, 1), -0.8412, 0.002);
  EXPECT_NEAR(m2->element(1, 2), +0.0007, 0.002);
  EXPECT_NEAR(m2->element(2, 0), +0.0012, 0.002);
  EXPECT_NEAR(m2->element(2, 1), -0.0000, 0.002);
  EXPECT_NEAR(m2->element(2, 2), +1.0000, 0.002);
}
