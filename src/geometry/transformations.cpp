#include "transformations.h"

#include "sofa.h"

#include "frame/frame.h"
#include "tensor.h"
#include "time/time.h"
#include "util/sofa_helper.h"
#include "vector.h"

constexpr double sMajA = 6378137.0;
constexpr double f = 1 / 298.257223563;
constexpr double sMinA = sMajA * (1. - f);
constexpr double eSq = f * (2. - f);

std::pair<asf::geometry::TensorSP, asf::geometry::TensorSP> asf::geometry::calculateEcefMatrices(
    const time::Time& time, const Frame* parent, const Frame* ecef)
{
  const auto jdTai = util::toSofaJd(time::convert<time::ModifiedJulianDate<time::TAI>>(time));
  const auto jdTt = util::toSofaJd(time::convert<time::ModifiedJulianDate<time::TT>>(time));
  const auto jdUt1 = util::toSofaJd(time::convert<time::ModifiedJulianDate<time::UT1>>(time));
  double x = 0.;
  double y = 0.;
  iauXy06(jdTt.first, jdTt.second, &x, &y);
  double rc2t[3][3], rtc2[3][3]; // NOLINT
  iauC2t06a(jdTai.first, jdTai.second, jdUt1.first, jdUt1.second, x, y, rc2t); // NOLINT
  iauTr(rc2t, rtc2); // NOLINT
  auto rotationIn = std::make_shared<Tensor>(parent);
  auto rotationOut = std::make_shared<Tensor>(ecef);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      rotationIn->element(i, j) = rc2t[i][j]; // NOLINT
      rotationOut->element(i, j) = rtc2[i][j]; // NOLINT
    }
  }
  return std::make_pair(rotationIn, rotationOut);
}

void asf::geometry::llaToVector(Vector& vector, double lat, double lon, double a)
{
  const double N = sMajA / sqrt(1 - eSq * pow(sin(lon), 2));
  vector.element(0) = (N + a) * cos(lat) * cos(lon);
  vector.element(1) = (N + a) * cos(lat) * sin(lon);
  vector.element(2) = (N * (1 - eSq) + a) * sin(lat);
}

void asf::geometry::vectorToLla(Vector& to, const Vector& from)
{
  const auto xE = from.element(0);
  const auto yE = from.element(1);
  const auto zE = from.element(2);

  const auto p = sqrt(pow(xE, 2.) * pow(yE, 2.));
  const auto ESq = sMajA * sMajA - sMinA * sMinA;
  const auto F = 54. * sMinA * sMinA * zE * zE;
  const auto G = p * p + (1 - eSq) * zE * zE - eSq * ESq;
  const auto c = (eSq * eSq * F * p * p) / (pow(G, 3.));
  const auto s = pow(1 + c + sqrt(c * c + 2. * c), 1. / 3.);
  const auto P = F / (2. * pow(s + 4. / 3., 2.) * G * G);
  const auto Q = sqrt(1. + 2. * eSq * eSq * P);
  const auto r0 = sqrt(sMajA * sMajA / 2. * (1. + 1. / Q) - (P * (1. - eSq) * zE) / (Q * (1. + Q)) - P * p * p / 2.)
      - ((P * eSq * p) / (1. + Q));
  const auto U = sqrt(pow(p - eSq * r0, 2) + zE * zE);
  const auto V = sqrt(pow(p - eSq * r0, 2.) + (1. - eSq) * pow(zE, 2.));
  const auto z0 = (pow(sMinA, 2.) * zE) / (sMajA * V);
  const auto ePrimeSq = eSq * sMajA * sMajA / (sMinA * sMinA);

  to.element(0) = atan((zE + ePrimeSq * z0) / p);
  to.element(1) = atan2(yE, xE);
  to.element(2) = U * (1. - pow(sMinA, 2.) / (sMajA * V)); // NOLINT
}
