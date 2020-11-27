#include <gtest/gtest.h>

#include "geometry/frame/eci.h"
#include "geometry/frame/wgs84.h"
#include "geometry/vector.h"
#include "time/utc.h"

using namespace asf;
using namespace asf::geometry;

TEST(VehicleFrameTests, Construction)
{
  EXPECT_NO_THROW(Wgs84(nullptr, time::UTC(std::chrono::system_clock::now())));
}

TEST(VehicleFrameTests, Unwind)
{
  using namespace std::chrono_literals;
  auto eci = std::make_shared<ECI>(nullptr);
  auto wgs = std::make_shared<Wgs84>(eci.get(), time::UTC(/*sys_days{January/9/2014} + 2h + 35min + 34s*/));
  auto vecWgs = std::make_shared<Vector>(wgs.get(), TransformationBehaviour::Position);
  vecWgs->element(0) = 40;
  vecWgs->element(1) = 40;
  vecWgs->element(2) = 40;
  auto vecEci = wgs->to(*vecWgs, FrameType::ECI);
  EXPECT_NEAR(vecEci.element(0), -4.2848e6, 0.01e6);
  EXPECT_NEAR(vecEci.element(1), -2.3515e6, 0.01e6);
  EXPECT_NEAR(vecEci.element(2), 4.0840e6, 0.01e6);
}

TEST(VehicleFrameTests, Embed)
{
  using namespace std::chrono_literals;
  auto eci = std::make_shared<ECI>(nullptr);
  auto wgs = std::make_shared<Wgs84>(eci.get(), time::UTC(/*sys_days{January/9/2014} + 2h + 35min + 34s*/));
  auto vecEci = std::make_shared<Vector>(eci.get(), TransformationBehaviour::Position);
  vecEci->element(0) = 4e6;
  vecEci->element(1) = 4e6;
  vecEci->element(2) = 3e6;
  auto vecWgs = wgs->to(*vecEci, FrameType::LLA);
  EXPECT_NEAR(vecWgs.element(0), 28.1517, 0.01);
  EXPECT_NEAR(vecWgs.element(1), -102.2414, 0.01);
  EXPECT_NEAR(vecWgs.element(2), 29716.645, 0.01);
}
