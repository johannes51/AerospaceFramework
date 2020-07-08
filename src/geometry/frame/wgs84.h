#ifndef WGS84_H
#define WGS84_H

#include <chrono>

#include "frameimpl.h"

namespace asf {
namespace geometry {

class Wgs84 : public FrameImpl {
public:
  Wgs84(Frame* parent, std::chrono::system_clock::time_point&& time);
  ASF_DISABLE_COPY_AND_MOVE(Wgs84)

protected:
  virtual FrameType type() const override { return FrameType::LLA; }

private:
  virtual bool equals(const Frame& other) const override;
  virtual Vector unwind(const Vector& from) const override;
  virtual Vector embed(const Vector& from) const override;

  FrameSP ecef_;
};

} // namespace geometry
} // namespace asf

#endif // WGS84_H
