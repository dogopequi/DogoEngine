#pragma once
#include "dgpch.h"
#include "Component.h"
#include "DG_Component.h"
#include "Dogo/Physics/DG_Physics.h"
#include "Dogo/Renderer/AssimpModel.h"
#include "Dogo/Actors/Actor.h"
namespace Dogo
{
    
    void BaseComponent::AttachToComponent(BaseComponent* parent) {
        m_Parent = parent;
        parent->Init();
        Init();
    }
    void BaseComponent::AttachActor(const Actor& actor) {
        m_Parent = actor.GetTC();
        Init();
    }


    TransformComponent::TransformComponent(uint64_t id) : BaseComponent(id) { }
    TransformComponent::TransformComponent() : BaseComponent() {
    }
    TransformComponent::~TransformComponent() {}

    void TransformComponent::Update()
    {
        if (m_Parent != nullptr)
        {
            switch (m_ParentType)
            {
            case COMPONENT_TYPE::TRANSFORM:
            {
                auto* dyn = dynamic_cast<TransformComponent*>(m_Parent);
                if (dyn)
                {
                    m_Transform = dyn->GetTransform();
                }
                else
                    DG_WARN("Failed to cast to TransformComponent");
                break;
            }
            case COMPONENT_TYPE::DYNAMIC_MESH:
            {
                auto* dyn = dynamic_cast<DynamicMeshComponent*>(m_Parent);
                if (dyn)
                    m_Transform = dyn->GetBody()->getGlobalPose();
                else
                    DG_WARN("Failed to cast to DynamicMeshComponent");
                break;
            }
            default:
                DG_WARN("Parent type not registered");
                break;
            }
		}
    }


    DynamicMeshComponent::DynamicMeshComponent(uint64_t id) : BaseComponent(id) {
    }
    DynamicMeshComponent::DynamicMeshComponent() : BaseComponent() {
    }
    DynamicMeshComponent::~DynamicMeshComponent() {}

    void DynamicMeshComponent::Update()
    {
        DG_INFO("UPDATE");
        if (m_Parent)
        {
            auto* dyn = dynamic_cast<TransformComponent*>(m_Parent);
            if (dyn)
            {
                PxTransform transform = dyn->GetTransform();
                m_DynamicBody->setGlobalPose(transform);
            }
            else
                DG_WARN("Failed to cast to TransformComponent");
        }

    }

    void DynamicMeshComponent::Init()
    {
        DG_INFO("StaticMeshComponent Init called.");
        m_Shape = DG_Physics::GetShape(2.0f, 2.0f, 2.0f);
        PxTransform t = PxTransform(PxVec3(10.0f, 0.0f, 10.0f));
        m_DynamicBody = DG_Physics::GetRigidDynamic(t);
        m_DynamicBody->attachShape(*m_Shape);
        m_DynamicBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, false);
        DG_INFO("Creating dynamic mesh component1");
        DG_Physics::AddActor(m_DynamicBody);
    }

    StaticMeshComponent::StaticMeshComponent(uint64_t id) : BaseComponent(id) { 
    }
    StaticMeshComponent::StaticMeshComponent() : BaseComponent() {
    }

    StaticMeshComponent::~StaticMeshComponent() {}

    void StaticMeshComponent::Update()
    {
        if (m_Parent)
        {
            auto* dyn = dynamic_cast<TransformComponent*>(m_Parent);
            if (dyn)
            {
                PxTransform transform = dyn->GetTransform();
                PxVec3 pos = transform.p;
                m_StaticBody->setGlobalPose(transform);
            }
            else
                DG_WARN("Failed to cast to TransformComponent");
        }
    }
}