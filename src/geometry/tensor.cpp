#include "tensor.h"

#include "vector.h"

Tensor::Tensor(const Frame* frame, Eigen::Matrix3d matrix)
    : frame_(frame)
    , matrix_(matrix)
{
}

double& Tensor::element(int row, int col)
{
  if (row > 2 || row < 0 || col > 2 || col < 0) {
    throw false;
  }
  return matrix_(row, col);
}

const double& Tensor::element(int row, int col) const
{
  if (row > 2 || row < 0 || col > 2 || col < 0) {
    throw false;
  }
  return matrix_(row, col);
}

const Frame* Tensor::frame() const
{
  return frame_;
}

const Eigen::Matrix3d& Tensor::eMatrix() const
{
  return matrix_;
}

Vector Tensor::operator*(const Vector& rhs) const
{
  return Vector(rhs.frame(), matrix_ * rhs.eVector(), rhs.behavesAs());
}
