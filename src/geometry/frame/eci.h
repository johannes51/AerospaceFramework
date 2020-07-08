#ifndef ECI_H
#define ECI_H

#include "frameimpl.h"

namespace asf {
namespace geometry {

class ECI : public FrameImpl {
public:
  ECI(const Frame* parent);
  virtual ~ECI() = default;
  ASF_DISABLE_COPY_AND_MOVE(ECI)

protected:
  virtual FrameType type() const override { return FrameType::ECI; }

private:
  virtual bool equals(const Frame& other) const override;
  virtual Vector unwind(const Vector& from) const override;
  virtual Vector embed(const Vector& from) const override;
};

} // namespace geometry
} // namespace asf

#endif // ECI_H
