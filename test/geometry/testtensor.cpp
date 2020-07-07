#include <gtest/gtest.h>

#include "geometry/tensor.h"

TEST(TensorTests, Construction)
{
  EXPECT_NO_THROW(Tensor(nullptr););
}
