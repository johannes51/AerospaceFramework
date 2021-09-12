#include "julianliketimeimp.h"

namespace a_t = asf::time;

a_t::JulianLikeTimeData a_t::decompose(long double jd)
{
  auto result = a_t::JulianLikeTimeData { static_cast<int>(jd), 0. };
  result.dayFraction = static_cast<double>(jd - result.wholeDays);
  return result;
}

a_t::JulianLikeTimeData a_t::decompose(double jd1, double jd2)
{
  auto wholeDays1 = static_cast<int>(jd1);
  auto wholeDays2 = static_cast<int>(jd2);
  return { wholeDays1 + wholeDays2, (jd1 - wholeDays1) + (jd2 - wholeDays2) };
}
