#pragma once

#include "frameimpl.h"

namespace asf {
namespace geometry {

class VehicleFrame : public FrameImpl {
public:
  VehicleFrame();

  virtual Vector to(const Vector& from, FrameType toType) const override;
  virtual Vector to(const Vector& from, const Frame* frameTo) const override;

  StateVectorSP getState();
  void update(StateVectorSP stateVector);
  void attach(const Frame* parent);

protected:
  virtual FrameType type() const override { return FrameType::Vehicle; }

private:
  StateVectorSP state_;

  virtual bool equals(const Frame& other) const override;
  virtual Vector unwind(const Vector& from) const override;
  virtual Vector embed(const Vector& from) const override;
};

} // namespace geometry
} // namespace asf
