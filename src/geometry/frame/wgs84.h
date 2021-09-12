#ifndef WGS84_H
#define WGS84_H

#include "frameimpl.h"
#include "time/time.h"

namespace asf {
namespace geometry {

class Wgs84 : public FrameImpl {
public:
  Wgs84(Frame* parent, const asf::time::Time& time);
  ASF_DISABLE_COPY_AND_MOVE(Wgs84)

protected:
  FrameType type() const override { return FrameType::LLA; }

private:
  bool equals(const Frame& other) const override;
  Vector unwind(const Vector& from) const override;
  Vector embed(const Vector& from) const override;

  FrameSP ecef_;
};

} // namespace geometry
} // namespace asf

#endif // WGS84_H
