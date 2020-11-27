#include "tensor.h"

#include "vector.h"

namespace a_g = asf::geometry;

a_g::Tensor::Tensor(const Frame* frame, Eigen::Matrix3d matrix)
    : frame_(frame)
    , matrix_(std::move(matrix))
{
}

double& a_g::Tensor::element(int row, int col)
{
  if (row > 2 || row < 0 || col > 2 || col < 0) {
    throw std::invalid_argument("Index out of bounds");
  }
  return matrix_(row, col);
}

const double& a_g::Tensor::element(int row, int col) const
{
  if (row > 2 || row < 0 || col > 2 || col < 0) {
    throw std::invalid_argument("Index out of bounds");
  }
  return matrix_(row, col);
}

const a_g::Frame* a_g::Tensor::frame() const
{
  return frame_;
}

const Eigen::Matrix3d& a_g::Tensor::eMatrix() const
{
  return matrix_;
}

a_g::Vector a_g::Tensor::operator*(const Vector& rhs) const
{
  return Vector(rhs.frame(), matrix_ * rhs.eVector(), rhs.behavesAs());
}
