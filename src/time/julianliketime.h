#ifndef JULIANLIKETIME_H
#define JULIANLIKETIME_H

#include "time.h"

namespace asf {
namespace time {

class JulianLikeTime : public Time {
public:
  virtual ~JulianLikeTime() = default;

  virtual double dayFraction() const = 0;
  virtual int dayNumber() const = 0;
};

} // namespace time
} // namespace asf

#endif // JULIANLIKETIME_H
