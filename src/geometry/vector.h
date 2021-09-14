#ifndef VECTOR_H
#define VECTOR_H

#include <Eigen/Core>

#include "frame/frame.h"

namespace asf {
namespace geometry {

enum class TransformationBehaviour {
  Vector,
  Position,
  Velocity,
  Acceleration,
};

class Vector {
public:
  Vector(const Frame* frame, TransformationBehaviour behavesAs = TransformationBehaviour::Vector);
  Vector(
      const Frame* frame, Eigen::Vector3d eVector, TransformationBehaviour behavesAs = TransformationBehaviour::Vector);
  Vector(const Frame* frame, double x, double y, double z,
      TransformationBehaviour behavesAs = TransformationBehaviour::Vector);
  virtual ~Vector() = default;
  Vector(const Vector&) = default;
  Vector& operator=(const Vector&) = default;
  Vector(Vector&&) = default;
  Vector& operator=(Vector&&) = default;

  virtual double& element(int index);
  virtual const double& element(int index) const;
  const Frame* frame() const;
  void setFrame(const Frame* value);
  const Eigen::Vector3d& eVector() const;

  const TransformationBehaviour& behavesAs() const;

  virtual Vector to(FrameType type) const;
  virtual Vector to(const Frame* frame) const;

  Vector operator+(const Vector& rhs) const;
  bool operator==(const Vector& rhs) const;
  bool operator!=(const Vector& rhs) const;

protected:
  const Frame* frame_;
  TransformationBehaviour behavesAs_;
  Eigen::Vector3d vector_;
};

} // namespace geometry
} // namespace asf

#endif // VECTOR_H
