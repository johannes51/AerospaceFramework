#include "tt.h"

namespace a_t = asf::time;

a_t::TT::TT(const TimePoint& timePoint)
    : CalendarTime(timePoint)
{
}
