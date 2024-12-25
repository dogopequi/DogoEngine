#pragma once
#include "dgpch.h"
#include "Component.h"
#include "DG_Component.h"
namespace Dogo
{
    TransformComponent::TransformComponent(uint64_t id) : DogoECS::DG_Component(id) {}
    TransformComponent::TransformComponent() : DogoECS::DG_Component() {}

    TransformComponent::~TransformComponent() { }
}
namespace DogoECS {
    template<>
    REGISTER_COMPONENT_TEMPLATE(Dogo::TransformComponent)

    template<>
    ADD_COMPONENT_TEMPLATE(Dogo::TransformComponent)

    template <>
    REMOVE_COMPONENT_TEMPLATE(Dogo::TransformComponent)

    template<>
    UPDATE_COMPONENTS_TEMPLATE(Dogo::TransformComponent)
}