#include <gtest/gtest.h>

#include "geometry/frame/ecef.h"
#include "geometry/frame/eci.h"
#include "geometry/vector.h"
#include "time/utc.h"

using namespace asf;
using namespace asf::geometry;

TEST(EcefTests, Construction)
{
  EXPECT_NO_THROW(ECEF(nullptr, time::UTC(std::chrono::system_clock::now())));
}

TEST(EcefTests, Embed)
{
  using namespace std::chrono_literals;
  auto eci = std::make_shared<ECI>(nullptr);
  auto ecef = std::make_shared<ECEF>(eci.get(), time::UTC({ 2014, 1, 9, 2, 35, 34. }));
  auto vecEci = std::make_shared<Vector>(eci.get(), 1, 1, 1, TransformationBehaviour::Position);

  auto vecEcef = ecef->to(*vecEci, ecef.get());

  EXPECT_NEAR(vecEcef.element(0), -0.2994111, 0.01);
  EXPECT_NEAR(vecEcef.element(1), -1.3811847, 0.01);
  //  EXPECT_NEAR(vecEcef.element(2), 1.0013399, 0.01); // TODO: collect data
}

TEST(EcefTests, Unwind)
{
  using namespace std::chrono_literals;
  auto eci = std::make_shared<ECI>(nullptr);
  auto ecef = std::make_shared<ECEF>(eci.get(), time::UTC({ 2014, 1, 9, 2, 35, 34. }));
  auto vecEcef = std::make_shared<Vector>(eci.get(), 1, 1, 1, TransformationBehaviour::Position);

  auto vecEci = ecef->to(*vecEcef, eci.get());

  EXPECT_NEAR(vecEci.element(0), -1.3805, 0.01);
  EXPECT_NEAR(vecEci.element(1), -0.3006, 0.01);
  //  EXPECT_NEAR(vecEci.element(2), 1.0018, 0.01); // TODO: collect data
}
