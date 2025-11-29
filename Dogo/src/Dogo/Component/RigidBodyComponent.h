#pragma once
#include "Components.h"
#include "Dogo/Physics/DG_Physics.h"
namespace Dogo
{
    namespace ECS
    {
        struct RigidBodyComponent : public DogoECS::DG_Component
        {
            RigidBodyComponent() : DogoECS::DG_Component() {}
            ~RigidBodyComponent();
            void Init(const glm::vec3& pos, const glm::vec3& shape, bool kinematic);
            void ApplyKinematic();
            inline void ApplyGravity() {
                rigidBody->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);
            }
            inline void DisableGravity() {
                rigidBody->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
            }
            PxRigidDynamic* rigidBody = nullptr;
            float mass = 1.0f;
            bool kinematic = false;
            PxShape* shape = nullptr;
            PxFilterData filterData;
            bool hasGravity = true;
        };
    }
}