#pragma once

#include <chrono>

#include "frameimpl.h"

namespace asf {
namespace geometry {

class ECEF : public FrameImpl {
public:
  ECEF(const Frame* parent, std::chrono::system_clock::time_point time);

protected:
  virtual FrameType type() const override { return FrameType::Other; }

private:
  virtual bool equals(const Frame& other) const override;
  virtual Vector unwind(const Vector& from) const override;
  virtual Vector embed(const Vector& from) const override;

  std::chrono::system_clock::time_point time_;
  TensorCSP rotationIn_;
  TensorCSP rotationOut_;
};

} // namespace geometry
} // namespace asf
