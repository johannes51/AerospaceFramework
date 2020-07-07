#pragma once

#include <memory>

namespace asf {
namespace geometry {

  class Vector;
  using VectorSP = std::shared_ptr<Vector>;
  using VectorCSP = std::shared_ptr<const Vector>;

  class Tensor;
  using TensorSP = std::shared_ptr<Tensor>;
  using TensorCSP = std::shared_ptr<const Tensor>;

  class StateVector;
  using StateVectorSP = std::shared_ptr<StateVector>;
  using StateVectorCSP = std::shared_ptr<const StateVector>;

} // namespace geometry
} // namespace asf

#define ASF_DISABLE_COPY(ClassName)                                                                                        \
  ClassName(const ClassName&) = delete;                                                                                \
  ClassName& operator=(const ClassName&) = delete;
#define ASF_DISABLE_MOVE(ClassName)                                                                                        \
  ClassName(ClassName&&) = delete;                                                                                     \
  ClassName& operator=(ClassName&&) = delete;
#define ASF_DISABLE_COPY_AND_MOVE(ClassName)                                                                               \
  ClassName(const ClassName&) = delete;                                                                                \
  ClassName& operator=(const ClassName&) = delete;                                                                     \
  ClassName(ClassName&&) = delete;                                                                                     \
  ClassName& operator=(ClassName&&) = delete;
