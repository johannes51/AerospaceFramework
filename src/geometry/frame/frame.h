#pragma once

#include "util/definitions.h"

enum class FrameType { ECI, LLA, Vehicle, Aerodynamic, Other };

class Frame {
public:
  virtual ~Frame() = default;
  DISABLE_COPY_AND_MOVE(Frame)

  virtual Vector to(const Vector& from) const = 0;
  virtual Vector to(const Vector& from, FrameType toType) const = 0;
  virtual Vector to(const Vector& from, const Frame* frameTo) const = 0;

  virtual const Frame* parent() const = 0;
  virtual void setParent(const Frame* value) = 0;

  virtual bool operator==(const Frame& rhs) const = 0;
  virtual bool operator!=(const Frame& rhs) const = 0;

protected:
  Frame() = default;

  virtual FrameType type() const = 0;

  friend class FrameManager;
};

using FrameSP = std::shared_ptr<Frame>;
