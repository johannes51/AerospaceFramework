#include "tt.h"

using namespace asf::time;

TT::TT()
{
}

TT::TT(const TimePoint& timePoint)
  : CalendarTime(timePoint)
{
}

