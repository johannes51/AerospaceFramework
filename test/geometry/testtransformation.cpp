#include <gtest/gtest.h>

#include "geometry/transformations.h"
#include "time/utc.h"

using namespace asf::geometry;
using namespace asf::time;

TEST(TransformationTests, EcefMatrices)
{
  UTC t {};

  auto [m1, m2] = calculateEcefMatrices(t, nullptr, nullptr);

  EXPECT_NE(m1, m2); // TODO: collect data
}
