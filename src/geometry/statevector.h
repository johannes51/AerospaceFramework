#pragma once

#include "util/asf_definitions.h"

namespace asf {
namespace geometry {

class Frame;

class StateVector {
public:
  StateVector(const Frame* frame);

  Vector& position();
  const Vector& position() const;
  Vector& velocity();
  const Vector& velocity() const;
  Vector& acceleration();
  const Vector& acceleration() const;

  Tensor& rotation();
  const Tensor& rotation() const;
  Tensor& angularVelocity();
  const Tensor& angularVelocity() const;
  Tensor& angularAcceleration();
  const Tensor& angularAcceleration() const;

protected:
  VectorSP position_;
  VectorSP velocity_;
  VectorSP acceleration_;
  TensorSP rotation_;
  TensorSP angularVelocity_;
  TensorSP angularAcceleration_;
};

} // namespace geometry
} // namespace asf
