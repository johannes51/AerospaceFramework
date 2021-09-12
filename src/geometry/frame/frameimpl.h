#ifndef FRAMEIMPL_H
#define FRAMEIMPL_H

#include "frame.h"

namespace asf {
namespace geometry {

class FrameImpl : public Frame {
public:
  ASF_DISABLE_COPY_AND_MOVE(FrameImpl)

  Vector to(const Vector& from) const override;
  Vector to(const Vector& from, FrameType toType) const override;
  Vector to(const Vector& from, const Frame* frameTo) const override;

  virtual bool operator==(const Frame& other) const final;
  virtual bool operator!=(const Frame& other) const final;

  virtual const Frame* parent() const final;
  virtual void setParent(const Frame* value) final;

protected:
  FrameImpl(const Frame* parent);

  const Frame* parent_;

private:
  virtual bool equals(const Frame& other) const = 0;
  virtual Vector unwind(const Vector& from) const = 0;
  virtual Vector embed(const Vector& from) const = 0;
};

} // namespace geometry
} // namespace asf

#endif // FRAMEIMPL_H
