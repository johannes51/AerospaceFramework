#ifndef CLASSICALJULIANDATE_H
#define CLASSICALJULIANDATE_H

#include "julianliketimeimp.h"

namespace asf {
namespace time {

template <typename Scale> class ClassicalJulianDate : public JulianLikeTimeImp<Scale> {
public:
  ClassicalJulianDate() = default;
};

} // namespace time
} // namespace asf

#endif // CLASSICALJULIANDATE_H
