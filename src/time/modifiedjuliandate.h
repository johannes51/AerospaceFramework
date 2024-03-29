#ifndef MODIFIEDJULIANDATE_H
#define MODIFIEDJULIANDATE_H

#include "julianliketimeimp.h"

#include "conversion_helpers.h"

namespace asf {
namespace time {

template <typename Scale> class ModifiedJulianDate : public JulianLikeTimeImp<Scale> {
public:
  typedef ModifiedJulianDate base_type;

  ModifiedJulianDate() = default;
  static ModifiedJulianDate fromSofaJd(const double& jd1, const double& jd2)
  {
    return ModifiedJulianDate { conv_helpers::sofaToMjdData({ jd1, jd2 }) };
  }
  static ModifiedJulianDate fromMjdDataYourResponsibility(JulianLikeTimeData&& data)
  {
    return ModifiedJulianDate { std::move(data) };
  }
  virtual ~ModifiedJulianDate() = default;

  static constexpr int DayOffset = 2400000;
  static constexpr double FractionOffset = 0.5;

private:
  explicit ModifiedJulianDate(JulianLikeTimeData&& data)
      : JulianLikeTimeImp<Scale>(std::move(data))
  {
  }
};

} // namespace time
} // namespace asf

#endif // MODIFIEDJULIANDATE_H
