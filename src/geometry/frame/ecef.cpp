#include "ecef.h"

#include "date/date.h"
#include "util/sofa/sofa.h"

#include "../vector.h"
#include "../tensor.h"

using namespace asf::geometry;

ECEF::ECEF(const Frame* parent, std::chrono::system_clock::time_point time)
    : FrameImpl(parent)
    , time_(time)
    , rotationIn_()
    , rotationOut_()
{
  auto dayNumber = date::floor<date::days>(time_);
  auto hours = date::floor<std::chrono::hours>(time_ - dayNumber);
  auto minutes = date::floor<std::chrono::minutes>(time_ - dayNumber - hours);
  std::chrono::duration<double, std::chrono::seconds::period> seconds =
      date::floor<std::chrono::seconds>(time_ - dayNumber - hours - minutes);
  auto date = date::year_month_day(dayNumber);
  double jdUtc1, jdUtc2;
  iauDtf2d("UTC", int(date.year()), unsigned(date.month()), unsigned(date.day()),
           hours.count(), minutes.count(), seconds.count(), &jdUtc1, &jdUtc2);
  double jdUt1_1, jdUt1_2;
  iauUtcut1(jdUtc1, jdUtc2, 0., &jdUt1_1, &jdUt1_2);
  double jdTai1, jdTai2;
  iauUt1tai(jdUt1_1, jdUt1_2, 0., &jdTai1, &jdTai2);
  double jdTt1, jdTt2;
  iauUt1tt(jdUt1_1, jdUt1_2, 0., &jdTt1, &jdTt2);
  double x,y;
  iauXy06(jdTt1, jdTt2, &x, &y);
  double rc2t[3][3], rtc2[3][3];
  iauC2t06a(jdTai1, jdTai2, jdUt1_1, jdUt1_2, x, y, rc2t);
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
  return time_ == static_cast<const ECEF&>(other).time_;
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
