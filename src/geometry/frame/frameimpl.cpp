#include "frameimpl.h"

#include "../vector.h"

namespace a_g = asf::geometry;

a_g::FrameImpl::FrameImpl(const Frame* parent)
    : parent_(parent)
{
}

a_g::Vector a_g::FrameImpl::to(const Vector& from) const
{
  return to(from, this);
}

a_g::Vector a_g::FrameImpl::to(const Vector& from, FrameType toType) const
{
  if (toType == FrameType::Other) {
    throw std::invalid_argument("Cannot convert to FrameType Other, pass Frame* instead");
  }
  auto result = from;
  if (toType != type()) {
    if (parent_ == nullptr) {
      throw std::invalid_argument("Need parent to undwind to");
    }
    result = unwind(from);
    return parent_->to(result, toType);
  }
  return result;
}

a_g::Vector a_g::FrameImpl::to(const Vector& from, const Frame* frameTo) const
{
  if (frameTo == this) {
    if (from.frame() == this) {
      return from;
    } else if (from.frame() == parent()) {
      return embed(from);
    } else {
      throw std::invalid_argument("Cannot unwind or embed");
    }
  } else {
    if (parent_ == nullptr) {
      throw std::invalid_argument("No parent to unwind to");
    }
    return parent_->to(unwind(from), frameTo);
  }
}

bool a_g::FrameImpl::operator==(const Frame& other) const
{
  return typeid(*this) == typeid(other) && parent() == other.parent() && equals(other);
}

bool a_g::FrameImpl::operator!=(const Frame& other) const
{
  return !(*this == other);
}

const a_g::Frame* a_g::FrameImpl::parent() const
{
  return parent_;
}

void a_g::FrameImpl::setParent(const Frame* value)
{
  parent_ = value;
}
