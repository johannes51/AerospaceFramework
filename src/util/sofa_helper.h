#ifndef SOFA_HELPER_H
#define SOFA_HELPER_H

#include <utility>

#include "time/time.h"

namespace asf {
namespace util {

std::pair<double, double> convertSofaJd(const asf::time::Time& time);

} // namespace util
} // namespace asf

#endif // SOFA_HELPER_H
