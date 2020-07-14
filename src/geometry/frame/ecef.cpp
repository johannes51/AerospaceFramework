#include "ecef.h"

#include "../vector.h"
#include "../tensor.h"
#include "time/conversions.h"
#include "time/tai.h"
#include "time/tt.h"
#include "time/ut1.h"
#include "time/utc.h"
#include "util/sofa/sofa.h"
#include "util/sofa_helper.h"

using namespace asf::geometry;

ECEF::ECEF(const Frame* parent, const time::Time& time)
    : FrameImpl(parent)
    , rotationIn_()
    , rotationOut_()
{
  const auto jdTai = util::convertSofaJd(time::convert<time::TAI>(time));
  const auto jdTt = util::convertSofaJd(time::convert<time::TT>(time));
  const auto jdUt1 = util::convertSofaJd(time::convert<time::UT1>(time));
  double x,y;
  iauXy06(jdTt.first, jdTt.second, &x, &y);
  double rc2t[3][3], rtc2[3][3];
  iauC2t06a(jdTai.first, jdTai.second, jdUt1.first, jdUt1.second, x, y, rc2t);
  iauTr(rc2t, rtc2);
  auto rotationIn = std::make_shared<Tensor>(parent_);
  auto rotationOut = std::make_shared<Tensor>(this);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      rotationIn->element(i, j) = rc2t[i][j];
      rotationOut->element(i, j) = rtc2[i][j];
    }
  }
  rotationIn_ = rotationIn;
  rotationOut_ = rotationOut;
}

bool ECEF::equals(const Frame& other) const
{
  const auto& otherEcef = static_cast<const ECEF&>(other);
  return rotationIn_ == otherEcef.rotationIn_ && rotationOut_ == otherEcef.rotationOut_;
}

Vector ECEF::unwind(const Vector& from) const
{
  auto result = *rotationOut_ * from;
  result.setFrame(parent_);
  return result;
}

Vector ECEF::embed(const Vector& from) const
{
  auto result = *rotationIn_ * from;
  result.setFrame(this);
  return result;
}
