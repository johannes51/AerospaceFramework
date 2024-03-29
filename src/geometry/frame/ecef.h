#ifndef ECEF_H
#define ECEF_H

#include "frameimpl.h"
#include "time/modifiedjuliandate.h"
#include "time/time.h"
#include "time/ut1.h"

namespace asf {
namespace geometry {

class ECEF : public FrameImpl {
public:
  ECEF(const Frame* parent, const time::Time& time);

protected:
  FrameType type() const override { return FrameType::Other; }

private:
  bool equals(const Frame& other) const override;
  Vector unwind(const Vector& from) const override;
  Vector embed(const Vector& from) const override;

  TensorCSP rotationIn_;
  TensorCSP rotationOut_;
};

} // namespace geometry
} // namespace asf

#endif // ECEF_H
