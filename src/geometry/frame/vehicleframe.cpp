#include "vehicleframe.h"

#include "../statevector.h"
#include "../transformations.h"
#include "../vector.h"

namespace a_g = asf::geometry;

a_g::VehicleFrame::VehicleFrame()
    : FrameImpl(nullptr)
    , state_()
{
}

a_g::Vector a_g::VehicleFrame::to(const Vector& from, FrameType toType) const
{
  if (parent_ == nullptr && toType != type()) {
    throw std::invalid_argument("No parent to unwind to");
  }
  return FrameImpl::to(from, toType);
}

a_g::Vector a_g::VehicleFrame::to(const Vector& from, const Frame* frameTo) const
{
  if (parent_ == nullptr && frameTo != this) {
    throw std::invalid_argument("No parent to unwind to");
  }
  return FrameImpl::to(from, frameTo);
}

a_g::StateVectorSP a_g::VehicleFrame::getState()
{
  return state_;
}

void a_g::VehicleFrame::update(StateVectorSP stateVector)
{
  state_ = std::move(stateVector);
}

void a_g::VehicleFrame::attach(const Frame* parent)
{
  parent_ = parent;
  state_ = std::make_shared<StateVector>(parent_);
}

bool a_g::VehicleFrame::equals(const Frame& other) const
{
  (void)other;
  return true; // TODO: fix!
}

a_g::Vector a_g::VehicleFrame::unwind(const Vector& from) const
{
  return from; // TODO: define unwind
}

a_g::Vector a_g::VehicleFrame::embed(const Vector& from) const
{
  return from; // TODO: define embed
}
