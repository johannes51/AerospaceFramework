#include "sofa_helper.h"

#include "time/conversions.h"
#include "time/modifiedjuliandate.h"

std::pair<double, double> asf::util::convertSofaJd(const asf::time::Time& time)
{
  auto jd = time::convert<time::ModifiedJulianDate>(time);
  return std::pair<double, double>(time::ModifiedJulianDate::DayOffset,
                                   jd.dayFraction() + time::ModifiedJulianDate::DayOffset);
}
