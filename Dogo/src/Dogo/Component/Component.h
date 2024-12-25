#pragma once
#include "DG_Component.h"
#include "Dogo/Physics/DG_Physics.h"
#include "Dogo/Logger.h"
namespace Dogo
{
    class TransformComponent : public DogoECS::DG_Component
    {
    public:
        TransformComponent(uint64_t id);
        TransformComponent();

        ~TransformComponent() override;


        inline void Update() override
        {

            DG_TRACE("x : %f, y: %f, z: %f", m_Transform.p.x, m_Transform.p.y, m_Transform.p.z);
        }

        inline float GetX() const { return m_Transform.p.x; }
        inline float GetY() const { return m_Transform.p.y; }
        inline float GetZ() const { return m_Transform.p.z; }
        inline PxTransform GetTransform() const { return m_Transform; }
        inline void SetX(float x) { m_Transform = PxTransform(PxVec3(x, GetY(), GetZ())); }
        inline void SetY(float y) { m_Transform = PxTransform(PxVec3(GetX(), y, GetZ())); }
        inline void SetZ(float z) { m_Transform = PxTransform(PxVec3(GetX(), GetY(), z)); }
        inline void SetTransform(PxTransform t) { m_Transform = t; }

        inline void SetName(std::string name) { this->m_Name = name; }
        inline std::string GetName() const { return m_Name; }

    private:
        std::string m_Name;
        PxTransform m_Transform = PxTransform(PxVec3(2.0f, 2.0f, 2.0f));
    };
}
    namespace DogoECS {
    template<> void DG_ComponentManager::RegisterComponentImpl<Dogo::TransformComponent>();

    template<> Dogo::TransformComponent* DG_ComponentManager::AddComponentImpl<Dogo::TransformComponent>(uint64_t EntityID);

    template<> void DG_ComponentManager::UpdateComponentsImpl<Dogo::TransformComponent>();

    template<> void DG_ComponentManager::RemoveComponentImpl<Dogo::TransformComponent>(uint64_t EntityID);
}