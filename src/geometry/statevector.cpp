#include "statevector.h"

#include "frame/frame.h"
#include "tensor.h"
#include "vector.h"

StateVector::StateVector(const Frame* frame)
    : position_(std::make_shared<Vector>(frame, TransformationBehaviour::Position))
    , velocity_(std::make_shared<Vector>(frame, TransformationBehaviour::Velocity))
    , acceleration_(std::make_shared<Vector>(frame, TransformationBehaviour::Acceleration))
    , rotation_(std::make_shared<Tensor>(frame))
    , angularVelocity_(std::make_shared<Tensor>(frame))
    , angularAcceleration_(std::make_shared<Tensor>(frame))
{
  if (!frame) {
    throw false;
  }
}

Vector& StateVector::position()
{
  return *position_;
}

const Vector& StateVector::position() const
{
  return *position_;
}

const Vector& StateVector::velocity() const
{
  return *velocity_;
}
