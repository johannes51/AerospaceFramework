#include "eci.h"

#include "../vector.h"

ECI::ECI(const Frame* parent)
    : FrameImpl(parent)
{
}

bool ECI::equals(const Frame& other) const
{
  (void)other;
  return true;
}

Vector ECI::unwind(const Vector& from) const
{
  return from;
}

Vector ECI::embed(const Vector& from) const
{
  return from;
}
