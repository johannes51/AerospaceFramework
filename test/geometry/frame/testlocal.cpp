#include <gtest/gtest.h>

#include "geometry/frame/eci.h"
#include "geometry/frame/local.h"
#include "geometry/tensor.h"
#include "geometry/vector.h"

using namespace asf;
using namespace asf::geometry;

TEST(LocalTests, Construction)
{
  EXPECT_NO_THROW(Local(););
}

TEST(LocalTests, Embed)
{
  auto eci = std::make_shared<ECI>(nullptr);
  auto local = std::make_shared<Local>();
  auto vecOff = std::make_shared<Vector>(eci.get(), 1.5, 1.5, 1.5, TransformationBehaviour::Position);
  local->attach(eci.get(), vecOff);
  auto vecEci = std::make_shared<Vector>(eci.get(), 1, 1, 1, TransformationBehaviour::Position);

  auto vecLocal = local->to(*vecEci, local.get());

  EXPECT_NEAR(vecLocal.element(0), -0.5, 0.01);
  EXPECT_NEAR(vecLocal.element(1), -0.5, 0.01);
  EXPECT_NEAR(vecLocal.element(2), -0.5, 0.01);
}

TEST(LocalTests, Unwind)
{
  auto eci = std::make_shared<ECI>(nullptr);
  auto local = std::make_shared<Local>();
  auto vecOff = std::make_shared<Vector>(eci.get(), 2.5, 2.5, 2.5, TransformationBehaviour::Position);
  local->attach(eci.get(), vecOff);
  auto vecLocal = std::make_shared<Vector>(local.get(), 1, 1, 1, TransformationBehaviour::Position);

  auto vecEci = local->to(*vecLocal, eci.get());

  EXPECT_NEAR(vecEci.element(0), 3.5, 0.01);
  EXPECT_NEAR(vecEci.element(1), 3.5, 0.01);
  EXPECT_NEAR(vecEci.element(2), 3.5, 0.01);
}
