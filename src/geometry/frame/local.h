#ifndef LOCAL_H
#define LOCAL_H

#include "frameimpl.h"

namespace asf {
namespace geometry {

class Local : public FrameImpl {
public:
  Local();
  ASF_DISABLE_COPY_AND_MOVE(Local)

  void attach(const Frame* value, VectorCSP offset);
  void attach(const Frame* value, VectorCSP offset, TensorCSP rotation);

private:
  FrameType type() const override { return FrameType::Other; }

  bool equals(const Frame& other) const override;
  Vector unwind(const Vector& from) const override;
  Vector embed(const Vector& from) const override;

private:
  VectorCSP offset_;
  TensorCSP rotation_;
};

} // namespace geometry
} // namespace asf

#endif // LOCAL_H
