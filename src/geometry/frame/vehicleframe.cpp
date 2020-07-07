#include "vehicleframe.h"

#include "../statevector.h"
#include "../transformations.h"
#include "../vector.h"

VehicleFrame::VehicleFrame()
    : FrameImpl(nullptr)
{
}

Vector VehicleFrame::to(const Vector& from, FrameType toType) const
{
  if (parent_ == nullptr && toType != type()) {
    throw false;
  }
  return FrameImpl::to(from, toType);
}

Vector VehicleFrame::to(const Vector& from, const Frame* frameTo) const
{
  if (parent_ == nullptr && frameTo != this) {
    throw false;
  }
  return FrameImpl::to(from, frameTo);
}

StateVectorSP VehicleFrame::getState()
{
  return state_;
}

void VehicleFrame::update(StateVectorSP stateVector)
{
  state_ = stateVector;
}

void VehicleFrame::attach(const Frame* parent)
{
  parent_ = parent;
  state_ = std::make_shared<StateVector>(parent_);
}

bool VehicleFrame::equals(const Frame& other) const
{
  return true;
}

Vector VehicleFrame::unwind(const Vector& from) const
{
  return from; // WARNING: define unwind
}

Vector VehicleFrame::embed(const Vector& from) const
{
  return from; // WARNING: define embed
}
