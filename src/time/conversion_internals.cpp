#include "conversion_internals.h"

#include "sofa.h"

#include "util/sofa_helper.h"

namespace a_t = asf::time;
namespace a_t_int = a_t::internal;

template <> a_t::TAI a_t_int::convertInternal<a_t::TAI, a_t::UTC>(const a_t::UTC& from)
{
  const auto jdUtc = util::toSofaJd(from);
  double jdTai1 = 0.;
  double jdTai2 = 0.;
  iauUtctai(jdUtc.first, jdUtc.second, &jdTai1, &jdTai2);

  return util::fromSofaJd<TAI>(jdTai1, jdTai2);
}

template <> a_t::TAI a_t_int::convertInternal<a_t::TAI, a_t::TT>(const a_t::TT& from)
{
  const auto jdTt = util::toSofaJd(from);
  double jdTai1 = 0.;
  double jdTai2 = 0.;
  iauTttai(jdTt.first, jdTt.second, &jdTai1, &jdTai2);

  return util::fromSofaJd<TAI>(jdTai1, jdTai2);
}

template <> a_t::TAI a_t_int::convertInternal<a_t::TAI, a_t::UT1>(const a_t::UT1& from)
{
  const auto jdUt1 = util::toSofaJd(from);
  double jdTai1 = 0.;
  double jdTai2 = 0.;
  iauUt1tai(jdUt1.first, jdUt1.second, 0, &jdTai1, &jdTai2); // TODO: fix dt

  return util::fromSofaJd<TAI>(jdTai1, jdTai2);
}

template <> a_t::TT a_t_int::convertInternal<a_t::TT, a_t::TAI>(const a_t::TAI& from)
{
  const auto jdTai = util::toSofaJd(from);
  double jdTt1 = 0.;
  double jdTt2 = 0.;
  iauTaitt(jdTai.first, jdTai.second, &jdTt1, &jdTt2);

  return util::fromSofaJd<TT>(jdTt1, jdTt2);
}

template <> a_t::TT a_t_int::convertInternal<a_t::TT, a_t::UT1>(const a_t::UT1& from)
{
  const auto jdUt1 = util::toSofaJd(from);
  double jdTt1 = 0.;
  double jdTt2 = 0.;
  iauUt1tt(jdUt1.first, jdUt1.second, 0, &jdTt1, &jdTt2); // TODO: fix dt

  return util::fromSofaJd<TT>(jdTt1, jdTt2);
}

template <> a_t::TT a_t_int::convertInternal<a_t::TT, a_t::UTC>(const a_t::UTC& from)
{
  const auto jdUtc = util::toSofaJd(from);
  double jdTai1 = 0.;
  double jdTai2 = 0.;
  double jdTt1 = 0.;
  double jdTt2 = 0.;
  iauUtctai(jdUtc.first, jdUtc.second, &jdTai1, &jdTai2);
  iauTaitt(jdTai1, jdTai2, &jdTt1, &jdTt2);

  return util::fromSofaJd<TT>(jdTt1, jdTt2);
}

template <> a_t::UT1 a_t_int::convertInternal<a_t::UT1, a_t::TAI>(const a_t::TAI& from)
{
  const auto jdTai = util::toSofaJd(from);
  double jdUt1_1 = 0.;
  double jdUt1_2 = 0.;
  iauTaiut1(jdTai.first, jdTai.second, 0, &jdUt1_1, &jdUt1_1); // TODO: fix dt

  return util::fromSofaJd<UT1>(jdUt1_1, jdUt1_2);
}

template <> a_t::UT1 a_t_int::convertInternal<a_t::UT1, a_t::TT>(const a_t::TT& from)
{
  const auto jdTt = util::toSofaJd(from);
  double jdUt1_1 = 0.;
  double jdUt1_2 = 0.;
  iauTtut1(jdTt.first, jdTt.second, 0, &jdUt1_1, &jdUt1_2);

  return util::fromSofaJd<UT1>(jdUt1_1, jdUt1_2);
}

template <> a_t::UT1 a_t_int::convertInternal<a_t::UT1, a_t::UTC>(const a_t::UTC& from)
{
  const auto jdUtc = util::toSofaJd(from);
  double jdUt1_1 = 0.;
  double jdUt1_2 = 0.;
  iauUtcut1(jdUtc.first, jdUtc.second, 0, &jdUt1_1, &jdUt1_2);

  return util::fromSofaJd<UT1>(jdUt1_1, jdUt1_2);
}

template <> a_t::UTC a_t_int::convertInternal<a_t::UTC, a_t::UT1>(const a_t::UT1& from)
{
  const auto jdUt1 = util::toSofaJd(from);
  double jdUtc1 = 0.;
  double jdUtc2 = 0.;
  iauUt1utc(jdUt1.first, jdUt1.second, 0, &jdUtc1, &jdUtc2);

  return util::fromSofaJd<UTC>(jdUtc1, jdUtc2);
}

template <> a_t::UTC a_t_int::convertInternal<a_t::UTC, a_t::TAI>(const a_t::TAI& from)
{
  const auto jdTai = util::toSofaJd(from);
  double jdUtc1 = 0.;
  double jdUtc2 = 0.;
  iauTaiutc(jdTai.first, jdTai.second, &jdUtc1, &jdUtc2);

  return util::fromSofaJd<UTC>(jdUtc1, jdUtc2);
}

template <> a_t::UTC a_t_int::convertInternal<a_t::UTC, a_t::TT>(const a_t::TT& from)
{
  const auto jdTt = util::toSofaJd(from);
  double jdTai1 = 0.;
  double jdTai2 = 0.;
  double jdUtc1 = 0.;
  double jdUtc2 = 0.;
  iauTttai(jdTt.first, jdTt.second, &jdTai1, &jdTai2);
  iauTaiutc(jdTai1, jdTai2, &jdUtc1, &jdUtc2);

  return util::fromSofaJd<UTC>(jdUtc1, jdUtc2);
}
