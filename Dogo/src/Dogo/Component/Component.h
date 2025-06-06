#pragma once
#include "DG_Component.h"
#include "Dogo/Physics/DG_Physics.h"
#include "Dogo/Logger.h"

enum class COMPONENT_TYPE
{
	TRANSFORM, STATIC_MESH, DYNAMIC_MESH
};

namespace Dogo
{
    class Model;
    class Actor;

    class BaseComponent : public DogoECS::DG_Component
    {

    public:
        BaseComponent::BaseComponent(uint64_t id) : DogoECS::DG_Component(id) {}
        BaseComponent::BaseComponent() : DogoECS::DG_Component() {
        }
        virtual ~BaseComponent() = default;
        virtual void AttachToComponent(BaseComponent* parent);
        virtual void AttachActor(const Actor& actor);
        virtual COMPONENT_TYPE GetParentType() { return m_ParentType; }
		virtual void SetParentType(COMPONENT_TYPE type) { m_ParentType = type; }
        virtual void Init(const glm::vec3& pos) { DG_INFO("Base Init called."); };

    protected:
        BaseComponent* m_Parent = nullptr;
        COMPONENT_TYPE m_ParentType;
    };

    class TransformComponent;
    /////////////////////////////////////////////////////////////////////////
    class StaticMeshComponent : public BaseComponent
    {
    public:
        StaticMeshComponent(uint64_t id);
        StaticMeshComponent();

        ~StaticMeshComponent() override;
        void Update() override;

        void Init(const glm::vec3& pos) override;

        inline PxRigidStatic* GetBody() const
        {
            return m_StaticBody;
        }


    private:
        PxShape* m_Shape;
        PxRigidStatic* m_StaticBody;
    };

    class DynamicMeshComponent : public BaseComponent
    {
    public:
        DynamicMeshComponent(uint64_t id);
        DynamicMeshComponent();

        ~DynamicMeshComponent() override;
        void Update() override;

        void Init(const glm::vec3& pos) override;
        void MoveTo(const PxTransform& t) {
            if (m_DynamicBody)
                m_DynamicBody->setKinematicTarget(t);
        }

        inline PxRigidDynamic* GetBody() const
        {
            return m_DynamicBody;
        }


    private:
        PxShape* m_Shape;
        PxRigidDynamic* m_DynamicBody;
    };

    class TransformComponent : public BaseComponent
    {
    public:
        TransformComponent(uint64_t id);
        TransformComponent();

        ~TransformComponent() override;

        void Update() override;

        void Init(const glm::vec3& pos) override { DG_INFO("TransformComponent Init called."); SetPos(pos); }
        inline float GetX() const { return m_Transform.p.x; }
        inline float GetY() const { return m_Transform.p.y; }
        inline float GetZ() const { return m_Transform.p.z; }
		inline glm::vec3 GetPos() const { return glm::vec3(m_Transform.p.x, m_Transform.p.y, m_Transform.p.z); }
		inline void SetPos(const glm::vec3& pos) { m_Transform.p = PxVec3(pos.x, pos.y, pos.z); }
        inline const PxTransform& GetTransform() const { return m_Transform; }
        inline void SetX(float x) { m_Transform = PxTransform(PxVec3(x, GetY(), GetZ())); }
        inline void SetY(float y) { m_Transform = PxTransform(PxVec3(GetX(), y, GetZ())); }
        inline void SetZ(float z) { m_Transform = PxTransform(PxVec3(GetX(), GetY(), z)); }
        inline void SetTransform(const PxTransform& t) { m_Transform = t; }

    private:
        PxTransform m_Transform;
    };
}