#pragma once
#include "dgpch.h"
#include "Component.h"
#include "DG_Component.h"
#include "Dogo/Physics/DG_Physics.h"
namespace Dogo
{
    TransformComponent::TransformComponent(uint64_t id) : DogoECS::DG_Component(id) {}
    TransformComponent::TransformComponent() : DogoECS::DG_Component() {
    }

    TransformComponent::~TransformComponent() { }
}

namespace Dogo
{
    StaticMeshComponent::StaticMeshComponent(uint64_t id) : DogoECS::DG_Component(id) {}
    StaticMeshComponent::StaticMeshComponent() : DogoECS::DG_Component() {}

    StaticMeshComponent::~StaticMeshComponent() { }
}