#ifndef MOCKSTATEVECTOR_H
#define MOCKSTATEVECTOR_H

#include "mock/mocktensor.h"
#include "mock/mockvector.h"

#include "geometry/statevector.h"

class MockStateVector : public StateVector {
public:
  MockStateVector()
      : StateVector((Frame*)1)
  {
    position_ = std::make_shared<MockVector>();
    velocity_ = std::make_shared<MockVector>();
    acceleration_ = std::make_shared<MockVector>();
    rotation_ = std::make_shared<MockTensor>();
    angularVelocity_ = std::make_shared<MockTensor>();
    angularAcceleration_ = std::make_shared<MockTensor>();
  }
};

#endif // MOCKSTATEVECTOR_H
