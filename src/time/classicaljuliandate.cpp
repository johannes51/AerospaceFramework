#include "classicaljuliandate.h"

//asf::time::ClassicalJulianDate::ClassicalJulianDate(const asf::time::ClassicalJulianDate& other)
//  : JulianLikeTime(std::make_unique<CalendarTime>(*other.scale_))
//{
//}

asf::time::ClassicalJulianDate asf::time::ClassicalJulianDate::toClassical() const
{
  return *this;
}

std::unique_ptr<asf::time::CalendarTime> asf::time::ClassicalJulianDate::toCal() const
{
}

double asf::time::ClassicalJulianDate::dayFraction() const
{
}
