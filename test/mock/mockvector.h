#ifndef MOCKVECTOR_H
#define MOCKVECTOR_H

#include "geometry/frame/eci.h"
#include "geometry/vector.h"

class MockVector : public asf::geometry::Vector {
public:
  MockVector()
      : Vector(new asf::geometry::ECI((asf::geometry::Frame*)1))
  {
    vector_ << 0, 0, 0;
  }

  virtual Vector to(asf::geometry::FrameType type) const override { (void) type; return *this; }
  virtual Vector to(const asf::geometry::Frame* frame) const override { (void) frame; return *this; }
};

#endif // MOCKVECTOR_H
