#include "eci.h"

#include "../vector.h"

namespace a_g = asf::geometry;

a_g::ECI::ECI(const Frame* parent)
    : FrameImpl(parent)
{
}

bool a_g::ECI::equals(const Frame& other) const
{
  (void)other;
  return true;
}

a_g::Vector a_g::ECI::unwind(const Vector& from) const
{
  return from;
}

a_g::Vector a_g::ECI::embed(const Vector& from) const
{
  return from;
}
