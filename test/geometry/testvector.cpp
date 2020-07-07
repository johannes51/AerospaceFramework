#include <gtest/gtest.h>

#include "mock/mockvector.h"

#include "geometry/frame/eci.h"
#include "geometry/frame/local.h"
#include "geometry/frame/wgs84.h"
#include "geometry/vector.h"

TEST(VectorTests, Construction)
{
  EXPECT_NO_THROW(Vector(new ECI((Frame*)1)));
}

TEST(VectorTests, To1)
{
  Vector v(new ECI((Frame*)1));
  //  EXPECT_EQ(v.to(FrameType::ECI).frame(), FrameType::ECI); // TODO: enable test
}

TEST(VectorTests, To2)
{
  //  Vector v(std::make_shared<Wgs84>(std::chrono::system_clock::now()), 80, 80, 100);
  //  EXPECT_EQ(v.to(FrameType::ECI).frame(), FrameType::ECI); // TODO: enable test
}

TEST(VectorTests, Element)
{
  Vector v(new ECI((Frame*)1));
  v.element(0) = 1;
  v.element(1) = 2;
  v.element(2) = 4;

  EXPECT_EQ(v.element(0), 1);
  EXPECT_EQ(v.element(1), 2);
  EXPECT_EQ(v.element(2), 4);
}

TEST(VectorTests, Comparison1)
{
  Vector a1(new ECI((Frame*)1));
  a1.element(0) = 1;
  a1.element(1) = 2;
  a1.element(2) = 4;
  Vector a2(new ECI((Frame*)1));
  a2.element(0) = 1;
  a2.element(1) = 2;
  a2.element(2) = 4;
  EXPECT_TRUE(a1 == a2);
  EXPECT_FALSE(a1 != a2);
}

TEST(VectorTests, Comparison2)
{
  Vector a1(new ECI((Frame*)1));
  //  Vector a2(std::make_shared<Local>(std::shared_ptr<MockVector>()), 1, 2, 3);
  //  EXPECT_FALSE(a1 == a2);
  //  EXPECT_TRUE(a1 != a2); // TODO: enable test
}

TEST(VectorTests, Comparison3)
{
  Vector a1(new ECI((Frame*)1));
  a1.element(0) = 1;
  a1.element(1) = 2;
  a1.element(2) = 3;
  Vector a2(new ECI((Frame*)1));
  a2.element(0) = 1;
  a2.element(1) = 2;
  a2.element(2) = 4;
  EXPECT_FALSE(a1 == a2);
  EXPECT_TRUE(a1 != a2);
}

TEST(VectorTests, Addition1)
{
  Vector a1(new ECI((Frame*)1));
  a1.element(0) = 1;
  a1.element(1) = 2;
  a1.element(2) = 4;
  //  Vector a2(std::make_shared<Local>(
  //                std::make_shared<MockVector>()),
  //      5, 7, 8);
  //  EXPECT_ANY_THROW(a1 + a2); // TODO: enable test
}

TEST(VectorTests, Addition2)
{
  Vector a1(new ECI((Frame*)1));
  a1.element(0) = 1;
  a1.element(1) = 2;
  a1.element(2) = 4;
  Vector a2(new ECI((Frame*)1));
  a2.element(0) = 5;
  a2.element(1) = 7;
  a2.element(2) = 8;
  Vector expected(new ECI((Frame*)1));
  expected.element(0) = 6;
  expected.element(1) = 9;
  expected.element(2) = 12;
  EXPECT_TRUE(a1 + a2 == expected);
}
