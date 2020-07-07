#pragma once

#include "geometry/tensor.h"

#include "mock/mockvector.h"

class MockTensor : public Tensor {
public:
  MockTensor()
      : Tensor((Frame*)1)
  {
  }
};
