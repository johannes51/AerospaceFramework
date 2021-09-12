#ifndef JULIANLIKETIMEIMP_H
#define JULIANLIKETIMEIMP_H

#include <utility> // for std::move o.O

#include "calendartime.h"
#include "julianliketime.h"

namespace asf {
namespace time {

struct JulianLikeTimeData {
  int wholeDays;
  double dayFraction;
};

JulianLikeTimeData decompose(long double jd);
JulianLikeTimeData decompose(double jd1, double jd2);

template <typename Scale> class JulianLikeTimeImp : public JulianLikeTime {
public:
  typedef std::enable_if_t<std::is_base_of_v<CalendarTime, Scale>, Scale> scale_type;

  ~JulianLikeTimeImp() override = 0;

  int wholeDays() const final;
  double dayFraction() const final;

protected:
  JulianLikeTimeImp() = default;
  explicit JulianLikeTimeImp(JulianLikeTimeData&& data)
      : data_(std::move(data))
  {
  }

private:
  JulianLikeTimeData data_ = { 0, 0. };
};

template <typename Scale> JulianLikeTimeImp<Scale>::~JulianLikeTimeImp() = default;

template <typename Scale> int asf::time::JulianLikeTimeImp<Scale>::wholeDays() const
{
  return data_.wholeDays;
}

template <typename Scale> double asf::time::JulianLikeTimeImp<Scale>::dayFraction() const
{
  return data_.dayFraction;
}

} // namespace time
} // namespace asf

#endif // JULIANLIKETIMEIMP_H
