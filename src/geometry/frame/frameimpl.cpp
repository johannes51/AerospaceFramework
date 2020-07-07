#include "frameimpl.h"

#include "../vector.h"

using namespace asf::geometry;

FrameImpl::FrameImpl(const Frame* parent)
    : parent_(parent)
{
}

Vector FrameImpl::to(const Vector& from) const
{
  return to(from, this);
}

Vector FrameImpl::to(const Vector& from, FrameType toType) const
{
  if (toType == FrameType::Other) {
    throw false;
  }
  auto result = from;
  if (toType == type()) {
    return result;
  } else {
    if (parent_ == nullptr) { throw false; }
    result = unwind(from);
    return parent_->to(result, toType);
  }
  return result;
}

Vector FrameImpl::to(const Vector& from, const Frame* frameTo) const
{
  if (frameTo == this) {
    if (from.frame() == this) {
      return from;
    } else if (from.frame() == parent()) {
      return embed(from);
    } else {
      throw false;
    }
  } else {
    if (parent_ == nullptr) { throw false; }
    return parent_->to(unwind(from), frameTo);
  }
}

bool FrameImpl::operator==(const Frame& other) const
{
  return typeid(*this) == typeid(other) && parent() == other.parent() && equals(other);
}

bool FrameImpl::operator!=(const Frame& other) const
{
  return !(*this == other);
}

const Frame* FrameImpl::parent() const
{
  return parent_;
}

void FrameImpl::setParent(const Frame* value)
{
  parent_ = value;
}
