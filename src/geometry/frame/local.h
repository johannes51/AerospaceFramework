#pragma once

#include "frameimpl.h"

namespace asf {
namespace geometry {

class Local : public FrameImpl {
public:
  Local();
  ASF_DISABLE_COPY_AND_MOVE(Local)

  void attach(const Frame* value, VectorCSP offset, TensorCSP rotation);

private:
  virtual FrameType type() const override { return FrameType::Other; }

  virtual bool equals(const Frame& other) const override;
  virtual Vector unwind(const Vector& from) const override;
  virtual Vector embed(const Vector& from) const override;

private:
  VectorCSP offset_;
  TensorCSP rotation_;
};

} // namespace geometry
} // namespace asf
