#ifndef JULIANLIKETIME_H
#define JULIANLIKETIME_H

#include "time.h"

namespace asf {
namespace time {

class JulianLikeTime : public Time {
public:
  ~JulianLikeTime() override = default;

  virtual int wholeDays() const = 0;
  virtual double dayFraction() const = 0;
};

} // namespace time
} // namespace asf

#endif // JULIANLIKETIME_H
