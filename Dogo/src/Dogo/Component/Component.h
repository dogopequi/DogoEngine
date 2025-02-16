#pragma once
#include "DG_Component.h"
#include "Dogo/Physics/DG_Physics.h"
#include "Dogo/Logger.h"
#include "Dogo/Renderer/AssimpModel.h"
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
        }


        inline float GetX() const { return m_Transform->p.x; }
        inline float GetY() const { return m_Transform->p.y; }
        inline float GetZ() const { return m_Transform->p.z; }
        inline PxTransform* GetTransform() const { return m_Transform; }
        inline void SetX(float x) { m_Transform = new PxTransform(PxVec3(x, GetY(), GetZ())); }
        inline void SetY(float y) { m_Transform = new PxTransform(PxVec3(GetX(), y, GetZ())); }
        inline void SetZ(float z) { m_Transform = new PxTransform(PxVec3(GetX(), GetY(), z)); }
        inline void SetTransform(PxTransform* t) { m_Transform = t; }

        inline void SetName(std::string name) { this->m_Name = name; }
        inline std::string GetName() const { return m_Name; }

    private:
        std::string m_Name;
        PxTransform* m_Transform;
    };
    /////////////////////////////////////////////////////////////////////////
        class StaticMeshComponent : public DogoECS::DG_Component
        {
        public:
            StaticMeshComponent(uint64_t id);
            StaticMeshComponent();

            ~StaticMeshComponent() override;


            inline void Update() override
            {
            }
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

            PxRigidStatic* GetActor() const 
            {
                return m_StaticBody;
            }

            inline void SetName(std::string name) { this->m_Name = name; }
            inline std::string GetName() const { return m_Name; }

        private:
            std::string m_Name;

            PxRigidStatic* m_StaticBody;
            Model* model;
        };
    }