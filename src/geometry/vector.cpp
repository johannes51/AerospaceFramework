#include "vector.h"

using namespace asf::geometry;

Vector::Vector(const Frame* frame, TransformationBehaviour behavesAs)
    : frame_(std::move(frame))
    , behavesAs_(behavesAs)
{
  if (!frame_) {
    throw false;
  }
}

Vector::Vector(const Frame* frame, Eigen::Vector3d eVector, TransformationBehaviour behavesAs)
    : frame_(std::move(frame))
    , behavesAs_(behavesAs)
    , vector_(eVector)
{
}

double& Vector::element(int index)
{
  if (index > 2 || index < 0) {
    throw false;
  }
  return vector_(index);
}

const double& Vector::element(int index) const
{
  if (index > 2 || index < 0) {
    throw false;
  }
  return vector_(index);
}

Vector Vector::to(FrameType type) const
{
  return frame_->to(*this, type);
}

Vector Vector::to(const Frame* frame) const
{
  return frame_->to(*this, frame);
}

const Frame* Vector::frame() const
{
  return frame_;
}

void Vector::setFrame(const Frame* value)
{
  frame_ = value;
}

const Eigen::Vector3d& Vector::eVector() const
{
  return vector_;
}

const TransformationBehaviour& Vector::behavesAs() const
{
  return behavesAs_;
}

Vector Vector::operator+(const Vector& rhs) const
{
  if (*frame_ != *rhs.frame_) {
    throw false;
  }
  auto result = Vector(*this);
  result.vector_ = vector_ + rhs.vector_;
  return result;
}

bool Vector::operator==(const Vector& rhs) const
{
  return *frame_ == *rhs.frame_ && vector_ == rhs.vector_;
}

bool Vector::operator!=(const Vector& rhs) const
{
  return !(*this == rhs);
}
