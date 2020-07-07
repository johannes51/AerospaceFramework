#pragma once

#include "frameimpl.h"

class Local : public FrameImpl {
public:
  Local();
  DISABLE_COPY_AND_MOVE(Local)

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
