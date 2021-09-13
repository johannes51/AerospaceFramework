#ifndef MOCKCJD_H
#define MOCKCJD_H

#include "time/classicaljuliandate.h"

namespace a_t = asf::time;

class MockCjd : public a_t::ClassicalJulianDate<a_t::UTC> {
public:
  MockCjd(a_t::JulianLikeTimeData&& data)
      : a_t::ClassicalJulianDate<a_t::UTC>(std::move(data))
  {
  }
};

#endif // MOCKCJD_H
