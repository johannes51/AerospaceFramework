#ifndef CONVERSION_HELPERS_H
#define CONVERSION_HELPERS_H

#include "calendartime.h" // for TimePoint
#include "julianliketimeimp.h" // for JulianLikeTimeData

namespace asf {
namespace time {
namespace conv_helpers {

TimePoint ttToTai(const TimePoint& tt);
TimePoint ut1ToTai(const TimePoint& ut1);
TimePoint utcToTai(const TimePoint& utc);
TimePoint taiToTt(const TimePoint& tai);
TimePoint ut1ToTt(const TimePoint& ut1);
TimePoint utcToTt(const TimePoint& utc);
TimePoint taiToUt1(const TimePoint& tai);
TimePoint ttToUt1(const TimePoint& tt);
TimePoint utcToUt1(const TimePoint& utc);
TimePoint taiToUtc(const TimePoint& tai);
TimePoint ttToUtc(const TimePoint& tt);
TimePoint ut1ToUtc(const TimePoint& ut1);

JulianLikeTimeData cjdToMjd(JulianLikeTimeData cjd);
JulianLikeTimeData mjdToCjd(JulianLikeTimeData mjd);

TimePoint mjdToCal(JulianLikeTimeData mjd);
JulianLikeTimeData calToMjd(TimePoint cal);

} // namespace conv_helpers
} // namespace time
} // namespace asf

#endif // CONVERSION_HELPERS_H
