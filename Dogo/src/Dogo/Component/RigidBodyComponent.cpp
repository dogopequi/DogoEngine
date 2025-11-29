#include "dgpch.h"
#include "RigidBodyComponent.h"

namespace Dogo
{
	namespace ECS
	{
		RigidBodyComponent::~RigidBodyComponent()
		{
			rigidBody = nullptr;
			shape = nullptr;
		}
		void RigidBodyComponent::Init(const glm::vec3& pos, const glm::vec3& shape, bool kinematic)
		{
			rigidBody = DG_Physics::GetRigidDynamic(PxTransform(PxVec3(pos.x, pos.y, pos.z)));
			this->shape = DG_Physics::GetShape(shape.x, shape.y, shape.z);
			rigidBody->attachShape(*this->shape);
			PxRigidBodyExt::updateMassAndInertia(*rigidBody, mass);
			this->kinematic = kinematic;
			rigidBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, kinematic);
			this->shape->setSimulationFilterData(filterData);
			rigidBody->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);
			DG_Physics::AddActor(rigidBody);
		}
		void RigidBodyComponent::ApplyKinematic()
		{
			rigidBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, kinematic);
		}
	}
}