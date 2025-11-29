#include "dgpch.h"
#include "System.h"
#include "Dogo/Component/Components.h"
#include "Dogo/Component/AudioSourceComponent.h"
#include "Dogo/Component/RigidBodyComponent.h"
#include "Dogo/Component/SpriteRendererComponent.h"
#include "Dogo/Physics/DG_Physics.h"
namespace Dogo
{
	void SpriteRenderSystem2D::Update(const std::weak_ptr<Renderer2D>& renderer)
	{
		if (!renderer.expired())
		{
			auto r = renderer.lock();
			DogoECS::DG_ComponentManager* manager = ECS::GetComponentManager();
			for (auto it = manager->AllActiveBegin<ECS::SpriteRendererComponent>();
				it != manager->AllActiveEnd<ECS::SpriteRendererComponent>(); ++it)
			{
				ECS::TransformComponent* pos = ECS::GetComponent<ECS::TransformComponent>(it->GetEntityID());
				it->Draw(r, pos->position.x, pos->position.y);
			}
		}
		else
			DG_TRACE("SpriteRenderSystem2D was not provided with a Renderer2D.");
	}
	namespace PhysicsSystem
	{
		double m_Accumulator = 0.0;
		const double m_FixedStep = 1.0 / 60.0;
		void Update(double step)
		{
			DogoECS::DG_ComponentManager* componentManager = ECS::GetComponentManager();
			if (step > 0.25)
				step = 0.25;
			m_Accumulator += step;

			while (m_Accumulator >= m_FixedStep)
			{
				DG_Physics::StepPhysics(m_FixedStep);
				m_Accumulator -= m_FixedStep;
			}

			auto entityPair = componentManager->GetEntitiesWith<ECS::RigidBodyComponent, ECS::TransformComponent>();
			for (auto it = entityPair.first; it != entityPair.second; ++it)
			{
				auto [phys, pos] = *it;
				if (phys->rigidBody && !phys->kinematic)
				{
					PxTransform t = phys->rigidBody->getGlobalPose();
					pos->SetPosition(glm::vec3(t.p.x, t.p.y, t.p.z));
				}
				else if (phys->rigidBody && phys->kinematic)
				{
					glm::vec3 targetPos = pos->GetPosition();
					phys->rigidBody->setKinematicTarget(PxTransform(targetPos.x, targetPos.y, targetPos.z));
				}
				ECS::VelocityComponent* vel = ECS::GetComponent<ECS::VelocityComponent>(phys->GetEntityID());
				if (vel)
				{
					if (phys->rigidBody)
					{
						if (!phys->kinematic)
						{
							PxVec3 linearVel = phys->rigidBody->getLinearVelocity();
							vel->SetLinearVelocity(glm::vec3(linearVel.x, linearVel.y, linearVel.z));
							PxVec3 angularVel = phys->rigidBody->getAngularVelocity();
							vel->SetAngularVelocity(glm::vec3(angularVel.x, angularVel.y, angularVel.z));
						}
						else
						{
							phys->rigidBody->setKinematicTarget(PxTransform(pos->position.x, pos->position.y, pos->position.z));
						}
					}
				}
			}


		}
	}
	void AudioSystem2D::Update()
	{
		DogoECS::DG_ComponentManager* componentManager = ECS::GetComponentManager();
		auto entityPair = componentManager->GetEntitiesWith<ECS::AudioSourceComponent2D, ECS::TransformComponent>();
		for (auto it = entityPair.first; it != entityPair.second; ++it)
		{
			auto [audio, pos] = *it;
			ALfloat sourcePos[] = { pos->position.x, pos->position.y, pos->position.z };
			alSourcefv(audio->source, AL_POSITION, sourcePos);
		}
	}
	void AudioSystem3D::Update()
	{
		DogoECS::DG_ComponentManager* componentManager = ECS::GetComponentManager();
		auto entityPair = componentManager->GetEntitiesWith<ECS::AudioSourceComponent3D, ECS::TransformComponent>();
		for (auto it = entityPair.first; it != entityPair.second; ++it)
		{
			auto [audio, pos] = *it;
			ALfloat sourcePos[] = { pos->position.x, pos->position.y, pos->position.z };
			alSourcefv(audio->source, AL_POSITION, sourcePos);
			ECS::VelocityComponent* vel = ECS::GetComponent<ECS::VelocityComponent>(audio->GetEntityID());
			ALfloat sourceVel[3] = { 0.0f, 0.0f, 0.0f };
			if (vel != nullptr) {
				sourceVel[0] = vel->linearVelocity.x;
				sourceVel[1] = vel->linearVelocity.y;
				sourceVel[2] = vel->linearVelocity.z;
			}
			alSourcefv(audio->source, AL_VELOCITY, sourceVel);
		}
	}

	void MovementSystem2D::Update(double step)
	{
		DogoECS::DG_ComponentManager* componentManager = ECS::GetComponentManager();
		auto comps = componentManager->GetTracker<ECS::TransformComponent>();
	}
	void MovementSystem3D::Update(double step)
	{
		DogoECS::DG_ComponentManager* componentManager = ECS::GetComponentManager();
		auto comps = componentManager->GetTracker<ECS::TransformComponent>();
	}
}
