#include "dgpch.h"
#include "Actor.h"
#include "Dogo/Component/Component.h"
namespace Dogo
{
	Actor::Actor(float x, float y, float z)
	{
		m_Entity = DogoECS::DG_EntityManager::CreateEntity();
		TC = m_Entity->AddComponent<TransformComponent>();
		TC->Init(glm::vec3(x, y, z));
	}
	Actor::~Actor()
	{
		m_Entity->RemoveComponent<TransformComponent>(TC->GetComponentID_ui64());
	}
	void Actor::AddDynamicModel(Model* model)
	{
		model->AddDynamicMeshComponent(TC->GetPos());
		TC->AttachToComponent(model->GetDynamicMeshComponent());
		TC->SetParentType(COMPONENT_TYPE::DYNAMIC_MESH);
		m_Model = model;
	}

	void Actor::AddStaticModel(Model* model)
	{
		model->AddStaticMeshComponent(TC->GetPos());
		model->GetStaticMeshComponent()->AttachToComponent(TC);
		m_Model = model;

	}
	void Actor::Update()
	{
	}


	void Actor::SetPosition(float x, float y, float z)
	{
		TC->SetPos(glm::vec3(x, y, z));
	}

	glm::vec3 Actor::GetPosition() const
	{
		return glm::vec3(TC->GetX(), TC->GetY(), TC->GetZ());
	}

	void Actor::AddForce(glm::vec3 force)
	{
		DynamicMeshComponent* dmc = m_Model->GetDynamicMeshComponent();
		if (dmc != nullptr)
			dmc->GetBody()->addForce(PxVec3(force.x, force.y, force.z), PxForceMode::eFORCE);
	}
	void Actor::AddImpulse(glm::vec3 force)
	{
		DynamicMeshComponent* dmc = m_Model->GetDynamicMeshComponent();
		if (dmc != nullptr)
			dmc->GetBody()->addForce(PxVec3(force.x, force.y, force.z), PxForceMode::eIMPULSE);
	}


}