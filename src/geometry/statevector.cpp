#include "statevector.h"

#include "frame/frame.h"
#include "tensor.h"
#include "vector.h"

namespace a_g = asf::geometry;

a_g::StateVector::StateVector(const Frame* frame)
    : position_(std::make_shared<Vector>(frame, TransformationBehaviour::Position))
    , velocity_(std::make_shared<Vector>(frame, TransformationBehaviour::Velocity))
    , acceleration_(std::make_shared<Vector>(frame, TransformationBehaviour::Acceleration))
    , rotation_(std::make_shared<Tensor>(frame))
    , angularVelocity_(std::make_shared<Tensor>(frame))
    , angularAcceleration_(std::make_shared<Tensor>(frame))
{
}

a_g::Vector& a_g::StateVector::position()
{
  return *position_;
}

const a_g::Vector& a_g::StateVector::position() const
{
  return *position_;
}

const a_g::Vector& a_g::StateVector::velocity() const
{
  return *velocity_;
}
