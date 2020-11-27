#include "local.h"

#include "../tensor.h"
#include "../vector.h"

namespace a_g = asf::geometry;

a_g::Local::Local()
    : FrameImpl(nullptr)
{
}

void a_g::Local::attach(const Frame* value, VectorCSP offset, TensorCSP rotation)
{
  parent_ = value;
  offset_ = std::move(offset);
  rotation_ = std::move(rotation);
}

bool a_g::Local::equals(const Frame& other) const
{
  return offset_ == dynamic_cast<const Local&>(other).offset_
      && rotation_ == dynamic_cast<const Local&>(other).rotation_;
}

a_g::Vector a_g::Local::unwind(const Vector& from) const
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

a_g::Vector a_g::Local::embed(const Vector& from) const
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
