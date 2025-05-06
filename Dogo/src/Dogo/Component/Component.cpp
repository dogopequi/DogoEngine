#pragma once
#include "dgpch.h"
#include "Component.h"
#include "DG_Component.h"
#include "Dogo/Physics/DG_Physics.h"
#include "Dogo/Renderer/AssimpModel.h"
#include "Dogo/Actors/Actor.h"
namespace Dogo
{
    TransformComponent::TransformComponent(uint64_t id) : DogoECS::DG_Component(id) { }
    TransformComponent::TransformComponent() : DogoECS::DG_Component() {
    }
    TransformComponent::~TransformComponent() {}
    void TransformComponent::AttachComponentToComponent(TransformComponent* parent)
    {
        m_Parent = parent;
		m_ParentType = COMPONENT_TYPE::TRANSFORM;
    }
    void TransformComponent::AttachComponentToComponent(DynamicMeshComponent* parent)
    {
        m_Parent = parent;
        m_ParentType = COMPONENT_TYPE::DYNAMIC_MESH;
    }
    void TransformComponent::AttachActorToComponent(const Actor& actor)
    {
        m_Parent = actor.GetTC();
    }
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
                    m_Transform = dyn->GetTransform();
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


    DynamicMeshComponent::DynamicMeshComponent(uint64_t id) : DogoECS::DG_Component(id) {  }
    DynamicMeshComponent::DynamicMeshComponent() : DogoECS::DG_Component() {
    }
    DynamicMeshComponent::~DynamicMeshComponent() {}
    void DynamicMeshComponent::AttachComponentToComponent(TransformComponent* parent)
    {
        m_Parent = parent;
        if (m_DynamicBody)
            m_DynamicBody->setGlobalPose(parent->GetTransform());
    }

    void DynamicMeshComponent::AttachActorToComponent(const Actor& actor)
    {
        AttachComponentToComponent(actor.GetTC());
    }
    void DynamicMeshComponent::Update()
    {
        if (m_Parent)
        {
            m_DynamicBody->setGlobalPose(m_Parent->GetTransform());
        }

    }

    StaticMeshComponent::StaticMeshComponent(uint64_t id) : DogoECS::DG_Component(id) { }
    StaticMeshComponent::StaticMeshComponent() : DogoECS::DG_Component() { }

    StaticMeshComponent::~StaticMeshComponent() {}
    void StaticMeshComponent::AttachComponentToComponent(TransformComponent* parent)
    {
        m_Parent = parent;
    }
    void StaticMeshComponent::AttachActorToComponent(const Actor& actor)
    {
        m_Parent = actor.GetTC();
    }
    void StaticMeshComponent::Update()
    {
        if (m_Parent)
            m_StaticBody->setGlobalPose(m_Parent->GetTransform());
    }
}