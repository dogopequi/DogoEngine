#pragma once
#include <DogoECS.h>
inline static constexpr size_t NUM_ENTITIES = 5000;
inline static constexpr size_t NUM_COMPONENTS = 10000;
inline static DogoECS::DG_EntityManager entityManager(NUM_ENTITIES);
inline static DogoECS::DG_ComponentManager componentManager(NUM_COMPONENTS, NUM_ENTITIES);

inline DogoECS::DG_EntityManager* GetEntityManager() { return &entityManager; }
inline DogoECS::DG_ComponentManager* GetComponentManager() { return &componentManager; }

struct PositionComponent : public DogoECS::DG_Component { float x = 0, y = 0, z = 0; };
struct VelocityComponent : public DogoECS::DG_Component { float vx = 0, vy = 0, vz = 0; };