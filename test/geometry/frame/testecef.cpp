#include <gtest/gtest.h>

#include "geometry/frame/ecef.h"
#include "geometry/frame/eci.h"
#include "geometry/vector.h"
#include "date/date.h"

TEST(EcefTests, Construction)
{
  EXPECT_NO_THROW(ECEF(nullptr, std::chrono::system_clock::now()););
}

TEST(EcefTests, Embed)
{
  using namespace date;
  using namespace std::chrono_literals;
  auto eci = std::make_shared<ECI>(nullptr);
  auto ecef = std::make_shared<ECEF>(eci.get(), sys_days{January/9/2014} + 2h + 35min + 34s);
  auto vecEci = std::make_shared<Vector>(eci.get(), TransformationBehaviour::Position);
  vecEci->element(0) = 1;
  vecEci->element(1) = 1;
  vecEci->element(2) = 1;
  auto vecEcef = ecef->to(*vecEci, ecef.get());
  EXPECT_NEAR(vecEcef.element(0), -0.2994111, 0.01);
  EXPECT_NEAR(vecEcef.element(1), -1.3811847, 0.01);
  EXPECT_NEAR(vecEcef.element(2),  1.0013399, 0.01);
}

TEST(EcefTests, Unwind)
{
  using namespace date;
  using namespace std::chrono_literals;
  auto eci = std::make_shared<ECI>(nullptr);
  auto ecef = std::make_shared<ECEF>(eci.get(), sys_days{January/9/2014} + 2h + 35min + 34s);
  auto vecEcef = std::make_shared<Vector>(eci.get(), TransformationBehaviour::Position);
  vecEcef->element(0) = 1;
  vecEcef->element(1) = 1;
  vecEcef->element(2) = 1;
  auto vecEci = ecef->to(*vecEcef, eci.get());
  EXPECT_NEAR(vecEci.element(0), -1.3805, 0.01);
  EXPECT_NEAR(vecEci.element(1), -0.3006, 0.01);
  EXPECT_NEAR(vecEci.element(2),  1.0018, 0.01);
}
