#include "ecef.h"

#include "sofa.h"

#include "../tensor.h"
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
  // TODO: put somewhere else, then test
  const auto jdTai = util::toSofaJd(time::convert<time::ModifiedJulianDate<time::TAI>>(time));
  const auto jdTt = util::toSofaJd(time::convert<time::ModifiedJulianDate<time::TT>>(time));
  const auto jdUt1 = util::toSofaJd(time::convert<time::ModifiedJulianDate<time::UT1>>(time));
  double x = 0.;
  double y = 0.;
  iauXy06(jdTt.first, jdTt.second, &x, &y);
  double rc2t[3][3], rtc2[3][3]; // NOLINT
  iauC2t06a(jdTai.first, jdTai.second, jdUt1.first, jdUt1.second, x, y, rc2t); // NOLINT
  iauTr(rc2t, rtc2); // NOLINT
  auto rotationIn = std::make_shared<Tensor>(parent_);
  auto rotationOut = std::make_shared<Tensor>(this);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      rotationIn->element(i, j) = rc2t[i][j]; // NOLINT
      rotationOut->element(i, j) = rtc2[i][j]; // NOLINT
    }
  }
  rotationIn_ = rotationIn;
  rotationOut_ = rotationOut;
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
