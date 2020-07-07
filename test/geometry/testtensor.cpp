#include <gtest/gtest.h>

#include "geometry/tensor.h"

using namespace asf::geometry;

TEST(TensorTests, Construction)
{
  EXPECT_NO_THROW(Tensor(nullptr););
}
