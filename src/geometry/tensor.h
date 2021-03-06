#ifndef TENSOR_H
#define TENSOR_H

#include <Eigen/Core>

#include "frame/frame.h"
#include "util/asf_definitions.h"

namespace asf {
namespace geometry {

class Tensor {
public:
  Tensor(const Frame* frame, Eigen::Matrix3d matrix = Eigen::Matrix3d());
  virtual ~Tensor() = default;
  Tensor(const Tensor&) = default;
  Tensor& operator=(const Tensor&) = default;
  Tensor(Tensor&&) = default;
  Tensor& operator=(Tensor&&) = default;

  double& element(int row, int col);
  const double& element(int row, int col) const;
  const Frame* frame() const;
  const Eigen::Matrix3d& eMatrix() const;

  Vector to(FrameType type) const;
  Vector to(const Frame* frame) const;

  Vector operator*(const Vector& rhs) const;

protected:
  const Frame* frame_;
  Eigen::Matrix3d matrix_;
};

} // namespace geometry
} // namespace asf

#endif // TENSOR_H
