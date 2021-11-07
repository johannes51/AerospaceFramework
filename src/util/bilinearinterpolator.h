#ifndef BILINEARINTERPOLATOR_H
#define BILINEARINTERPOLATOR_H

#include <vector>

#include "asf_definitions.h"

/**
 * @brief A class doing biliniear interpolation in a dataset between two axes.
 */
class BilinearInterpolator {
public:
  /**
   * @brief Construct a biliniear interpolator from a 2-dimensional table.
   * @param xAxis x-axis as a vector. Needs to have at least 2 values (how else would one interpolate).
   * @param yAxis y-axis as a vector. Also needs to have at least 2 values.
   * @param data Matrix (vector of vectors) containing the values of the function. Needs to coincide with xAxis and
   * yAxis and thus also have the same dimensions.
   */
  BilinearInterpolator(
      const std::vector<double>& xAxis, const std::vector<double>& yAxis, const std::vector<std::vector<double>>& data);
  ASF_DISABLE_COPY(BilinearInterpolator)
  BilinearInterpolator(BilinearInterpolator&&) = default;
  BilinearInterpolator& operator=(BilinearInterpolator&&) = default;

  /**
   * @brief Interpolate at f(x, y)
   * @param x x-axis-value to interpolate at.
   * @param y y-axis-value to interpolate at.
   * @return The interpolated result.
   */
  double interpolate(double x, double y) const;

private:
  struct SupportingPoints {
    double leftX;
    double rightX;
    double bottomY;
    double topY;
    double bottomLeftData;
    double bottomRightData;
    double topRightData;
    double topLeftData;
  };

  SupportingPoints findSupports(double x, double y) const;
  static double linearInterpolate(double x, double x1, double x2, double f1, double f2);
  static std::pair<size_t, size_t> findSupports(double value, const std::vector<double>& axis);
  static std::vector<double>::const_iterator findMidpoint(
      const std::vector<double>::const_iterator left, const std::vector<double>::const_iterator right);

  std::vector<std::vector<double>> data_;
  std::vector<double> xAxis_;
  std::vector<double> yAxis_;
};

#endif // BILINEARINTERPOLATOR_H
