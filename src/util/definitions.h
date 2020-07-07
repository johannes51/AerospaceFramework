#pragma once

#include <memory>

class Vector;
using VectorSP = std::shared_ptr<Vector>;
using VectorCSP = std::shared_ptr<const Vector>;

class Tensor;
using TensorSP = std::shared_ptr<Tensor>;
using TensorCSP = std::shared_ptr<const Tensor>;

class Craft;
using CraftSP = std::shared_ptr<Craft>;
using CraftCSP = std::shared_ptr<const Craft>;

class Component;
using ComponentSP = std::shared_ptr<Component>;

class RigidBodyComponent;
using RigidBodyComponentSP = std::shared_ptr<RigidBodyComponent>;

class SystemComponent;
using SystemComponentSP = std::shared_ptr<SystemComponent>;

class Separator;
using SeparatorSP = std::shared_ptr<Separator>;

class Environment;
using EnvironmentSP = std::shared_ptr<Environment>;
using EnvironmentCSP = std::shared_ptr<const Environment>;

class AtmosphereModel;
using AtmosphereModelSP = std::shared_ptr<AtmosphereModel>;

class GravityModel;
using GravityModelSP = std::shared_ptr<GravityModel>;

class SystemSimulation;
using SystemSimulationSP = std::shared_ptr<SystemSimulation>;

class Dynamics;
using DynamicsSP = std::shared_ptr<Dynamics>;

class StateVector;
using StateVectorSP = std::shared_ptr<StateVector>;
using StateVectorCSP = std::shared_ptr<const StateVector>;

class RigidBody;
using RigidBodyCSP = std::shared_ptr<const RigidBody>;

class Force;
using ForceCSP = std::shared_ptr<const Force>;

class PhysicsEngineAdapter;
using PhysicsEngineAdapterSP = std::shared_ptr<PhysicsEngineAdapter>;

#define DISABLE_COPY(ClassName)                                                                                        \
  ClassName(const ClassName&) = delete;                                                                                \
  ClassName& operator=(const ClassName&) = delete;
#define DISABLE_MOVE(ClassName)                                                                                        \
  ClassName(ClassName&&) = delete;                                                                                     \
  ClassName& operator=(ClassName&&) = delete;
#define DISABLE_COPY_AND_MOVE(ClassName)                                                                               \
  ClassName(const ClassName&) = delete;                                                                                \
  ClassName& operator=(const ClassName&) = delete;                                                                     \
  ClassName(ClassName&&) = delete;                                                                                     \
  ClassName& operator=(ClassName&&) = delete;
