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
    class TransformComponent;
    /////////////////////////////////////////////////////////////////////////
    class StaticMeshComponent : public DogoECS::DG_Component
    {
    public:
        StaticMeshComponent(uint64_t id);
        StaticMeshComponent();

        ~StaticMeshComponent() override;
        void Update() override;
        void AddModel(Model* model)
        {
            this->model = model;
        }

        void AttachToParent(PxShape* parent)
        {
            m_StaticBody->attachShape(*parent);
        }

        void Init(const PxTransform& t) {
            m_StaticBody = DG_Physics::GetRigidStatic(t);
        }

        inline PxRigidStatic* GetBody() const
        {
            return m_StaticBody;
        }

		inline Model* GetModel() const
		{
			return model;
		}

        inline void SetName(std::string name) { this->m_Name = name; }
        inline std::string GetName() const { return m_Name; }
        void AttachComponentToComponent(TransformComponent* parent);
        void AttachActorToComponent(const Actor& actor);

    private:
        std::string m_Name;
        TransformComponent* m_Parent = nullptr;
        PxRigidStatic* m_StaticBody;
        Model* model;
    };

    class DynamicMeshComponent : public DogoECS::DG_Component
    {
    public:
        DynamicMeshComponent(uint64_t id);
        DynamicMeshComponent();

        ~DynamicMeshComponent() override;
        void Update() override;
        void AddModel(Model* model)
        {
            this->model = model;
        }

        void AttachToParent(PxShape* parent)
        {
            m_DynamicBody->attachShape(*parent);
        }

        void Init(const PxTransform& t) {
            m_DynamicBody = DG_Physics::GetRigidDynamic(t);
            m_DynamicBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, false);
        }

        void MoveTo(const PxTransform& t) {
            if (m_DynamicBody)
                m_DynamicBody->setKinematicTarget(t);
        }

        inline PxRigidDynamic* GetBody() const
        {
            return m_DynamicBody;
        }

        inline Model* GetModel() const
        {
            return model;
        }
        inline void SetName(std::string name) { this->m_Name = name; }
        inline std::string GetName() const { return m_Name; }
        void AttachComponentToComponent(TransformComponent* parent);
        void AttachActorToComponent(const Actor& actor);

    private:
        std::string m_Name;
        TransformComponent* m_Parent = nullptr;
        PxRigidDynamic* m_DynamicBody;
        Model* model;
    };

    class TransformComponent : public DogoECS::DG_Component
    {
    public:
        TransformComponent(uint64_t id);
        TransformComponent();

        ~TransformComponent() override;

        void Update() override;


        inline float GetX() const { return m_Transform.p.x; }
        inline float GetY() const { return m_Transform.p.y; }
        inline float GetZ() const { return m_Transform.p.z; }
        inline const PxTransform& GetTransform() const { return m_Transform; }
        inline void SetX(float x) { m_Transform = PxTransform(PxVec3(x, GetY(), GetZ())); }
        inline void SetY(float y) { m_Transform = PxTransform(PxVec3(GetX(), y, GetZ())); }
        inline void SetZ(float z) { m_Transform = PxTransform(PxVec3(GetX(), GetY(), z)); }
        inline void SetTransform(const PxTransform& t) { m_Transform = t; }
        void AttachComponentToComponent(TransformComponent* parent);
        void AttachComponentToComponent(DynamicMeshComponent* parent);
        void AttachActorToComponent(const Actor& actor);

        inline void SetName(std::string name) { this->m_Name = name; }
        inline std::string GetName() const { return m_Name; }

    private:
        DG_Component* m_Parent = nullptr;
        std::string m_Name;
        PxTransform m_Transform;
        COMPONENT_TYPE m_ParentType;
    };
}