#include "local.h"

#include "../tensor.h"
#include "../vector.h"

Local::Local()
    : FrameImpl(nullptr)
{
}

void Local::attach(const Frame* value, VectorCSP offset, TensorCSP rotation)
{
  parent_ = value;
  offset_ = std::move(offset);
  rotation_ = std::move(rotation);
}

bool Local::equals(const Frame& other) const
{
  return offset_ == static_cast<const Local&>(other).offset_ && rotation_ == static_cast<const Local&>(other).rotation_;
}

Vector Local::unwind(const Vector& from) const
{
  auto transformed = rotation_->eMatrix() * from.eVector();
  switch (from.behavesAs()) {
  case TransformationBehaviour::Vector:
  case TransformationBehaviour::Velocity:
  case TransformationBehaviour::Acceleration:
    return Vector(parent(), transformed, from.behavesAs());
    break;
  case TransformationBehaviour::Position:
    return Vector(parent(), transformed - offset_->eVector(), from.behavesAs());
    break;
  }
  return from;
}

Vector Local::embed(const Vector& from) const
{
  auto transformed = rotation_->eMatrix().transpose() * from.eVector();
  switch (from.behavesAs()) {
  case TransformationBehaviour::Position:
    return Vector(this, transformed + offset_->eVector(), from.behavesAs());
    break;
  default:
    return Vector(this, transformed, from.behavesAs());
    break;
  }
}
