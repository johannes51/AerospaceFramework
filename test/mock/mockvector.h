#pragma once

#include "geometry/frame/eci.h"
#include "geometry/vector.h"

class MockVector : public Vector {
public:
  MockVector()
      : Vector(new ECI((Frame*)1))
  {
    vector_ << 0, 0, 0;
  }

  virtual Vector to(FrameType type) const override { return *this; }
  virtual Vector to(const Frame* frame) const override { return *this; }
};
