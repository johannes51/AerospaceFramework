#pragma once

#include "frameimpl.h"

class ECI : public FrameImpl {
public:
  ECI(const Frame* parent);
  virtual ~ECI() = default;
  DISABLE_COPY_AND_MOVE(ECI)

protected:
  virtual FrameType type() const override { return FrameType::ECI; }

private:
  virtual bool equals(const Frame& other) const override;
  virtual Vector unwind(const Vector& from) const override;
  virtual Vector embed(const Vector& from) const override;
};
