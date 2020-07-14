#include "conversions.h"

#include <utility>

#include "calendartime.h"
#include "modifiedjuliandate.h"
#include "tai.h"
#include "tt.h"
#include "ut1.h"

using namespace asf::time;


template<>
TAI asf::time::convert(const UTC& from)
{
  return TAI(); // WARNING: doesn't do anything
}

template<>
TT asf::time::convert(const UTC& from)
{
  return TT(); // WARNING: doesn't do anything
}

template<>
UT1 asf::time::convert(const UTC& from)
{
  return UT1(); // WARNING: doesn't do anything
}

template<>
ModifiedJulianDate asf::time::convert(const TAI& from)
{
  return ModifiedJulianDate(std::make_unique<TAI>()); // WARNING: doesn't do anything
}

template<>
ModifiedJulianDate asf::time::convert(const TT& from)
{
  return ModifiedJulianDate(std::make_unique<TT>()); // WARNING: doesn't do anything
}

template<>
ModifiedJulianDate asf::time::convert(const UT1& from)
{
  return ModifiedJulianDate(std::make_unique<UT1>()); // WARNING: doesn't do anything
}
