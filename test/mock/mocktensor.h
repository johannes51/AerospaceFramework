#ifndef MOCKTENSOR_H
#define MOCKTENSOR_H

#include "geometry/tensor.h"

#include "mock/mockvector.h"

class MockTensor : public Tensor {
public:
  MockTensor()
      : Tensor((Frame*)1)
  {
  }
};

#endif // MOCKTENSOR_H
