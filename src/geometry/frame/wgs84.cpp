#include "wgs84.h"

#include "../transformations.h"
#include "../vector.h"
#include "ecef.h"

namespace a_g = asf::geometry;

a_g::Wgs84::Wgs84(Frame* parent, const asf::time::Time& time)
    : FrameImpl(parent)
    , ecef_(std::make_shared<ECEF>(parent, time))
{
}

bool a_g::Wgs84::equals(const Frame& other) const
{
  return *parent() == *other.parent();
}

a_g::Vector a_g::Wgs84::unwind(const Vector& from) const
{
  if (from.behavesAs() != TransformationBehaviour::Position) {
    throw std::invalid_argument("Can only represent positions in WGS-84");
  }
  auto result = Vector(ecef_.get(), TransformationBehaviour::Position);
  llaToVector(result, from.element(0), from.element(1), from.element(2));
  return ecef_->to(result, parent_);
}

a_g::Vector a_g::Wgs84::embed(const Vector& from) const
{
  if (from.behavesAs() != TransformationBehaviour::Position) {
    throw std::invalid_argument("Can only represent positions in WGS-84");
  }
  auto result = Vector(this, TransformationBehaviour::Position);
  vectorToLla(result, from.to(ecef_.get()));
  return result;
}
