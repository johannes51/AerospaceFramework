#ifndef CONVERSION_HELPERS_H
#define CONVERSION_HELPERS_H

#include "julianliketimeimp.h" // for JulianLikeTimeData
#include "timepoint.h" // for TimePoint

namespace asf {
namespace time {
namespace conv_helpers {

JulianLikeTimeData cjdToMjdData(JulianLikeTimeData cjd);
JulianLikeTimeData mjdToCjdData(JulianLikeTimeData mjd);

TimePoint mjdDataToTimePoint(JulianLikeTimeData mjd);
JulianLikeTimeData timePointToMjdData(TimePoint cal);

std::pair<double, double> mjdDataToSofaJd(const JulianLikeTimeData& mjd);
JulianLikeTimeData sofaToMjdData(const std::pair<double, double>& mjd);
double decomposeDayFraction(const TimePoint& timePoint);
void reconstituteDayFraction(TimePoint& timePoint, double dayFraction);
std::pair<double, double> timePointToSofaJd(const TimePoint& timePoint);
TimePoint sofaJdToTimePoint(const std::pair<double, double>& sofaJd);

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

} // namespace conv_helpers
} // namespace time
} // namespace asf

#endif // CONVERSION_HELPERS_H
