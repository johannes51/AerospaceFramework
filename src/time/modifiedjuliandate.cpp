#include "modifiedjuliandate.h"


asf::time::ModifiedJulianDate::ModifiedJulianDate(std::unique_ptr<asf::time::CalendarTime> scale)
  : JulianLikeTime(std::move(scale))
{
}

std::unique_ptr<asf::time::CalendarTime> asf::time::ModifiedJulianDate::toCal() const
{
}

asf::time::ClassicalJulianDate asf::time::ModifiedJulianDate::toClassical() const
{
}

double asf::time::ModifiedJulianDate::dayFraction() const
{
  return 0;
}
