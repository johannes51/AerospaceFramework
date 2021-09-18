#include <gtest/gtest.h>

#include "geometry/frame/eci.h"
#include "geometry/frame/vehicleframe.h"
#include "geometry/vector.h"

using namespace asf;
using namespace asf::geometry;

TEST(VehicleFrameTests, Construction)
{
  EXPECT_NO_THROW(VehicleFrame {});
}

TEST(VehicleFrameTests, Unwind)
{
  auto eci = std::make_shared<ECI>(nullptr);
  auto v = std::make_shared<VehicleFrame>();
  v->attach(eci.get());
  auto vecV = std::make_shared<Vector>(v.get(), 1, 1, 1, TransformationBehaviour::Position);
  // TODO: collect data
  auto vecEci = v->to(*vecV, FrameType::ECI);

  EXPECT_NEAR(vecEci.element(0), 1., 0.01e6);
  EXPECT_NEAR(vecEci.element(1), 1., 0.01e6);
  EXPECT_NEAR(vecEci.element(2), 1., 0.01e6);
}

TEST(VehicleFrameTests, Embed)
{
  auto eci = std::make_shared<ECI>(nullptr);
  auto v = std::make_shared<VehicleFrame>();
  v->attach(eci.get());
  auto vecEci = std::make_shared<Vector>(eci.get(), 1, 1, 1, TransformationBehaviour::Position);
  // TODO: collect data
  auto vecV = v->to(*vecEci, v.get());

  EXPECT_NEAR(vecV.element(0), 1., 0.01);
  EXPECT_NEAR(vecV.element(1), 1., 0.01);
  EXPECT_NEAR(vecV.element(2), 1., 0.01);
}
