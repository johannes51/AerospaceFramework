#include "wgs84.h"

#include "../vector.h"
#include "ecef.h"

namespace a_g = asf::geometry;

constexpr double a = 6378137.0;
constexpr double f = 1 / 298.257223563;
constexpr double b = a * (1. - f);
constexpr double eSq = f * (2. - f);

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
  // TODO: put somewhere else, then test
  const auto& lat = from.element(0);
  const auto& lon = from.element(1);
  const auto& h = from.element(2);

  const double N = a / sqrt(1 - eSq * pow(sin(lon), 2));
  result.element(0) = (N + h) * cos(lat) * cos(lon);
  result.element(1) = (N + h) * cos(lat) * sin(lon);
  result.element(2) = (N * (1 - eSq) + h) * sin(lat);

  return ecef_->to(result, parent_);
}

a_g::Vector a_g::Wgs84::embed(const Vector& from) const
{
  if (from.behavesAs() != TransformationBehaviour::Position) {
    throw std::invalid_argument("Can only represent positions in WGS-84");
  }
  auto result = Vector(this, TransformationBehaviour::Position);
  // TODO: put somewhere else, then test
  const auto ecef = from.to(ecef_.get());
  const auto xE = ecef.element(0);
  const auto yE = ecef.element(1);
  const auto zE = ecef.element(2);

  const auto p = sqrt(pow(xE, 2.) * pow(yE, 2.));
  const auto ESq = a * a - b * b;
  const auto F = 54. * b * b * zE * zE;
  const auto G = p * p + (1 - eSq) * zE * zE - eSq * ESq;
  const auto c = (eSq * eSq * F * p * p) / (pow(G, 3.));
  const auto s = pow(1 + c + sqrt(c * c + 2. * c), 1. / 3.);
  const auto P = F / (2. * pow(s + 4. / 3., 2.) * G * G);
  const auto Q = sqrt(1. + 2. * eSq * eSq * P);
  const auto r0 = sqrt(a * a / 2. * (1. + 1. / Q) - (P * (1. - eSq) * zE) / (Q * (1. + Q)) - P * p * p / 2.)
      - ((P * eSq * p) / (1. + Q));
  const auto U = sqrt(pow(p - eSq * r0, 2) + zE * zE);
  const auto V = sqrt(pow(p - eSq * r0, 2.) + (1. - eSq) * pow(zE, 2.));
  const auto z0 = (pow(b, 2.) * zE) / (a * V);
  const auto ePrimeSq = eSq * a * a / (b * b);

  result.element(0) = atan((zE + ePrimeSq * z0) / p);
  result.element(1) = atan2(yE, xE);
  result.element(2) = U * (1. - pow(b, 2.) / (a * V)); // NOLINT

  return result;
}
