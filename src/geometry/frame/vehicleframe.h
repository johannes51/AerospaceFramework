#ifndef VEHICLEFRAME_H
#define VEHICLEFRAME_H

#include "frameimpl.h"

namespace asf {
namespace geometry {

class VehicleFrame : public FrameImpl {
public:
  VehicleFrame();

  Vector to(const Vector& from, FrameType toType) const override;
  Vector to(const Vector& from, const Frame* frameTo) const override;

  StateVectorSP getState();
  void update(StateVectorSP stateVector);
  void attach(const Frame* parent);

protected:
  FrameType type() const override { return FrameType::Vehicle; }

private:
  StateVectorSP state_;

  bool equals(const Frame& other) const override;
  Vector unwind(const Vector& from) const override;
  Vector embed(const Vector& from) const override;
};

} // namespace geometry
} // namespace asf

#endif // VEHICLEFRAME_H
