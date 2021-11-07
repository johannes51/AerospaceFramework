#include "bilinearinterpolator.h"

#include <algorithm>
#include <stdexcept>

BilinearInterpolator::BilinearInterpolator(
    const std::vector<double>& xAxis, const std::vector<double>& yAxis, const std::vector<std::vector<double>>& data)
    : data_(data)
    , xAxis_(xAxis)
    , yAxis_(yAxis)
{
  if (xAxis.size() < 2 || yAxis.size() < 2 || data.size() != xAxis.size() || data[0].size() != yAxis.size()) {
    throw std::invalid_argument("Wrong axis sizes");
  }
}

double BilinearInterpolator::interpolate(double x, double y) const
{
  auto support = findSupports(x, y);
  auto bottomInterpolated
      = linearInterpolate(x, support.leftX, support.rightX, support.bottomLeftData, support.bottomRightData);
  auto topInterpolated = linearInterpolate(x, support.leftX, support.rightX, support.topLeftData, support.topRightData);
  return linearInterpolate(y, support.bottomY, support.topY, bottomInterpolated, topInterpolated);
}

BilinearInterpolator::SupportingPoints BilinearInterpolator::findSupports(double x, double y) const
{
  auto result = SupportingPoints {};

  auto xSupports = findSupports(x, xAxis_);
  auto ySupports = findSupports(y, yAxis_);

  result.leftX = xAxis_.at(xSupports.first);
  result.rightX = xAxis_.at(xSupports.second);
  result.bottomY = yAxis_.at(ySupports.first);
  result.topY = yAxis_.at(ySupports.second);

  result.bottomLeftData = data_.at(xSupports.first).at(ySupports.first);
  result.bottomRightData = data_.at(xSupports.second).at(ySupports.first);
  result.topLeftData = data_.at(xSupports.first).at(ySupports.second);
  result.topRightData = data_.at(xSupports.second).at(ySupports.second);
  return result;
}

double BilinearInterpolator::linearInterpolate(double x, double x1, double x2, double f1, double f2)
{
  return (x2 - x) / (x2 - x1) * f1 + (x - x1) / (x2 - x1) * f2;
}

std::pair<size_t, size_t> BilinearInterpolator::findSupports(double value, const std::vector<double>& axis)
{
  if (value < axis.front() || value > axis.back()) {
    throw std::invalid_argument("Value outside of range (this is an INTERpolator!)");
  }
  std::pair<size_t, size_t> result;

  auto done = false;
  auto mid = findMidpoint(axis.cbegin(), axis.cend());
  while (!done) {
    if (value < *mid) {
      result.second = mid - axis.begin();
      result.first = result.second - 1;
      std::advance(mid, -1);
      if (value > *mid) {
        done = true;
      }
    } else {
      result.first = mid - axis.begin();
      result.second = result.first + 1;
      std::advance(mid, 1);
      if (value < *mid) {
        done = true;
      }
    }
  }
  return result;
}

std::vector<double>::const_iterator BilinearInterpolator::findMidpoint(
    const std::vector<double>::const_iterator left, const std::vector<double>::const_iterator right)
{
  auto result = left;
  std::advance(result, std::distance(left, right) / 2);
  return result;
}
