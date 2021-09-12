#ifndef ECI_H
#define ECI_H

#include "frameimpl.h"

namespace asf {
namespace geometry {

class ECI : public FrameImpl {
public:
  explicit ECI(const Frame* parent);
  virtual ~ECI() = default;
  ASF_DISABLE_COPY_AND_MOVE(ECI)

protected:
  FrameType type() const override { return FrameType::ECI; }

private:
  bool equals(const Frame& other) const override;
  Vector unwind(const Vector& from) const override;
  Vector embed(const Vector& from) const override;
};

} // namespace geometry
} // namespace asf

#endif // ECI_H
