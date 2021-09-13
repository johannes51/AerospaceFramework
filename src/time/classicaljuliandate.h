#ifndef CLASSICALJULIANDATE_H
#define CLASSICALJULIANDATE_H

#include "julianliketimeimp.h"

namespace asf {
namespace time {

template <typename Scale> class ClassicalJulianDate : public JulianLikeTimeImp<Scale> {
public:
  ClassicalJulianDate() = default;
  static ClassicalJulianDate fromCjdDataYourResponsibility(JulianLikeTimeData&& data)
  {
    return ClassicalJulianDate { std::move(data) };
  }

protected:
  explicit ClassicalJulianDate(JulianLikeTimeData&& data)
      : JulianLikeTimeImp<Scale>(std::move(data))
  {
  }
};

} // namespace time
} // namespace asf

#endif // CLASSICALJULIANDATE_H
