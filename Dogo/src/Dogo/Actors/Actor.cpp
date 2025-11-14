#include "dgpch.h"
#include "Actor.h"
namespace Dogo
{
	Actor::Actor(float x, float y, float z)
	{
	}
	Actor::~Actor()
	{
	}
	void Actor::AddDynamicModel(Model* model)
	{
		m_Model = model;
	}

	void Actor::AddStaticModel(Model* model)
	{
		m_Model = model;

	}
	void Actor::Update()
	{
	}


	void Actor::SetPosition(float x, float y, float z)
	{
	}

	glm::vec3 Actor::GetPosition() const
	{
		return glm::vec3(0.0f);
	}

	void Actor::AddForce(glm::vec3 force)
	{
	}
	void Actor::AddImpulse(glm::vec3 force)
	{
	}


}