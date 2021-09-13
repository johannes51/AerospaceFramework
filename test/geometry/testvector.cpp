#include <gtest/gtest.h>

#include "mock/mockvector.h"

#include "geometry/frame/eci.h"
#include "geometry/frame/local.h"
#include "geometry/frame/wgs84.h"
#include "geometry/vector.h"

using namespace asf::geometry;

TEST(VectorTests, Construction)
{
  EXPECT_NO_THROW(Vector(new ECI(nullptr)));
}

TEST(VectorTests, Element)
{
  Vector v(new ECI(nullptr));
  v.element(0) = 1;
  v.element(1) = 2;
  v.element(2) = 4;

  EXPECT_EQ(v.element(0), 1);
  EXPECT_EQ(v.element(1), 2);
  EXPECT_EQ(v.element(2), 4);
}

TEST(VectorTests, Comparison1)
{
  Vector a1(new ECI(nullptr));
  a1.element(0) = 1;
  a1.element(1) = 2;
  a1.element(2) = 4;
  Vector a2(new ECI(nullptr));
  a2.element(0) = 1;
  a2.element(1) = 2;
  a2.element(2) = 4;
  EXPECT_TRUE(a1 == a2);
  EXPECT_FALSE(a1 != a2);
}

TEST(VectorTests, Comparison2)
{
  Vector a1(new ECI(nullptr));
  auto l = std::make_shared<Local>();
  Vector a2(l.get());
  a2.element(0) = 1;
  a2.element(1) = 2;
  a2.element(2) = 3;
  EXPECT_FALSE(a1 == a2);
  EXPECT_TRUE(a1 != a2);
}

TEST(VectorTests, Comparison3)
{
  Vector a1(new ECI(nullptr));
  a1.element(0) = 1;
  a1.element(1) = 2;
  a1.element(2) = 3;
  Vector a2(new ECI(nullptr));
  a2.element(0) = 1;
  a2.element(1) = 2;
  a2.element(2) = 4;
  EXPECT_FALSE(a1 == a2);
  EXPECT_TRUE(a1 != a2);
}

TEST(VectorTests, Addition1)
{
  Vector a1(new ECI(nullptr));
  a1.element(0) = 1;
  a1.element(1) = 2;
  a1.element(2) = 4;
  auto l = std::make_shared<Local>();
  Vector a2(l.get());
  a2.element(0) = 5;
  a2.element(0) = 7;
  a2.element(0) = 8;
  EXPECT_ANY_THROW(a1 + a2);
}

TEST(VectorTests, Addition2)
{
  Vector a1(new ECI(nullptr));
  a1.element(0) = 1;
  a1.element(1) = 2;
  a1.element(2) = 4;
  Vector a2(new ECI(nullptr));
  a2.element(0) = 5;
  a2.element(1) = 7;
  a2.element(2) = 8;
  Vector expected(new ECI(nullptr));
  expected.element(0) = 6;
  expected.element(1) = 9;
  expected.element(2) = 12;
  EXPECT_TRUE(a1 + a2 == expected);
}
