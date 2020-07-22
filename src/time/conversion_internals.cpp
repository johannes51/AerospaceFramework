#include "conversion_internals.h"

using namespace asf::time;

template<>
TAI asf::time::internal::convertInternal<TAI, UTC>(const UTC& from)
{
  return TAI();
}

template<>
TAI asf::time::internal::convertInternal<TAI, TT>(const TT& from)
{
  return TAI();
}

template<>
TAI asf::time::internal::convertInternal<TAI, UT1>(const UT1& from)
{
  return TAI();
}

template<>
TT asf::time::internal::convertInternal<TT, TAI>(const TAI& from)
{
  return TT();
}

template<>
TT asf::time::internal::convertInternal<TT, UT1>(const UT1& from)
{
  return TT();
}

template<>
TT asf::time::internal::convertInternal<TT, UTC>(const UTC& from)
{
  return TT();
}

template<>
UT1 asf::time::internal::convertInternal<UT1, TAI>(const TAI& from)
{
  return UT1();
}

template<>
UT1 asf::time::internal::convertInternal<UT1, TT>(const TT& from)
{
  return UT1();
}

template<>
UT1 asf::time::internal::convertInternal<UT1, UTC>(const UTC& from)
{
  return UT1();
}

template<>
UTC internal::convertInternal<UTC, UT1>(const UT1& from)
{
  return UTC();
}
