#include "vector.h"

namespace a_g = asf::geometry;

a_g::Vector::Vector(const Frame* frame, TransformationBehaviour behavesAs)
    : Vector(frame, Eigen::Vector3d {}, behavesAs)
{
}

a_g::Vector::Vector(const Frame* frame, Eigen::Vector3d eVector, TransformationBehaviour behavesAs)
    : frame_(frame)
    , behavesAs_(behavesAs)
    , vector_(std::move(eVector))
{
}

asf::geometry::Vector::Vector(
    const asf::geometry::Frame* frame, double x, double y, double z, asf::geometry::TransformationBehaviour behavesAs)
    : Vector(frame, Eigen::Vector3d { x, y, z }, behavesAs)
{
}

double& a_g::Vector::element(int index)
{
  if (index > 2 || index < 0) {
    throw std::invalid_argument("Index out of bounds");
  }
  return vector_(index);
}

const double& a_g::Vector::element(int index) const
{
  if (index > 2 || index < 0) {
    throw std::invalid_argument("Index out of bounds");
  }
  return vector_(index);
}

a_g::Vector a_g::Vector::to(FrameType type) const
{
  return frame_->to(*this, type);
}

a_g::Vector a_g::Vector::to(const Frame* frame) const
{
  return frame_->to(*this, frame);
}

const a_g::Frame* a_g::Vector::frame() const
{
  return frame_;
}

void a_g::Vector::setFrame(const Frame* value)
{
  frame_ = value;
}

const Eigen::Vector3d& a_g::Vector::eVector() const
{
  return vector_;
}

const a_g::TransformationBehaviour& a_g::Vector::behavesAs() const
{
  return behavesAs_;
}

a_g::Vector a_g::Vector::operator+(const Vector& rhs) const
{
  if (*frame_ != *rhs.frame_) {
    throw std::invalid_argument("Cannot add vectors of different frames");
  }
  auto result = Vector(*this);
  result.vector_ = vector_ + rhs.vector_;
  return result;
}

bool a_g::Vector::operator==(const Vector& rhs) const
{
  return *frame_ == *rhs.frame_ && vector_ == rhs.vector_;
}

bool a_g::Vector::operator!=(const Vector& rhs) const
{
  return !(*this == rhs);
}
