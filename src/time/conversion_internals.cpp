#include "conversion_internals.h"

namespace a_t = asf::time;
namespace a_t_int = a_t::internal;

template <> a_t::TAI a_t_int::convertInternal<a_t::TAI, a_t::UTC>(const UTC& from)
{
  (void)from; // TODO: implement
  return TAI();
}

template <> a_t::TAI a_t_int::convertInternal<a_t::TAI, a_t::TT>(const TT& from)
{
  (void)from; // TODO: implement
  return TAI();
}

template <> a_t::TAI a_t_int::convertInternal<a_t::TAI, a_t::UT1>(const UT1& from)
{
  (void)from; // TODO: implement
  return TAI();
}

template <> a_t::TT a_t_int::convertInternal<a_t::TT, a_t::TAI>(const TAI& from)
{
  (void)from; // TODO: implement
  return TT();
}

template <> a_t::TT a_t_int::convertInternal<a_t::TT, a_t::UT1>(const UT1& from)
{
  (void)from; // TODO: implement
  return TT();
}

template <> a_t::TT a_t_int::convertInternal<a_t::TT, a_t::UTC>(const UTC& from)
{
  (void)from; // TODO: implement
  return TT();
}

template <> a_t::UT1 a_t_int::convertInternal<a_t::UT1, a_t::TAI>(const TAI& from)
{
  (void)from; // TODO: implement
  return UT1();
}

template <> a_t::UT1 a_t_int::convertInternal<a_t::UT1, a_t::TT>(const TT& from)
{
  (void)from; // TODO: implement
  return UT1();
}

template <> a_t::UT1 a_t_int::convertInternal<a_t::UT1, a_t::UTC>(const UTC& from)
{
  (void)from; // TODO: implement
  return UT1();
}

template <> a_t::UTC a_t_int::convertInternal<a_t::UTC, a_t::UT1>(const UT1& from)
{
  (void)from; // TODO: implement
  return UTC();
}

template <> a_t::UTC a_t_int::convertInternal<a_t::UTC, a_t::TAI>(const TAI& from)
{
  (void)from; // TODO: implement
  return UTC();
}

template <> a_t::UTC a_t_int::convertInternal<a_t::UTC, a_t::TT>(const TT& from)
{
  (void)from; // TODO: implement
  return UTC();
}
