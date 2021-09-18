#include "ecef.h"

#include "sofa.h"

#include "../tensor.h"
#include "../transformations.h"
#include "../vector.h"
#include "time/conversions.h"
#include "time/tai.h"
#include "time/tt.h"
#include "time/ut1.h"
#include "time/utc.h"
#include "util/sofa_helper.h"

namespace a_g = asf::geometry;

a_g::ECEF::ECEF(const a_g::Frame* parent, const asf::time::Time& time)
    : FrameImpl(parent)
    , rotationIn_()
    , rotationOut_()
{
  auto [rotationIn, rotationOut] = calculateEcefMatrices(time, parent_, this);
  rotationIn_ = std::move(rotationIn);
  rotationOut_ = std::move(rotationOut);
}

bool a_g::ECEF::equals(const Frame& other) const
{
  const auto& otherEcef = dynamic_cast<const ECEF&>(other);
  return rotationIn_ == otherEcef.rotationIn_ && rotationOut_ == otherEcef.rotationOut_;
}

a_g::Vector a_g::ECEF::unwind(const Vector& from) const
{
  auto result = *rotationOut_ * from;
  result.setFrame(parent_);
  return result;
}

a_g::Vector a_g::ECEF::embed(const Vector& from) const
{
  auto result = *rotationIn_ * from;
  result.setFrame(this);
  return result;
}
